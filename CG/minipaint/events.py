import glfw
import state
from config import *
from drawing import put_pixel, draw_line, draw_shape, flood_fill
from ui import save_png, save_button_rect, clear_button_rect, tool_button_rect, thickness_button_rect, color_button_rect

# verifica se um ponto está dentro de uma área
def _in(px,py,r):
     x0,y0,x1,y1 = r
     return x0 <= px <= x1 and y0 <= py <= y1

# lida com os clicks no painel
def handle_panel_click(px,py):
    if _in(px,py,save_button_rect()):
        save_png()
        return True
    
    if _in(px,py,clear_button_rect()): 
        state.framebuffer.fill(255)
        return True
    
    for i,(tid,_) in enumerate(TOOLS):
        if _in(px,py,tool_button_rect(i)):
            state.current_tool=tid
            return True

    for i,t in enumerate(THICKNESS_OPTIONS):
        if _in(px,py,thickness_button_rect(i)):
            state.thickness=t
            return True

    for i,color in enumerate(COLORS):
        if _in(px,py,color_button_rect(i)):
            state.current_color=color 
            return True
        
    return False

def mouse_button_callback(window,button,action,mods=0):
    # pega posição do cursor no momento do click
    x, y = glfw.get_cursor_pos(window)
    x, y = int(x), int(y)

    if button == glfw.MOUSE_BUTTON_LEFT:
        if action == glfw.PRESS: # se o botão esquerdo for pressionado
            if x >= PANEL_X: 
                handle_panel_click(x,y)
                return
            
            state.mouse_down = True
            state.start_x, state.start_y = x,y # salva a posição inicial e final
            state.last_x, state.last_y = x,y

            if state.current_tool == 'flood_fill':
                flood_fill(x,y,state.current_color)
                state.mouse_down = False # evita que o balde continue desenhando enquanto o mouse estiver pressionado
            elif state.current_tool in ['pencil', 'eraser']:
                color = (255, 255, 255) if state.current_tool == 'eraser' else state.current_color
                put_pixel(x, y, color) # pinta o pixel inicial do lápis ou borracha

        elif action == glfw.RELEASE:
            state.mouse_down = False
            if state.current_tool not in('pencil','eraser','flood_fill') and x < PANEL_X: # quando levantar o botão, se for uma forma, desenha a forma final
                draw_shape(state.start_x, state.start_y, x, y, state.current_tool)

# trata o movimento do mouse
def cursor_pos_callback(window,xpos,ypos):
    # atualiza a posição atual do cursor
    state.current_x, state.current_y = int(xpos), int(ypos)
    
    # se o mouse estiver pressionado e for lápis ou borracha, desenha uma linha entre a última posição e a atual
    if state.mouse_down and state.current_tool in('pencil','eraser') and state.current_x < PANEL_X:
        color = (255, 255, 255) if state.current_tool == 'eraser' else state.current_color
        draw_line(state.last_x, state.last_y, state.current_x, state.current_y, color)
        state.last_x, state.last_y = state.current_x, state.current_y

def key_callback(window,key,sc,action,mods):
    if action==glfw.PRESS:
        if key==glfw.KEY_ESCAPE: 
            glfw.set_window_should_close(window,True)
        if key==glfw.KEY_S:
            save_png()