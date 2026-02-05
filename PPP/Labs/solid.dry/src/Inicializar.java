import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

public class Inicializar {
    private List<Publicacao> publicacoes;

    public Inicializar() {
        publicacoes = new ArrayList<>();
        JFrame janelaInicio = new JFrame("Controle bibliotecário");
        janelaInicio.setSize(200, 100);

        JButton botaoLivros = new JButton("Livros");
        JButton botaoRevistas = new JButton("Revistas");
        JButton botaoVideos = new JButton("Videos");

        JPanel painelInicio = new JPanel();
        painelInicio.add(botaoLivros);
        painelInicio.add(botaoRevistas);
        painelInicio.add(botaoVideos);
        janelaInicio.getContentPane().add(painelInicio);

        botaoLivros.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                new JanelaLivro(publicacoes).exibir();
            }
        });
        botaoRevistas.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                new JanelaRevista(publicacoes).exibir();
            }
        });
        botaoVideos.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                new JanelaVideo(publicacoes).exibir();
            }
        });

        janelaInicio.setVisible(true);
    }

    public static void main(String[] args) {
        new Inicializar();
    }
}
