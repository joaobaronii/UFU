package freezemonsters.sprite;

import spriteframework.sprite.BadSprite;
import spriteframework.sprite.BadnessBoxSprite;
import javax.swing.*;
import java.awt.*;
import java.util.LinkedList;
import java.util.Random;

public class Monster extends BadnessBoxSprite {
    private Slime slime;
    private boolean frozen = false;
    private int type;

    public Monster(int x, int y, int type) {
        this.type = type;
        initMonster(x, y);
        setRandomDirection();
    }

    private void initMonster(int x, int y) {
        this.x = x;
        this.y = y;
        slime = new Slime(x, y);
        String monsterPath = "src/images/monster" + type + ".png";
        ImageIcon ii = new ImageIcon(monsterPath);
        Image monsterImg = ii.getImage().getScaledInstance(30, 30, Image.SCALE_DEFAULT);
        setImage(monsterImg);
    }

    public Slime getSlime() {
        return slime;
    }

    @Override
    public LinkedList<BadSprite> getBadnesses() {
        LinkedList<BadSprite> aSlime = new LinkedList<>();
        aSlime.add(slime);
        return aSlime;
    }

    public void moveRandomly() {
        if (!frozen) {
            Random generate = new Random();
            if (generate.nextInt(10) == 0) {
                setRandomDirection();
            }
            x += dx;
            y += dy;
        }
    }

    private void setRandomDirection() {
        Random generate = new Random();
        dx = generate.nextInt(3) - 1;
        dy = generate.nextInt(3) - 1;
        if (dx == 0 && dy == 0) {
            dx = generate.nextBoolean() ? 1 : -1;
        }
    }


    public void freeze() {
        String frozenPath = "src/images/monster" + type + "bg.png";
        ImageIcon ii = new ImageIcon(frozenPath);
        Image frozenImg = ii.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);
        setImage(frozenImg);
        frozen = true;
    }

    public boolean isFrozen() {
        return frozen;
    }

    public int getType() {
        return type;
    }
}
