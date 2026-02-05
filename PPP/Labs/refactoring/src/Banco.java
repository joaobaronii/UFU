public class Cliente {
    private String nome;
    private ContaBancaria conta;

    public Cliente(String nome, ContaBancaria conta) {
        this.nome = nome;
        this.conta = conta;
    }

    public void exibirSaldoComJuros() {
        double juros = conta.calcularJuros();
        System.out.println("Cliente: " + nome);
        System.out.println("Saldo atual: R$" + conta.getSaldo());
        System.out.println("Juros aplicados: R$" + juros);
        System.out.println("Saldo final: R$" + (conta.getSaldo() + juros));
    }

}
public class ContaBancaria {
    private double saldo;
    private double taxaDeJuros;

    public ContaBancaria(double saldo, double taxaDeJuros) {
        this.saldo = saldo;
        this.taxaDeJuros = taxaDeJuros;
    }
    public double getSaldo() {
        return saldo;
    }
    public double getTaxaDeJuros() {
        return taxaDeJuros;
    }

    public double calcularJuros() {
        return getSaldo() * getTaxaDeJuros();
    }
}