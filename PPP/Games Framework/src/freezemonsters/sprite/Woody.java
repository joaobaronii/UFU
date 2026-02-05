package freezemonsters.sprite;

import javax.swing.ImageIcon;
import java.awt.*;
import java.awt.event.KeyEvent;
import spriteframework.Commons;
import spriteframework.sprite.Player;

public class Woody extends Player {
    private int height;
    private int lastDx;
    private int lastDy;

    public Woody() {
        super();
    }

    protected void loadImage() {
        ImageIcon ii = new ImageIcon("src/images/woody.png");
        Image woodyImage = ii.getImage().getScaledInstance(30,60, image.SCALE_SMOOTH);
        width = 30;
        height = 60;
        setImage(woodyImage);
    }

    public void act() {
        x += dx;
        y += dy;

        if (x <= 2)
            x = 2;
        if (x >= Commons.BOARD_WIDTH - Math.floor(1.5*width))
            x = Commons.BOARD_WIDTH - (int)Math.floor(1.5*width);
        if (y <= 2)
            y = 2;
        if (y >= Commons.GROUND - Math.floor(0.6*height))
            y = Commons.GROUND - (int)Math.floor(0.6*height);
        if (dx != 0 || dy != 0) {
            lastDx = dx;
            lastDy = dy;
        }
    }

    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT)
            dx = -2;
        if (key == KeyEvent.VK_RIGHT)
            dx = 2;
        if (key == KeyEvent.VK_UP)
            dy = -2;
        if (key == KeyEvent.VK_DOWN)
            dy = 2;
    }

    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT && dx < 0)
            dx = 0;
        if (key == KeyEvent.VK_RIGHT && dx > 0)
            dx = 0;
        if (key == KeyEvent.VK_UP && dy < 0)
            dy = 0;
        if (key == KeyEvent.VK_DOWN && dy > 0)
            dy = 0;
    }

    public int getLastDx() {
        return lastDx;
    }

    public int getLastDy() {
        return lastDy;
    }
}
