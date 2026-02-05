import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;

public class inicializar {
    private List<Publicacao> publicacoes;

    public inicializar() {
        publicacoes = new ArrayList<Publicacao>();
        JFrame janelaInicio = new JFrame("Controle bibliotecário");
        janelaInicio.setSize(200,100);

        JButton botaoRevistas = new JButton("Revistas");
        JButton botaoLivros = new JButton("Livros");

        JPanel painelInicio = new JPanel();
        painelInicio.add(botaoRevistas);
        painelInicio.add(botaoLivros);
        janelaInicio.getContentPane().add(painelInicio);

        botaoRevistas.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                abrirRevista();
                janelaInicio.setVisible(false);
            }
        });

        botaoLivros.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                abrirLivro();
                janelaInicio.setVisible(false);
            }
        });

        janelaInicio.setVisible(true);
    }

    public void abrirLivro() {
        JFrame janelaLivro = new JFrame("Livros");
        janelaLivro.setSize(250, 230);

        JTextField campoTitulo = new JTextField(20);
        JLabel labelTitulo = new JLabel("Título:");
        JLabel labelAutor = new JLabel("Autor:");
        JTextField campoAutor = new JTextField(20);
        JTextField campoAno = new JTextField(5);
        JLabel labelAno = new JLabel("Ano:");
        JButton botaoIncluir = new JButton("Incluir");
        JButton botaoRevistas = new JButton("Revistas");
        JButton botaoListagem = new JButton("Listagem");

        JPanel painelLivros = new JPanel();
        painelLivros.add(labelTitulo);
        painelLivros.add(campoTitulo);
        painelLivros.add(labelAutor);
        painelLivros.add(campoAutor);
        painelLivros.add(labelAno);
        painelLivros.add(campoAno);
        painelLivros.add(botaoIncluir);
        painelLivros.add(botaoRevistas);
        painelLivros.add(botaoListagem);
        janelaLivro.getContentPane().add(painelLivros);

        botaoIncluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String titulo = campoTitulo.getText();
                String autor = campoAutor.getText();
                String ano = campoAno.getText();

                publicacoes.add(new Livro(titulo, ano, autor));
                JOptionPane.showMessageDialog(janelaLivro, "Livro incluído com sucesso!");
                campoTitulo.setText("");
                campoAutor.setText("");
                campoAno.setText("");
            }
        });

        botaoListagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Listagem();
            }
        });

        botaoRevistas.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                abrirRevista();
                janelaLivro.setVisible(false);
            }
        });

        janelaLivro.setVisible(true);
    }

    private void Listagem() {
        JFrame janelaListagem = new JFrame("Listagem");
        janelaListagem.setSize(400, 300);
        JTextArea listaTxtArea = new JTextArea();
        listaTxtArea.setEditable(false);

        for (Publicacao p : publicacoes) {
            listaTxtArea.append(p.toString() + "\n");
        }

        JScrollPane listaScroll = new JScrollPane(listaTxtArea);
        janelaListagem.add(listaScroll);

        janelaListagem.setVisible(true);
    }

    public void abrirRevista() {
        JFrame janelaRevista = new JFrame("Revistas");
        janelaRevista.setSize(250, 230);

        JTextField campoTitulo = new JTextField(20);
        JLabel labelTitulo = new JLabel("Título:");
        JLabel labelOrg = new JLabel("Org.:");
        JLabel labelVol = new JLabel("Vol.:");
        JLabel labelNro = new JLabel("Nro.:");
        JTextField campoOrg = new JTextField(20);
        JTextField campoVol = new JTextField(2);
        JTextField campoNro = new JTextField(2);
        JTextField campoAno = new JTextField(5);
        JLabel labelAno = new JLabel("Ano:");
        JButton botaoIncluir = new JButton("Incluir");
        JButton botaoLivros = new JButton("Livros");
        JButton botaoListagem = new JButton("Listagem");

        JPanel painelRevista = new JPanel();
        painelRevista.add(labelTitulo);
        painelRevista.add(campoTitulo);
        painelRevista.add(labelOrg);
        painelRevista.add(campoOrg);
        painelRevista.add(labelVol);
        painelRevista.add(campoVol);
        painelRevista.add(labelNro);
        painelRevista.add(campoNro);
        painelRevista.add(labelAno);
        painelRevista.add(campoAno);
        painelRevista.add(botaoIncluir);
        painelRevista.add(botaoLivros);
        painelRevista.add(botaoListagem);
        janelaRevista.getContentPane().add(painelRevista);

        botaoListagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Listagem();
            }
        });

        botaoIncluir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String titulo = campoTitulo.getText();
                String org = campoOrg.getText();
                String ano = campoAno.getText();
                String nro = campoNro.getText();
                String vol = campoVol.getText();

                publicacoes.add(new Revista(titulo, ano, org, vol, nro));
                JOptionPane.showMessageDialog(janelaRevista, "Revista incluída com sucesso!");
                campoTitulo.setText("");
                campoOrg.setText("");
                campoAno.setText("");
                campoVol.setText("");
                campoNro.setText("");
            }
        });

        botaoLivros.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                abrirLivro();
                janelaRevista.setVisible(false);
            }
        });

        janelaRevista.setVisible(true);
    }

    public static void main(String[] args) {
        new inicializar();
    }
}
