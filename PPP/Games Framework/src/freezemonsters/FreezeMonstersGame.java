package freezemonsters;

import java.awt.EventQueue;
import spriteframework.AbstractBoard;
import spriteframework.MainFrame;

public class FreezeMonstersGame extends MainFrame {

    public FreezeMonstersGame() {
        super("Freeze Monsters");
    }

    protected AbstractBoard createBoard() {
        return new FreezeMonstersBoard();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            new FreezeMonstersGame();
        });
    }
}
