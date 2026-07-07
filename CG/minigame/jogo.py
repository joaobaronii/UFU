# loop principal e lógica de gameplay
import random
import pygame

from config import *
from entidades import Nave, Projetil, Inimigo
from geometria import colisao_circulo


class Jogo:
    def __init__(self):
        pygame.init()
        self.tela = pygame.display.set_mode((LARGURA, ALTURA))
        pygame.display.set_caption("Mini Game")
        self.clock = pygame.time.Clock()
        self.fonte = pygame.font.SysFont("monospace", 22, bold=True)
        self.fonte_grande = pygame.font.SysFont("monospace", 48, bold=True)

        # Gera as estrelas de fundo uma única vez (posição fixa com seed)
        random.seed(42)
        self.estrelas = [(random.randint(0, LARGURA),
                          random.randint(0, ALTURA)) for _ in range(60)]
        random.seed()

        self.reiniciar()

    def reiniciar(self):
        self.nave = Nave()
        self.projeteis = []
        self.inimigos = []
        self.timer_spawn = 0.0
        self.intervalo_spawn = 1.5   # começa em 1.5s, vai diminuindo
        self.game_over = False
        self.cooldown_tiro = 0.0

    #  EVENTOS

    def processar_eventos(self):
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                return False

            if evento.type == pygame.KEYDOWN:
                if self.game_over:
                    if evento.key == pygame.K_r:
                        self.reiniciar()
                else:
                    if evento.key == pygame.K_SPACE and self.cooldown_tiro <= 0:
                        self.projeteis.append(self.nave.atirar())
                        self.cooldown_tiro = 0.25  # máx 4 tiros/s

        return True

    #  ATUALIZAÇÃO

    def atualizar(self, dt):
        if self.game_over:
            return

        # Verifica as teclas pressionadas naquele momento
        teclas = pygame.key.get_pressed()
        self.nave.atualizar(dt, teclas)

        if self.cooldown_tiro > 0:
            self.cooldown_tiro -= dt

        # projéteis
        for p in self.projeteis:
            p.atualizar(dt)
        self.projeteis = [p for p in self.projeteis if p.ativo]

        # spawn de inimigos
        self.timer_spawn += dt
        if self.timer_spawn >= self.intervalo_spawn:
            self.timer_spawn = 0
            self.inimigos.append(Inimigo())
            # Dificuldade progressiva: intervalo cai até 0.5s
            self.intervalo_spawn = max(0.5, self.intervalo_spawn - 0.02)

        # inimigos
        for e in self.inimigos:
            e.atualizar(dt)
        self.inimigos = [e for e in self.inimigos if e.ativo]

        self._checar_colisoes()

        if self.nave.vidas <= 0:
            self.game_over = True

    def _checar_colisoes(self):
        """Verifica colisões projétil×inimigo e nave×inimigo."""

        # Projétil acerta inimigo → ambos somem, +10 pontos
        for p in self.projeteis:
            for e in self.inimigos:
                if colisao_circulo(p.x, p.y, p.RAIO, e.x, e.y, e.raio):
                    p.ativo = False
                    e.ativo = False
                    self.nave.pontuacao += 10

        # Inimigo bate na nave → perde vida
        for e in self.inimigos:
            if colisao_circulo(self.nave.x, self.nave.y, self.nave.RAIO,
                               e.x, e.y, e.raio):
                self.nave.tomar_dano()
                e.ativo = False

        # Remove os que foram marcados como inativos
        self.projeteis = [p for p in self.projeteis if p.ativo]
        self.inimigos = [e for e in self.inimigos if e.ativo]

    #  DESENHO

    def desenhar(self):
        self.tela.fill(PRETO)

        # Fundo estrelado (posições fixas, geradas no __init__)
        for (sx, sy) in self.estrelas:
            pygame.draw.circle(self.tela, (80, 80, 80), (sx, sy), 1)

        if not self.game_over:
            self.nave.desenhar(self.tela)
            for p in self.projeteis:
                p.desenhar(self.tela)
            for e in self.inimigos:
                e.desenhar(self.tela)
            self._desenhar_hud()
        else:
            self._desenhar_game_over()

        pygame.display.flip()

    def _desenhar_hud(self):
        txt_pontos = self.fonte.render(
            f"Pontos: {self.nave.pontuacao}",       True, BRANCO)
        txt_vidas = self.fonte.render(
            f"Vidas: {'♥ ' * self.nave.vidas}",    True, VERMELHO)
        txt_ctrl = self.fonte.render(
            "WASD/Setas: mover | Q/E: girar | ESPAÇO: atirar", True, CINZA
        )
        self.tela.blit(txt_pontos, (10, 10))
        self.tela.blit(txt_vidas,  (10, 36))
        self.tela.blit(txt_ctrl,   (10, ALTURA - 30))

    def _desenhar_game_over(self):
        cx = LARGURA // 2
        cy = ALTURA // 2

        go = self.fonte_grande.render(
            "GAME OVER",                         True, VERMELHO)
        pts = self.fonte.render(
            f"Pontuação final: {self.nave.pontuacao}",  True, BRANCO)
        rei = self.fonte.render(
            "Pressione R para reiniciar",               True, AMARELO)

        self.tela.blit(go,  (cx - go.get_width() // 2, cy - 80))
        self.tela.blit(pts, (cx - pts.get_width() // 2, cy))
        self.tela.blit(rei, (cx - rei.get_width() // 2, cy + 50))

    #  LOOP PRINCIPAL

    def executar(self):
        rodando = True
        while rodando:
            # dt em segundos — garante que a velocidade seja independente do FPS
            dt = self.clock.tick(FPS) / 1000.0
            rodando = self.processar_eventos()
            self.atualizar(dt)
            self.desenhar()
        pygame.quit()
