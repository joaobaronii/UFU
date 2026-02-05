import java.util.List;

public class MultiplicationVisitor implements NumberVisitor {
    public void visit(TwoElement twoElement) {
        int multiplication = twoElement.a * twoElement.b;
        System.out.println(twoElement.a + "*" + twoElement.b + "=" + multiplication);
    }

    @Override
    public void visit(ThreeElement threeElement) {
        int multiplication = threeElement.a * threeElement.b * threeElement.c;
        System.out.println(threeElement.a + "*" + threeElement.b + "*" + threeElement.c + "=" + multiplication);
    }

    @Override
    public void visit(List<NumberElement> elementList) {
        for (NumberElement ne : elementList) {
            ne.accept(this);
        }
    }
}
