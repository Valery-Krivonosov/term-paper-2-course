package logistics.exception;

public class NegativeWeightException extends LogisticsException {
    public NegativeWeightException(double weightKg) {
        super("Вес не может быть отрицательным: " + weightKg);
    }
}
