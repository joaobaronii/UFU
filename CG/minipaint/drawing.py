import math
from collections import deque
import state
from config import CANVAS_WIDTH, CANVAS_HEIGHT

# pinta de acordo com a espessura, criando um quadrado ao redor do pixel central
def put_pixel(x, y, color):
    for i in range(-state.thickness, state.thickness):
        for j in range(-state.thickness, state.thickness):
            px, py = int(x+i), int(y+j)

            if 0 <= px < CANVAS_WIDTH and 0 <= py < CANVAS_HEIGHT:
                state.framebuffer[py, px] = color

# pega a cor do pixel, retornando none se estiver fora dos limites
def get_pixel(x, y):
    if 0 <= x < CANVAS_WIDTH and 0 <= y < CANVAS_HEIGHT:
        return tuple(state.framebuffer[int(y), int(x)]) # retorna tupla com (R,G,B)
    return None

# algoritmo de Bresenham 
def bresenham_line_integer(x0, y0, x1, y1):
    points = []

    x0, y0, x1, y1 = int(x0), int(y0), int(x1), int(y1)

    dx = abs(x1 - x0)
    dy = abs(y1 - y0)

    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1

    err = dx - dy

    x, y = x0, y0

    while True:
        points.append((x, y))

        if x == x1 and y == y1:
            break

        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x += sx

        if e2 < dx:
            err += dx
            y += sy

    return points

# aplica bresenham para desenhar linha
def draw_line(x0,y0,x1,y1,color):
    points = bresenham_line_integer(x0, y0, x1, y1)

    for p in points:
        put_pixel(p[0], p[1], color)

# desenha retangulo usando draw_line
def draw_rectangle(x0, y0, x1, y1, color, filled=False):
    min_x, max_x = min(x0, x1), max(x0, x1)
    min_y, max_y = min(y0, y1), max(y0, y1)

    # se for preenchido, pinta o retângulo inteiro, se não apenas desenha as 4 linhas
    if filled:
        for y in range(min_y, max_y + 1):
            for x in range(min_x, max_x + 1):
                put_pixel(x, y, color)
    else:
        draw_line(min_x, min_y, max_x, min_y, color)
        draw_line(max_x, min_y, max_x, max_y, color)
        draw_line(max_x, max_y, min_x, max_y, color)
        draw_line(min_x, max_y, min_x, min_y, color)

# algoritmo do ponto médio para desenhar círculo
def draw_circle(xc, yc, r, color, filled=False):
    x = 0
    y = r
    d = 1 - r

    while y > x:
        if d < 0:
            d += 2 * x + 3
        else:
            d += 2 * (x - y) + 5
            y -= 1
        x += 1

        # se preenchido, pega as bordas e desenha uma linha entre elas
        if filled:
            draw_line(xc - x, yc + y, xc + x, yc + y, color)
            draw_line(xc - x, yc - y, xc + x, yc - y, color)
            draw_line(xc - y, yc + x, xc + y, yc + x, color)
            draw_line(xc - y, yc - x, xc + y, yc - x, color)
        # se não, desenha octeto
        else: 
            put_pixel(xc + x, yc + y, color)
            put_pixel(xc - x, yc + y, color)
            put_pixel(xc + x, yc - y, color)
            put_pixel(xc - x, yc - y, color)
            put_pixel(xc + y, yc + x, color)
            put_pixel(xc - y, yc + x, color)
            put_pixel(xc + y, yc - x, color)
            put_pixel(xc - y, yc - x, color)

# balde
def flood_fill(sx,sy,new_color):
    color=get_pixel(sx,sy) # pega a cor do pixel
    # se a cor do pixel for igual ou estiver fora dos limites, não faz nada
    if color is None or color==tuple(new_color): 
        return
    
    # cria uma fila para armazenar pixels a serem processados
    q = deque([(sx,sy)])

    # enquanto tiver fila, continua
    while q:
        x,y=q.popleft() # pega o primeiro da fila
        if 0 <= x < CANVAS_WIDTH and 0 <= y< CANVAS_HEIGHT: # se pixel está nos limites do canvas
            if tuple(state.framebuffer[y,x]) == color: # se a cor do pixel é igual do pixel inicial
                state.framebuffer[y,x] = new_color  # pinta o pixel
                 # coloca os vizinhos na fila
                q.append((x + 1, y)) # direita
                q.append((x - 1, y)) # esquerda
                q.append((x, y + 1)) # baixo
                q.append((x, y - 1)) # cima

# desenha a forma selecionada
def draw_shape(x0,y0,x1,y1,tool):
    if tool == 'line':
        draw_line(x0,y0,x1,y1,state.current_color)
    elif tool == 'rect':
        draw_rectangle(x0,y0,x1,y1,state.current_color,False)
    elif tool == 'rect_filled':
        draw_rectangle(x0,y0,x1,y1,state.current_color,True)
    elif tool in('circle','circle_filled'):
        r = int(math.sqrt((x1-x0)**2+(y1-y0)**2)) # distância euclidiana entre os pontos para definir o raio
        draw_circle(x0,y0,r,state.current_color,tool == 'circle_filled')