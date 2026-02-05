import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class JanelaRevista extends JanelaPublicacao {
    private JTextField campoOrg;
    private JTextField campoVol;
    private JTextField  campoNro;

    public JanelaRevista(List<Publicacao> publicacoes) {
        super("Revistas", publicacoes);
        campoOrg = new JTextField(20);
        campoVol = new JTextField(2);
        campoNro = new JTextField(2);

        JPanel painel = (JPanel) janela.getContentPane().getComponent(0);
        painel.add(new JLabel("Org.:"));
        painel.add(campoOrg);
        painel.add(new JLabel("Vol.:"));
        painel.add(campoVol);
        painel.add(new JLabel("Nro.:"));
        painel.add(campoNro);

        botaoIncluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                incluirRevista();
            }
        });
    }

    private void incluirRevista() {
        publicacoes.add(new Revista(campoTitulo.getText(), campoAno.getText(), campoOrg.getText(), campoVol.getText(), campoNro.getText()));
        JOptionPane.showMessageDialog(janela, "Revista incluída com sucesso!");
        campoTitulo.setText("");
        campoAno.setText("");
        campoOrg.setText("");
        campoVol.setText("");
        campoNro.setText("");
    }

}

