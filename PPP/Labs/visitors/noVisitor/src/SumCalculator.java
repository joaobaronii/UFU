import java.util.List;

public class SumCalculator {

    public void printSums(List<Object> elements) {
        for (Object el : elements) {
            if (el instanceof TwoElement) {
                ((TwoElement) el).printSum();
            } else if (el instanceof ThreeElement) {
                ((ThreeElement) el).printSum();
            }
        }
    }
}
