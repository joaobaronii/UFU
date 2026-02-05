import java.util.List;

public class TotalSumCalculator {

    private int totalSum = 0;

    public void calculateTotal(List<Object> elements) {
        for (Object el : elements) {
            if (el instanceof TwoElement) {
                int sum = ((TwoElement) el).sum();
                System.out.println("Adding " + ((TwoElement) el).a + "+" + ((TwoElement) el).b + "=" + sum + " to total");
                totalSum += sum;
            } else if (el instanceof ThreeElement) {
                int sum = ((ThreeElement) el).sum();
                System.out.println("Adding " + ((ThreeElement) el).a + "+" + ((ThreeElement) el).b + "+" + ((ThreeElement) el).c + "=" + sum + " to total");
                totalSum += sum;
            }
        }
    }

    public int getTotalSum() {
        return totalSum;
    }
}
