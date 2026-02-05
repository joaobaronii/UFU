public class Operacao extends ExpressaoAritmetica {
    private ExpressaoAritmetica op1;
    private ExpressaoAritmetica op2;
    private char operador;

    public Operacao(ExpressaoAritmetica op1, ExpressaoAritmetica op2, char operador) {
        this.op1 = op1;
        this.op2 = op2;
        this.operador = operador;
    }

    @Override
    public float getResultado() {
        float v1 = op1.getResultado();
        float v2 = op2.getResultado();
        float resultado;
        switch (operador) {
            case '+':
                resultado = v1 + v2;
                break;
            case '-':
                resultado = v1 - v2;
                break;
            case '*':
                resultado = v1 * v2;
                break;
            case '/':
                if(v2==0)
                    throw new ArithmeticException("divisao por zero");
                resultado = v1 / v2;
                break;
            default:
                throw new IllegalArgumentException("operador invalido: " + operador);
        }
    return resultado;
    }
}
