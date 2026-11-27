package logistics.exception;


public class OverLoadException extends LogisticsException {
    public OverLoadException(double weightKg, double capacityTons) {
        super("вес груза " + weightKg + " кг превышает грузоподъёмность " + capacityTons + " т");
    }
}
