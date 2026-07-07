# Nave, Projetil e Inimigo
import math
import random
import pygame

from config import *
from geometria import aplicar_rotacao_translacao, aplicar_escala


class Nave:
    # Triângulo apontando pra cima, definido no espaço local (centro = origem)
    VERTICES_BASE = [(0, -18), (12, 12), (-12, 12)]
    RAIO = 16

    def __init__(self):
        self.x = LARGURA // 2
        self.y = ALTURA - 80
        self.angulo = 0.0   # em radianos
        self.velocidade = 220   # px/s
        self.vel_rotacao = 3.0   # rad/s
        self.vidas = 3
        self.pontuacao = 0
        self.invencivel = 0.0   # segundos restantes de invencibilidade

    def atualizar(self, dt, teclas):
        # Rotação com Q (sentido anti-horário) e E (horário)
        if teclas[pygame.K_q]:
            self.angulo -= self.vel_rotacao * dt
        if teclas[pygame.K_e]:
            self.angulo += self.vel_rotacao * dt

        # Movimento nos 4 eixos — WASD ou setas
        if teclas[pygame.K_LEFT] or teclas[pygame.K_a]:
            self.x -= self.velocidade * dt
        if teclas[pygame.K_RIGHT] or teclas[pygame.K_d]:
            self.x += self.velocidade * dt
        if teclas[pygame.K_UP] or teclas[pygame.K_w]:
            self.y -= self.velocidade * dt
        if teclas[pygame.K_DOWN] or teclas[pygame.K_s]:
            self.y += self.velocidade * dt

        # Impede a nave de sair da tela
        self.x = max(20, min(LARGURA - 20, self.x))
        self.y = max(20, min(ALTURA - 20, self.y))

        if self.invencivel > 0:
            self.invencivel -= dt

    def obter_vertices(self):
        # Retorna os vértices da nave já transformados para o espaço de tela.
        return aplicar_rotacao_translacao(self.VERTICES_BASE, self.angulo, self.x, self.y)

    def desenhar(self, tela):
        # Efeito de piscar enquanto estiver invencível
        # Quando invencivel é um valor impar a nave desaparece da tela e quando for par, ela aparece de volta
        if self.invencivel > 0 and int(self.invencivel * 10) % 2 == 0:
            return
        verts = self.obter_vertices()
        # Preenche tudo de ciano e coloca uma borda branca por cima
        pygame.draw.polygon(tela, CIANO,   verts)
        pygame.draw.polygon(tela, BRANCO,  verts, 2)

    def atirar(self):
        # Cria um projétil na ponta da nave, na direção atual do ângulo.
        cos_a = math.cos(self.angulo)
        sin_a = math.sin(self.angulo)
        # Pega o vértice [0] (topo) e aplica a rotação manualmente
        px = 0 * cos_a - (-18) * sin_a + self.x
        py = 0 * sin_a + (-18) * cos_a + self.y
        return Projetil(px, py, self.angulo)

    def tomar_dano(self):
        # Desconta uma vida e ativa o período de invencibilidade.
        if self.invencivel <= 0:
            self.vidas -= 1
            self.invencivel = 2.0


class Projetil:
    VELOCIDADE = 500  # px/s
    RAIO = 4

    def __init__(self, x, y, angulo):
        self.x = x
        self.y = y
        self.angulo = angulo
        # Direção do projétil: segue o eixo "para cima" da nave
        # É negativo para o projétil não sair na direção contrária
        # É o deslocamento
        self.vx = -math.sin(angulo) * self.VELOCIDADE
        self.vy = -math.cos(angulo) * self.VELOCIDADE
        # Mostra se o projétil ainda existe
        self.ativo = True

    def atualizar(self, dt):
        self.x += self.vx * dt
        self.y += self.vy * dt
        # Desativa se sair dos limites da tela
        if self.x < 0 or self.x > LARGURA or self.y < 0 or self.y > ALTURA:
            self.ativo = False

    def desenhar(self, tela):
        pygame.draw.circle(
            tela, AMARELO, (int(self.x), int(self.y)), self.RAIO)


class Inimigo:
    RAIO_BASE = 20

    # Hexágono regular como forma base dos inimigos
    VERTICES_BASE = []
    for i in range(6):
        ang = math.radians(i * 60)
        VERTICES_BASE.append(
            (math.cos(ang) * RAIO_BASE, math.sin(ang) * RAIO_BASE))

    def __init__(self):
        # gera o inimigo em uma posição aleatoria da tela no eixo x
        self.x = random.randint(30, LARGURA - 30)
        self.y = -30  # começa acima da tela
        # deriva horizontal (ele pode se deslocar na diagonal por exemplo)
        self.vx = random.uniform(-60, 60)
        self.vy = random.uniform(80, 160)    # velocidade de descida aleatoria
        self.angulo = 0.0
        self.vel_rotacao = random.uniform(-1.5, 1.5)

        # Tamanho variado para dar variedade visual
        self.escala = random.uniform(0.6, 1.4)
        self.raio = self.RAIO_BASE * self.escala
        self.ativo = True

    def atualizar(self, dt):
        # pega a posição atual e soma com o deslocamento multiplicado pelo ultimo frame
        self.x += self.vx * dt
        self.y += self.vy * dt
        self.angulo += self.vel_rotacao * dt  # rotação contínua

        # Sai de cena quando passa da borda inferior
        if self.y > ALTURA + 40:
            self.ativo = False

    def obter_vertices(self):
        verts_escalados = aplicar_escala(
            self.VERTICES_BASE, self.escala, self.escala)
        return aplicar_rotacao_translacao(verts_escalados, self.angulo, self.x, self.y)

    def desenhar(self, tela):
        verts = self.obter_vertices()
        pygame.draw.polygon(tela, CINZA,    verts)
        pygame.draw.polygon(tela, VERMELHO, verts, 2)
