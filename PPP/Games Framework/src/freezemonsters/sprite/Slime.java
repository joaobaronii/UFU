package freezemonsters.sprite;

import spriteframework.sprite.BadSprite;
import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Slime extends BadSprite {
    private boolean destroyed;

    public Slime(int x, int y)
    {
        initSlime(x, y);
    }

    private void initSlime(int x, int y)
    {
        setDestroyed(true);
        this.x = x;
        this.y = y;
        ImageIcon ii = new ImageIcon("src/images/gosma.png");
        Image slimeImage = ii.getImage().getScaledInstance(15, 15, Image.SCALE_SMOOTH);
        setImage(slimeImage);
    }

    public void setDestroyed(boolean destroyed)
    {
        this.destroyed = destroyed;
    }

    public boolean isDestroyed()
    {
        return destroyed;
    }

    public void setDirection()
    {
        Random generator = new Random();
        dx = generator.nextInt(3) - 1;
        dy = generator.nextInt(3) - 1;
        while (dx==0 && dy==0){
            dx = generator.nextInt(3) - 1;
            dy = generator.nextInt(3) - 1;
        }
    }

    public void move(){
        x += dx;
        y += dy;
    }
}
