public class TesteComposite {
    public static void main(String[] args) {
        ExpressaoAritmetica a = new OperadorNumerico(0);
        System.out.println("a) " + a.getResultado());

        ExpressaoAritmetica b = new Operacao(new OperadorNumerico(1),
                new OperadorNumerico(2), '+');
        System.out.println("b) " + b.getResultado());

        ExpressaoAritmetica c = new Operacao(new OperadorNumerico(1),
                new Operacao(new OperadorNumerico(2), new OperadorNumerico(3), '+'),
                '*');
        System.out.println("c) " + c.getResultado());

        ExpressaoAritmetica d = new Operacao(
                new Operacao(new OperadorNumerico(2), new OperadorNumerico(3), '*'),
                new Operacao(
                        new OperadorNumerico(4),
                        new Operacao(
                                new OperadorNumerico(5), new OperadorNumerico(3), '-'),
                        '/'),
                '+');
        System.out.println("d) " + d.getResultado());
    }
}
