import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

class JanelaVideo extends JanelaPublicacao {
    private JTextField campoAutor;
    private JTextField campoDuracao;

    public JanelaVideo(List<Publicacao> publicacoes) {
        super("Video", publicacoes);
        campoAutor = new JTextField(20);
        campoDuracao = new JTextField(20);

        JPanel painel = (JPanel) janela.getContentPane().getComponent(0);
        painel.add(new JLabel("Autor:"));
        painel.add(campoAutor);
        painel.add(new JLabel("Duração:"));
        painel.add(campoDuracao);

        botaoIncluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                incluirVideo();
            }
        });
    }

    private void incluirVideo() {
        publicacoes.add(new Video(campoTitulo.getText(), campoAno.getText(), campoAutor.getText(), campoDuracao.getText()));
        JOptionPane.showMessageDialog(janela, "Video incluído com sucesso!");
        campoTitulo.setText("");
        campoAno.setText("");
        campoAutor.setText("");
        campoDuracao.setText("");
    }
}

