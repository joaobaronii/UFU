import java.util.List;

public class TotalMultiplicationVisitor implements NumberVisitor{

    int totalMultiplication = 0;

    @Override
    public void visit(TwoElement twoElement) {
        int multiplication = twoElement.a * twoElement.b;
        System.out.println("Adding " + twoElement.a + "*" + twoElement.b + "=" + multiplication + " to total");
        totalMultiplication += multiplication;
    }

    @Override
    public void visit(ThreeElement threeElement) {
        int multiplication = threeElement.a * threeElement.b * threeElement.c;
        System.out.println("Adding " + threeElement.a + "*" + threeElement.b + "*" + threeElement.c + "=" + multiplication + " to total");
        totalMultiplication += multiplication;
    }

    @Override
    public void visit(List<NumberElement> elementList) {
        for (NumberElement ne : elementList) {
            ne.accept(this);
        }
    }

    public int getTotalSum() {
        return totalMultiplication;
    }
}
