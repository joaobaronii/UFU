package cliente;

import java.util.Map;
import java.rmi.Naming;

import servidor.ServicoDeResultados;

public class ConsultaResultado {
    public static void main(String[] args) {
        try {
            ServicoDeResultados servicoDeResultados = (ServicoDeResultados) Naming.lookup("rmi://localhost/ServicoDeResultados");

            Map<String, Integer> resultados = servicoDeResultados.getResultados();

            System.out.println("Resultados da votação:");
            for (Map.Entry<String, Integer> entry : resultados.entrySet()) {
                System.out.println(entry.getKey() + ": " + entry.getValue() + " votos");
            }
        } catch (Exception e) {
            System.err.println("Erro: " + e.toString());
            e.printStackTrace();
        }
    }
}
