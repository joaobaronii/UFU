import java.util.List;


public class Pedido {

    private String cliente;

    private List<Double> itens;


    public Pedido(String cliente, List<Double> itens) {

        this.cliente = cliente;

        this.itens = itens;

    }


    public void processarPedido() {

        System.out.println("Processando pedido para o cliente: " + cliente);

    // Cálculo do subtotal
        double subtotal = getSubtotal();

    // Cálculo do desconto
        double desconto = getDesconto(subtotal);

    // Cálculo do imposto
        double imposto = getImposto(subtotal, desconto);

    // Cálculo do total final
        double total = getTotal(subtotal, desconto, imposto);

    // Exibição do recibo
        exibirRecibo(subtotal, desconto, imposto, total);

    }

    private static void exibirRecibo(double subtotal, double desconto, double imposto, double total) {
        System.out.println("Subtotal: R$" + subtotal);

        System.out.println("Desconto: R$" + desconto);

        System.out.println("Imposto: R$" + imposto);

        System.out.println("Total: R$" + total);
    }

    private static double getTotal(double subtotal, double desconto, double imposto) {
        return subtotal - desconto + imposto;
    }

    private static double getImposto(double subtotal, double desconto) {
        return (subtotal - desconto) * 0.08;
    }

    private static double getDesconto(double subtotal) {
        double desconto = 0;

        if (subtotal > 100) {

            desconto = subtotal * 0.1;

        }
        return desconto;
    }

    private double getSubtotal() {
        double subtotal = 0;

        for (double item : itens) {

            subtotal += item;

        }
        return subtotal;
    }

}