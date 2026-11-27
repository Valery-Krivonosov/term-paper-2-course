package logistics.exception;

public class DriverUnavailableException extends LogisticsException {
    public DriverUnavailableException(String name) {
        super("водитель " + name + " недоступен");
    }
}
