package servidor;

import java.rmi.registry.LocateRegistry;
import java.rmi.Naming;

public class Servidor {
    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry(1099);

            ServicoDeVotacao servicoDeVotacao = new ServicoDeVotacaoImpl();

            Naming.rebind("ServicoDeVotacao", servicoDeVotacao);

            ServicoDeResultados servicoDeResultados = new ServicoDeResultadosImpl(servicoDeVotacao);

            Naming.rebind("ServicoDeResultados", servicoDeResultados);

            System.out.println("Servidor pronto.");
        } catch (Exception e) {
            System.err.println("Erro: " + e.toString());
            e.printStackTrace();
        }
    }
}
