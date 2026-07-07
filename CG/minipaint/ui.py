import cv2 as cv
import numpy as np
import state
from config import *
from PIL import Image, ImageDraw

def save_button_rect():
    return PANEL_X+PAD, 8, PANEL_X+PAD+BTN_W, 8+BTN_H

def clear_button_rect():
    y0 = 8 + BTN_H + GAP
    return PANEL_X+PAD, y0, PANEL_X+PAD+BTN_W, y0+BTN_H

def tool_button_rect(i):
    y0 = TOOLS_Y0 + i * TOOL_STEP
    return PANEL_X+PAD, y0, PANEL_X+PAD+BTN_W, y0+BTN_H

def thickness_button_rect(i):
    x0 = PANEL_X + PAD + i*(THICK_CELL+GAP)
    return x0, THICK_BTN_Y, x0+THICK_CELL, THICK_BTN_Y+THICK_BTN_H

def color_button_rect(i):
    col = i % 2
    row = i // 2
    x0  = PANEL_X + PAD + col*COLOR_STEP
    y0  = SEC_COLOR_Y + row*COLOR_STEP
    return x0, y0, x0+COLOR_CELL, y0+COLOR_CELL

# salva imagem como png usando opencv
def save_png():
    filename = input("Digite o nome do arquivo para salvar: ").strip()

    if not filename:
        print("Nome inválido. Salvamento cancelado.")
        return
        
    if not filename.endswith('.png'):
        filename += '.png'
    try:
        # opencv usa BGR por padrão, precisamos converter de RGB para BGR ao salvar
        bgr_framebuffer = cv.cvtColor(state.framebuffer.astype(np.uint8), cv.COLOR_RGB2BGR)
        cv.imwrite(filename, bgr_framebuffer)
        print(f"Arquivo salvo: {filename}")
    except Exception as e:
        print(f"Erro ao salvar: {e}")

def _rr(draw,x0,y0,x1,y1,r,fill,outline=None,lw=1):
    draw.rounded_rectangle([x0,y0,x1,y1],radius=r,fill=fill,outline=outline,width=lw)

def _center_text(draw,x0,y0,x1,y1,text,font,color):
    bb=draw.textbbox((0,0),text,font=font)
    tw,th=bb[2]-bb[0],bb[3]-bb[1]
    draw.text(((x0+x1-tw)//2,(y0+y1-th)//2-1),text,font=font,fill=color)

def build_panel_image():
    img  = Image.new('RGBA',(PANEL_WIDTH,HEIGHT),(38,38,42,255))
    draw = ImageDraw.Draw(img)

    C_BG   =(38, 38, 42,255)
    C_BTN  =(60, 60, 65,255)
    C_SEL  =(55,115,185,255)
    C_BRD  =(80, 80, 86,255)
    C_SBRD =(100,160,225,255)
    C_TXT  =(215,215,215,255)
    C_STXT =(255,255,255,255)
    C_LBL  =(120,120,130,255)
    C_RED  =(140, 45, 45,255)
    C_RBRD =(190, 75, 75,255)
    C_GRN  =( 40,105, 55,255)
    C_GBRD =( 65,155, 85,255)
    C_SEP  =( 60, 60, 65,255)

    def lx(wx): 
        return wx - PANEL_X   # janela → local

    # separador esquerdo
    draw.line([(0,0),(0,HEIGHT-1)],fill=(65,65,70,255),width=2)

    # salvar
    x0,y0,x1,y1 = save_button_rect()
    _rr(draw,lx(x0),y0,lx(x1),y1,4,C_GRN,C_GBRD)
    _center_text(draw,lx(x0),y0,lx(x1),y1,"Salvar",FONT,C_STXT)

    # limpar
    x0,y0,x1,y1 = clear_button_rect()
    _rr(draw,lx(x0),y0,lx(x1),y1,4,C_RED,C_RBRD)
    _center_text(draw,lx(x0),y0,lx(x1),y1,"Limpar",FONT,C_STXT)

    # ferramentas
    draw.text((PAD, SEC_TOOLS_Y), "FERRAMENTAS", font=FONT_SM, fill=C_LBL)
    for i,(tid,label) in enumerate(TOOLS):
        x0,y0,x1,y1=tool_button_rect(i)
        sel = tid==state.current_tool
        _rr(draw,lx(x0),y0,lx(x1),y1,4,
            C_SEL if sel else C_BTN,
            C_SBRD if sel else C_BRD)
        _center_text(draw,lx(x0),y0,lx(x1),y1,label,FONT,
                     C_STXT if sel else C_TXT)

    # espessura 
    draw.text((PAD, SEC_THICK_Y), "ESPESSURA", font=FONT_SM, fill=C_LBL)
    for i,t in enumerate(THICKNESS_OPTIONS):
        x0,y0,x1,y1=thickness_button_rect(i)
        sel=t == state.thickness
        _rr(draw,lx(x0),y0,lx(x1),y1,3,
            C_SEL if sel else C_BTN,
            C_SBRD if sel else C_BRD)
        # bolinha preview
        cx=(lx(x0)+lx(x1))//2
        cy=(y0+y1)//2
        r=max(1,t//2)
        draw.ellipse([cx-r,cy-r,cx+r,cy+r],fill=(255,255,255,255))

    # cor
    draw.text((PAD, SEC_COLOR_Y - 13), "COR", font=FONT_SM, fill=C_LBL)
    for i,color in enumerate(COLORS):
        x0,y0,x1,y1 = color_button_rect(i)
        sel=color == state.current_color
        _rr(draw,lx(x0),y0,lx(x1),y1,4,(*color,255), (255,255,255,255) if sel else (70,70,75,255),lw=2 if sel else 1)
        if sel:  # checkmark
            cx,cy=(lx(x0)+lx(x1))//2,(y0+y1)//2
            lc=(0,0,0,200) if sum(color)>380 else (255,255,255,200)
            draw.line([(cx-5,cy),(cx-2,cy+4),(cx+5,cy-5)],fill=lc,width=2)

    return img