import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

abstract class  JanelaPublicacao {
    protected JFrame janela;
    protected JTextField campoTitulo, campoAno;
    protected JButton botaoIncluir, botaoListagem;
    protected List<Publicacao> publicacoes;

    public JanelaPublicacao(String titulo, List<Publicacao> publicacoes) {
        this.publicacoes = publicacoes;
        janela = new JFrame(titulo);
        janela.setSize(300, 200);

        campoTitulo = new JTextField(20);
        campoAno = new JTextField(5);
        botaoIncluir = new JButton("Incluir");
        botaoListagem = new JButton("Listagem");

        JPanel painel = new JPanel();
        painel.add(new JLabel("Título:"));
        painel.add(campoTitulo);
        painel.add(new JLabel("Ano:"));
        painel.add(campoAno);
        painel.add(botaoIncluir);
        painel.add(botaoListagem);

        janela.getContentPane().add(painel);

        botaoListagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                listagem();
            }
        });
    }

    protected void listagem() {
        JFrame janelaListagem = new JFrame("Listagem");
        janelaListagem.setSize(400, 300);
        JTextArea listaTxtArea = new JTextArea();
        listaTxtArea.setEditable(false);

        for (Publicacao p : publicacoes) {
            listaTxtArea.append(p.toString() + "\n");
        }

        janelaListagem.add(new JScrollPane(listaTxtArea));
        janelaListagem.setVisible(true);
    }

    public void exibir() {
        janela.setVisible(true);
    }

    public void ocultar() {
        janela.setVisible(false);
    }
}
