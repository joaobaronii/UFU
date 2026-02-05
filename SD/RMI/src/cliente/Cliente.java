package cliente;

import java.rmi.Naming;
import java.util.Scanner;

import servidor.ServicoDeVotacao;

public class Cliente {
    public static void main(String[] args) {
        try {
            ServicoDeVotacao servicoDeVotacao = (ServicoDeVotacao) Naming.lookup("rmi://localhost/ServicoDeVotacao");

            Scanner scanner = new Scanner(System.in);
            System.out.print("Digite o nome do eleitor: ");
            String eleitor = scanner.nextLine();

            System.out.println("Opcoes de candidatos:");
            System.out.println("13 - Lula");
            System.out.println("22 - Bolsonaro");

            System.out.print("Digite o numero do candidato: ");
            String candidato = scanner.nextLine();

            if(candidato.equals("13") || candidato.equals("22")){
                servicoDeVotacao.votar(eleitor, candidato);
                System.out.println("Voto registrado com sucesso.");
            } else {
                System.out.println("Candidato invalido.");
            }
        } catch (Exception e) {
            System.err.println("Erro: " + e.toString());
            e.printStackTrace();
        }
    }
}
