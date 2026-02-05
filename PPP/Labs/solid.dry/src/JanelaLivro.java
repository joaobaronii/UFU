import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

class JanelaLivro extends JanelaPublicacao {
    private JTextField campoAutor;

    public JanelaLivro(List<Publicacao> publicacoes) {
        super("Livros", publicacoes);
        campoAutor = new JTextField(20);

        JPanel painel = (JPanel) janela.getContentPane().getComponent(0);
        painel.add(new JLabel("Autor:"));
        painel.add(campoAutor);

        botaoIncluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                incluirLivro();
            }
        });
    }

    private void incluirLivro() {
        publicacoes.add(new Livro(campoTitulo.getText(), campoAno.getText(), campoAutor.getText()));
        JOptionPane.showMessageDialog(janela, "Livro incluído com sucesso!");
        campoTitulo.setText("");
        campoAno.setText("");
        campoAutor.setText("");
    }
}

