import numpy as np
from config import CANVAS_WIDTH, CANVAS_HEIGHT, COLORS

framebuffer = np.full((CANVAS_HEIGHT, CANVAS_WIDTH, 3), 255, dtype=np.uint8)

mouse_down  = False # click
start_x, start_y = 0, 0
last_x, last_y = 0, 0
current_x, current_y = 0, 0

current_color = COLORS[0]
current_tool = 'pencil'
thickness = 1

# painel do pillow
panel_tex_id = None