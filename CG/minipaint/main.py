import glfw
from OpenGL.GL import *
import numpy as np
import state
from config import *
from ui import build_panel_image
from events import mouse_button_callback, cursor_pos_callback, key_callback
from drawing import draw_shape

# envia o painel lateral como textura pro opengl desenhar
def upload_panel_texture():
    data = np.flipud(np.array(build_panel_image(), dtype=np.uint8))

    if state.panel_tex_id is None:
        state.panel_tex_id = glGenTextures(1)

    glBindTexture(GL_TEXTURE_2D, state.panel_tex_id)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,PANEL_WIDTH,HEIGHT,0,GL_RGBA,GL_UNSIGNED_BYTE,data.tobytes())
    glBindTexture(GL_TEXTURE_2D, 0)

# renderiza o painel
def render_panel_texture():
    glEnable(GL_TEXTURE_2D); glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glBindTexture(GL_TEXTURE_2D, state.panel_tex_id)
    glColor4f(1,1,1,1)
    glBegin(GL_QUADS)
    glTexCoord2f(0,0)
    glVertex2f(PANEL_X, 0)
    glTexCoord2f(1,0)
    glVertex2f(PANEL_X+PANEL_WIDTH, 0)
    glTexCoord2f(1,1)
    glVertex2f(PANEL_X+PANEL_WIDTH, HEIGHT)
    glTexCoord2f(0,1)
    glVertex2f(PANEL_X, HEIGHT)
    glEnd()
    glBindTexture(GL_TEXTURE_2D, 0)
    glDisable(GL_BLEND)
    glDisable(GL_TEXTURE_2D)

def main():
    if not glfw.init():
        print("Erro: Não foi possível inicializar o GLFW")
        return
    
    # define versão do opengl
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 3) 
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 3)
    # seleciona o perfil compatível para poder usar glDrawPixels
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_COMPAT_PROFILE)
    # janela não redimensionável para não crashar
    glfw.window_hint(glfw.RESIZABLE, glfw.FALSE)

    # cria janela
    window = glfw.create_window(WIDTH, HEIGHT, "Mini Paint", None, None)
    if not window: 
        print("Erro: Não foi possível criar a janela")
        glfw.terminate()
        return

    # define o contexto
    glfw.make_context_current(window)
    
    # define os callbacks 
    glfw.set_mouse_button_callback(window, mouse_button_callback)
    glfw.set_cursor_pos_callback(window, cursor_pos_callback)
    glfw.set_key_callback(window, key_callback)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1)
    glMatrixMode(GL_MODELVIEW)

    upload_panel_texture()
    prev_state = None

    # loop principal, enquanto não clicar no X
    while not glfw.window_should_close(window):
        # apaga o frame anterior
        glClear(GL_COLOR_BUFFER_BIT)

        # se clicar e a ferramenta for uma forma
        if state.mouse_down and state.current_tool not in('pencil','eraser','flood_fill'):
            backup = state.framebuffer.copy() # salva o estado do framebuffer 
            draw_shape(state.start_x, state.start_y, state.current_x, state.current_y, state.current_tool) # desenha a forma 

            flipped_buffer = np.flipud(state.framebuffer) 
            glRasterPos2i(0,0)
            glDrawPixels(CANVAS_WIDTH,CANVAS_HEIGHT, GL_RGB,GL_UNSIGNED_BYTE, flipped_buffer)
            
            state.framebuffer = backup # restaura o framebuffer para evitar que a forma desenhada temporariamente seja permanente
        else:
            flipped_buffer = np.flipud(state.framebuffer) 
            glRasterPos2i(0,0)
            glDrawPixels(CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, flipped_buffer)

        current_state = (state.current_tool, state.current_color, state.thickness)
        if current_state != prev_state:
            upload_panel_texture()
            prev_state = current_state

        render_panel_texture()
        glfw.swap_buffers(window) # troca os buffers para mostrar o novo frame
        glfw.poll_events() # processa os eventos (mouse, teclado)

    glfw.terminate()

if __name__=="__main__":
    main()