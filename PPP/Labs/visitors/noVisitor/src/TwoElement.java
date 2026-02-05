public class TwoElement {
    int a;
    int b;

    public TwoElement(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public int sum() {
        return a + b;
    }

    public void printSum() {
        System.out.println(a + "+" + b + "=" + sum());
    }
}
