package logistics.exception;

public class NoAvailableVehicleException extends LogisticsException {
    public NoAvailableVehicleException(String reason) {
        super("нет доступного транспорта: " + reason);
    }
}
