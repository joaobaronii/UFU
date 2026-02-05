package freezemonsters;

import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.util.Random;
import javax.swing.ImageIcon;
import spriteframework.AbstractBoard;
import spriteframework.sprite.BadSprite;
import spriteframework.sprite.Player;
import freezemonsters.sprite.*;

public class FreezeMonstersBoard extends AbstractBoard {
    private FreezeRay ray;
    private int frozenMonsters = 0;

    protected void createBadSprites() {
        Random random = new Random();
        for (int i = 0; i < Commons.NUMBER_OF_MONSTERS_TO_FREEZE; i++) {
            int type = random.nextInt(Commons.NUMBER_OF_MONSTER_TYPES) + 1;
            Monster monster = new Monster(
                    random.nextInt(Commons.BOARD_WIDTH - Commons.MONSTER_WIDTH),
                    random.nextInt(Commons.GROUND - Commons.MONSTER_HEIGHT),
                    type
            );
            badSprites.add(monster);
        }
    }

    protected void createOtherSprites() {
        ray = new FreezeRay();
    }

    @Override
    protected Player createPlayer() {
        return new Woody();
    }

    private void drawRay(Graphics g) {
        if (ray.isVisible()) {
            g.drawImage(ray.getImage(), ray.getX(), ray.getY(), this);
        }
    }

    @Override
    protected void drawOtherSprites(Graphics g) {
        drawRay(g);
    }

    protected void processOtherSprites(Player player, KeyEvent e) {
        int x = player.getX();
        int y = player.getY();
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_SPACE && inGame) {
            if (!ray.isVisible()) {
                Woody woody = (Woody) player;
                ray = new FreezeRay(x, y, woody.getLastDx(), woody.getLastDy());
            }
        }
    }

    protected void update() {
        if (frozenMonsters == Commons.NUMBER_OF_MONSTERS_TO_FREEZE) {
            inGame = false;
            timer.stop();
            message = "Game won!";
        }

        for (Player player : players)
            player.act();

        if (ray.isVisible()) {
            int rayX = ray.getX();
            int rayY = ray.getY();

            for (BadSprite monster : badSprites) {
                int monsterX = monster.getX();
                int monsterY = monster.getY();
                if (monster.isVisible() && ray.isVisible()) {
                    if (rayX >= monsterX
                            && rayX <= (monsterX + Commons.MONSTER_WIDTH)
                            && rayY >= monsterY
                            && rayY <= (monsterY + Commons.MONSTER_HEIGHT)) {
                        Monster m = (Monster) monster;
                        if (!m.isFrozen()) {
                            m.freeze();
                            frozenMonsters++;
                        }
                        ray.die();
                    }
                }
            }

            ray.move();
            if (ray.getX() <= 0 || ray.getX() >= Commons.BOARD_WIDTH - 5 ||
                    ray.getY() <= 0 || ray.getY() >= Commons.GROUND - 5) {
                ray.die();
            }
        }

        for (BadSprite monster : badSprites) {
            if (monster.isVisible()) {
                ((Monster) monster).moveRandomly();
                int x = monster.getX();
                int y = monster.getY();
                if (x <= 0) monster.setX(0);
                if (x >= Commons.BOARD_WIDTH - Commons.MONSTER_WIDTH) {
                    monster.setX(Commons.BOARD_WIDTH - Commons.MONSTER_WIDTH);
                }
                if (y <= 0) monster.setY(0);
                if (y >= Commons.GROUND - Commons.MONSTER_HEIGHT) {
                    monster.setY(Commons.GROUND - Commons.MONSTER_HEIGHT);
                }
            }
        }

        updateOtherSprites();
    }

    protected void updateOtherSprites() {
        Random generator = new Random();
        for (BadSprite monster : badSprites) {
            int slimeChance = generator.nextInt(15);
            Slime slime = ((Monster) monster).getSlime();
            if (slimeChance == Commons.CHANCE && monster.isVisible() && slime.isDestroyed()
                    && !((Monster) monster).isFrozen()) {
                slime.setDestroyed(false);
                slime.setX(monster.getX());
                slime.setY(monster.getY());
                slime.setDirection();
            }

            int slimeX = slime.getX();
            int slimeY = slime.getY();
            int playerX = players.get(0).getX();
            int playerY = players.get(0).getY();

            if (players.get(0).isVisible() && !slime.isDestroyed()) {
                if (slimeX >= playerX
                        && slimeX <= (playerX + Commons.PLAYER_WIDTH)
                        && slimeY >= playerY
                        && slimeY <= (playerY + Commons.PLAYER_HEIGHT)) {
                    ImageIcon ii = new ImageIcon("src/images/explosion.png");
                    players.get(0).setImage(ii.getImage());
                    players.get(0).setDying(true);
                    slime.setDestroyed(true);
                }
            }

            if (!slime.isDestroyed() && ray.isVisible()) {
                if (slimeX >= ray.getX()
                        && slimeX <= (ray.getX() + 5)
                        && slimeY >= ray.getY()
                        && slimeY <= (ray.getY() + 5)) {
                    slime.setDestroyed(true);
                    ray.die();
                }
            }

            if (!slime.isDestroyed()) {
                for (BadSprite otherMonster : badSprites) {
                    if (otherMonster != monster && otherMonster.isVisible()) {
                        int monsterX = otherMonster.getX();
                        int monsterY = otherMonster.getY();
                        if (slimeX >= monsterX
                                && slimeX <= (monsterX + Commons.MONSTER_WIDTH)
                                && slimeY >= monsterY
                                && slimeY <= (monsterY + Commons.MONSTER_HEIGHT)) {
                            slime.setDestroyed(true);
                        }
                    }
                }
            }

            if (!slime.isDestroyed()) {
                slime.move();
                if (slime.getX() <= 0 || slime.getX() >= Commons.BOARD_WIDTH - Commons.GUM_WIDTH ||
                        slime.getY() <= 0 || slime.getY() >= Commons.GROUND - Commons.GUM_HEIGHT) {
                    slime.setDestroyed(true);
                }
            }
        }
    }
}