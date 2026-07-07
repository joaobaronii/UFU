from PIL import ImageFont

# dimensões
PANEL_WIDTH  = 120
CANVAS_WIDTH = 800
CANVAS_HEIGHT= 600
WIDTH  = CANVAS_WIDTH + PANEL_WIDTH
HEIGHT = CANVAS_HEIGHT
PANEL_X = CANVAS_WIDTH

# cores
COLORS = [
    (0,   0,   0  ),  
    (255, 255, 255),  
    (255, 0,   0  ),  
    (0,   200, 0  ),  
    (0,   0,   255),  
    (255, 200, 0  ),  
    (0,   220, 220),  
    (220, 0,   220),  
]
COLOR_NAMES = ['Preto','Branco','Vermelho','Verde','Azul','Amarelo','Ciano','Magenta']

# ferramentas
TOOLS = [
    ('pencil',        'Lapis'),
    ('eraser',        'Borracha'),
    ('line',          'Linha'),
    ('rect',          'Retangulo'),
    ('rect_filled',   'Ret. Cheio'),
    ('circle',        'Circulo'),
    ('circle_filled', 'Circ. Cheio'),
    ('flood_fill',    'Balde'),
]

# espessuras
THICKNESS_OPTIONS = [1, 3, 5]

# fontes
_FP = '/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf'
try:
    FONT = ImageFont.truetype(_FP, 11)
    FONT_SM = ImageFont.truetype(_FP, 9)
except:
    FONT = ImageFont.load_default() 
    FONT_SM = ImageFont.load_default()

# layout
PAD = 8
BTN_W = PANEL_WIDTH - 2 * PAD # 104 px
BTN_H = 24
GAP = 3

# ferramentas
SEC_TOOLS_Y = 8 + 2*(BTN_H + GAP) + 8
TOOLS_Y0 = SEC_TOOLS_Y + 13
TOOL_STEP = BTN_H + GAP

# espessura
SEC_THICK_Y = TOOLS_Y0 + len(TOOLS) * TOOL_STEP + 6
THICK_BTN_Y = SEC_THICK_Y + 13
THICK_CELL = (BTN_W - 2*GAP) // 3
THICK_BTN_H = 20

# cor 
SEC_COLOR_Y = THICK_BTN_Y + THICK_BTN_H + 13 + 6
COLOR_CELL = (BTN_W - GAP) // 2 # 50 px
COLOR_STEP = COLOR_CELL + GAP