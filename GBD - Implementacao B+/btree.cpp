#include <sys/types.h>
#include <sys/stat.h>

#include "btree.h"

#ifndef _BTREE_CPP
#define	_BTREE_CPP

bool fileExists(const char *filename) { struct stat statBuf; if (stat(filename,&statBuf) < 0) return false; return S_ISREG(statBuf.st_mode); }

btree::btree() {
    char nomearquivo[20] = "arvoreb.dat";

    // se arquivo ja existir, abrir e carregar cabecalho
    if (fileExists(nomearquivo)) {
        // abre arquivo
        arquivo = fopen(nomearquivo,"r+");
        leCabecalho();
    }
    // senao, criar novo arquivo e salvar o cabecalho
    else {
        // cria arquivo
        arquivo = fopen(nomearquivo,"w+");

        // atualiza cabecalho
        cabecalhoArvore.numeroElementos = 0;
        cabecalhoArvore.paginaRaiz = -1;
        salvaCabecalho();
    }
}

btree::~btree() {
    // fechar arquivo
    fclose(arquivo);
}

int btree::computarTaxaOcupacao() {
    return 0;
}

void btree::insereChave(int chave, int valor) {
    if (cabecalhoArvore.paginaRaiz == -1) {
        int idNovaPagina;
        pagina* novaRaiz = novaPagina(&idNovaPagina);
        if (!novaRaiz) 
            return;
        
        novaRaiz->chaves[0] = chave;
        novaRaiz->valores[0] = valor;
        novaRaiz->numeroElementos = 1;

        cabecalhoArvore.paginaRaiz = idNovaPagina;
        cabecalhoArvore.alturaArvore = 1;
        cabecalhoArvore.numeroElementos = 1;

        salvaPagina(idNovaPagina, novaRaiz);
        delete novaRaiz;
        salvaCabecalho();
        return;
    }

    int chavePromovida;
    int paginaPromovida;
    
    int resultado = insereRecursivo(chave, valor, cabecalhoArvore.paginaRaiz, 1, &chavePromovida, &paginaPromovida);
    if (resultado == 1) {
        int idNovaPagina;
        pagina* novaRaiz = novaPagina(&idNovaPagina);
        if (!novaRaiz) 
            return;

        novaRaiz->numeroElementos = 1;
        novaRaiz->chaves[0] = chavePromovida;
        novaRaiz->valores[0] = cabecalhoArvore.paginaRaiz;
        novaRaiz->valores[1] = paginaPromovida;
        
        cabecalhoArvore.paginaRaiz = idNovaPagina;
        cabecalhoArvore.alturaArvore++;
        
        salvaPagina(idNovaPagina, novaRaiz);
        delete novaRaiz;
    }

    if(resultado != -1) {
        cabecalhoArvore.numeroElementos++;
        salvaCabecalho();
    }
}

int btree::insereRecursivo(int chave, int valor, int numPagina, int nivel, int *chavePromovida, int *paginaPromovida) {
    pagina* pg = lePagina(numPagina);
    if (pg == nullptr) {
        return -1; 
    }
    
    int pos = 0;
    while(pos < pg->numeroElementos && chave > pg->chaves[pos]) {
        pos++;
    }

    if(nivel == cabecalhoArvore.alturaArvore) { 
        if(pos < pg->numeroElementos && chave == pg->chaves[pos]) {
            delete pg;
            return -1;
        }

        if(pg->numeroElementos < ORDEM - 1) { 
            insereNaPagina(pg, chave, valor, -1);
            salvaPagina(numPagina, pg);
            delete pg;
            return 0;
        } else { 
            dividirNo(pg, chave, valor, -1, chavePromovida, paginaPromovida);
            delete pg;
            return 1;
        }
    } else { 
        int paginaFilha = pg->valores[pos];
        int resultado = insereRecursivo(chave, valor, paginaFilha, nivel + 1, chavePromovida, paginaPromovida);

        if(resultado == 1) { 
             if(pg->numeroElementos < ORDEM - 1) { 
                insereNaPagina(pg, *chavePromovida, -1, *paginaPromovida);
                salvaPagina(numPagina, pg);
                delete pg;
                return 0;
             } else { 
                dividirNo(pg, *chavePromovida, -1, *paginaPromovida, chavePromovida, paginaPromovida);
                delete pg;
                return 1;
             }
        }
        delete pg;
        return 0;
    }
}

void btree::insereNaPagina(pagina *pg, int chave, int valor, int paginaDireita) {
    int i = pg->numeroElementos;

    while(i > 0 && chave < pg->chaves[i-1]) {
        pg->chaves[i] = pg->chaves[i-1];
        if (paginaDireita == -1) {
             pg->valores[i] = pg->valores[i-1];
        } 
        else {
            pg->valores[i+1] = pg->valores[i];
        }
        i--;
    }

    pg->chaves[i] = chave;

    if (paginaDireita == -1) {
        pg->valores[i] = valor;
    } else {
        pg->valores[i+1] = paginaDireita;
    }
    
    pg->numeroElementos++;
}

void btree::dividirNo(pagina *pg, int chave, int valor, int paginaDireita, int *chavePromovida, int *paginaPromovida) {
    int i;
    int tempChaves[ORDEM];
    int tempValores[ORDEM + 1];

    for (i = 0; i < pg->numeroElementos; i++) {
        tempChaves[i] = pg->chaves[i];
        tempValores[i] = pg->valores[i];
    }
    tempValores[pg->numeroElementos] = pg->valores[pg->numeroElementos];

    i = pg->numeroElementos;
    while(i > 0 && chave < tempChaves[i-1]) {
        tempChaves[i] = tempChaves[i-1];
        if (paginaDireita == -1) {
             tempValores[i] = tempValores[i-1];
        } else {
            tempValores[i+1] = tempValores[i];
        }
        i--;
    }

    tempChaves[i] = chave;

    if (paginaDireita == -1) {
        tempValores[i] = valor;
    } else { 
        tempValores[i+1] = paginaDireita;
    }
    
    int idNovaPagina;
    pagina* novaPg = novaPagina(&idNovaPagina);
    if(!novaPg) 
        return;

    *paginaPromovida = idNovaPagina;
    int meio = ORDEM / 2;
    int totalElementos = pg->numeroElementos + 1;
    pg->numeroElementos = meio;

    for(i = 0; i < meio; i++) {
        pg->chaves[i] = tempChaves[i];
        pg->valores[i] = tempValores[i];
    }

    if(paginaDireita == -1) {
        *chavePromovida = tempChaves[meio];
        novaPg->numeroElementos = totalElementos - meio;
        
        for (i = 0; i < novaPg->numeroElementos; i++) {
            novaPg->chaves[i] = tempChaves[meio + i];
            novaPg->valores[i] = tempValores[meio + i];
        }
        pg->valores[meio] = idNovaPagina; 
    
    } else { 
        *chavePromovida = tempChaves[meio]; 
        novaPg->numeroElementos = totalElementos - meio - 1;

        for (i = 0; i < novaPg->numeroElementos; i++) {
            novaPg->chaves[i] = tempChaves[meio + 1 + i];
        }
        for (i = 0; i < novaPg->numeroElementos + 1; i++) {
            novaPg->valores[i] = tempValores[meio + 1 + i];
        }
    }
    
    salvaPagina(pg->numeroPagina, pg);
    salvaPagina(novaPg->numeroPagina, novaPg);
    delete novaPg;
}

void btree::removeChave(int chave) {
	// neste trabalho, não é necessário implementar a remoção!

    // se remover, atualizar cabecalho
    if (true) {
        cabecalhoArvore.numeroElementos--;
        salvaCabecalho();
    }
}

int btree::buscaChave(int chave) {
    if (cabecalhoArvore.paginaRaiz == -1) {
        return -1;
    }

    int numPaginaAtual = cabecalhoArvore.paginaRaiz;
    int nivelAtual = 1;

    while (nivelAtual <= cabecalhoArvore.alturaArvore) {
        pagina* pg = lePagina(numPaginaAtual);
        if (pg == nullptr) {
            return -1; 
        }

        int pos = 0;
        while (pos < pg->numeroElementos && chave > pg->chaves[pos]) {
            pos++;
        }

        if (pos < pg->numeroElementos && chave == pg->chaves[pos]) {
            if (nivelAtual == cabecalhoArvore.alturaArvore) {
                int valorEncontrado = pg->valores[pos];
                delete pg;
                return valorEncontrado;
            }
            else {
                numPaginaAtual = pg->valores[pos + 1];
            }
        }
        else {
            numPaginaAtual = pg->valores[pos];
        }
        
        delete pg;
        nivelAtual++;
    }

    return -1;
}

#endif	/* _BTREE_CPP */
