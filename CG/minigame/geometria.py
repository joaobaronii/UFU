# transformações 2D e detecção de colisão
import math


def aplicar_rotacao_translacao(vertices, angulo, tx, ty):
    """
    Rotaciona e translada uma lista de vértices (x, y).

    Fórmula de rotação 2D:
        x' = x*cos(θ) - y*sin(θ)
        y' = x*sin(θ) + y*cos(θ)
    Depois só somamos a translação (tx, ty).
    """
    cos_a = math.cos(angulo)
    sin_a = math.sin(angulo)
    resultado = []
    for (x, y) in vertices:
        x_novo = x * cos_a - y * sin_a + tx
        y_novo = x * sin_a + y * cos_a + ty
        resultado.append((x_novo, y_novo))
    return resultado


def aplicar_escala(vertices, sx, sy):
    """Escala os vértices em torno da origem local do objeto."""
    return [(x * sx, y * sy) for (x, y) in vertices]


def colisao_circulo(x1, y1, r1, x2, y2, r2):
    """
    Colisão simples entre dois círculos.
    Só calcula a distância entre os centros e compara com a soma dos raios.
    """
    dx = x1 - x2
    dy = y1 - y2
    distancia = math.sqrt(dx * dx + dy * dy)
    return distancia < (r1 + r2)
