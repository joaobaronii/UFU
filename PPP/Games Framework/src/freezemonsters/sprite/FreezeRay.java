package freezemonsters.sprite;

import spriteframework.sprite.Sprite;
import javax.swing.ImageIcon;
import java.awt.*;


public class FreezeRay extends Sprite {
    private int dx;
    private int dy;

    public FreezeRay(){
    }

    public FreezeRay(int x, int y, int dx, int dy) {
        this.dx = dx;
        this.dy = dy;
        initRay(x,y);
    }

    private void initRay(int x, int y) {
        ImageIcon ii = new ImageIcon("src/images/ray.png");
        Image rayImage = ii.getImage().getScaledInstance(20, 20, Image.SCALE_SMOOTH);
        setImage(rayImage);
        setX(x);
        setY(y);
    }

    public void move()
    {
        x += dx;
        y += dy;
    }
}
