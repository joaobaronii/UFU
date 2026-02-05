public class OperadorNumerico extends ExpressaoAritmetica {
    private float valor;

    public OperadorNumerico(int valor) {
        this.valor = valor;
    }

    @Override
    public float getResultado() {
        return valor;
    }
}
