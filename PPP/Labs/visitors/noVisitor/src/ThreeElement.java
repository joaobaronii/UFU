public class ThreeElement {
    int a;
    int b;
    int c;

    public ThreeElement(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public int sum() {
        return a + b + c;
    }

    public void printSum() {
        System.out.println(a + "+" + b + "+" + c + "=" + sum());
    }
}
