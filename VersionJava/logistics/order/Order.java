package logistics.order;

import logistics.cargo.Cargo;
import logistics.driver.Driver;
import logistics.exception.DriverUnavailableException;
import logistics.exception.InvalidOrderStateException;


public class Order {
    public enum State {
        CREATED,
        ASSIGNED,
        IN_TRANSIST,
        DELIVERED,
        CANCALED
    }

    private final long id;
    private boolean urgent = false;
    private State state = State.CREATED;
    
    private final Cargo cargo;
    private Driver driver;

    public Order(long id, boolean urgent, double weightKg, String destination) {
        this.id = id;
        this.urgent = urgent;
        this.cargo = new Cargo(weightKg, destination);
    }

    public long getId() {
        return id;
    }

    public boolean isUrgent() {
        return urgent;
    }

    public State getState() {
        return state;
    }

    public Driver getDriver() {
        return driver;
    }

    public Cargo getCargo() {
        return cargo;
    }

    private String stateToStr() {
        return switch (state) {
            case CREATED -> "созан";
            case ASSIGNED -> "назначен";
            case IN_TRANSIST -> "в пути";
            case DELIVERED -> "доставлен";
            case CANCALED -> "отменен";
        };
    }

    public void assignDriver(Driver driver) {
        if (driver == null) {
            throw new IllegalArgumentException("передан пустой водитель");
        }

        if (driver.getState() == Driver.State.ON_TRIP) {
            throw new DriverUnavailableException(driver.getFullName());
        }

        if (driver.getState() == Driver.State.RESTING) {
            throw new DriverUnavailableException(driver.getFullName());
        }

        if (this.driver != null && this.driver != driver) {
            releaseDriver();
        }

        this.driver = driver;
        state = State.ASSIGNED;
        driver.setState(Driver.State.ON_TRIP);

       System.out.println("[Order] заказ id=" + id +
                    " назначен на водителя '" + driver.getFullName() + "'");
    }

    public void releaseDriver() {
        if (driver == null) {
            return;
        }

        driver.finishTrip();
        System.out.println("[Order] заказ id=" + id +
                    " освободил водителя '" + driver.getFullName() + "'");
        driver = null;

        if (state == State.IN_TRANSIST || state == State.ASSIGNED) {
            state = State.CREATED;
        }
    }

    public void startTransit() {
        if (driver == null || state != State.ASSIGNED) {
            throw new InvalidOrderStateException(
                "заказ id=" + id + " не может перейти 'в пути' без назначенного водителя"
            );
        }

        state = State.IN_TRANSIST;
        System.out.println("[Order] заказ id=" + id + " в пути");
    }

    public void deliver() {
        if (state != State.IN_TRANSIST) {
            throw new InvalidOrderStateException(
                 "заказ id=" + id + " не в пути, нельзя доставить"
            );
        }

        state = State.DELIVERED;

        if (driver != null) {
            driver.finishTrip();
            System.out.println("[Order] заказ id=" + id +
                        " доставлен, водитель '" + driver.getFullName() + "' освобождён");
            driver = null;
        }
    }

    public void cancel() {
        if (state == State.DELIVERED) {
            throw new InvalidOrderStateException(
                "заказ id=" + id + " уже доставлен, нельзя отменить"
            );    
        }

        if (state == State.CANCALED) {
            throw new InvalidOrderStateException("заказ id=" + id + " уже отменён");
        }

        if (driver != null) {
            driver.finishTrip();
            System.out.println("[Order] заказ id=" + id +
                        " отменён, водитель '" + driver.getFullName() + "' освобождён");
            driver = null;
        } else {
            System.out.println("[Order] заказ id=" + id + " отменён");
        }

        state = State.CANCALED;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Заказ id=").append(id).append(", срочность=")
        .append(urgent ? "срочный" : "обычный").append(", состояние=")
        .append(stateToStr()).append("\n  ").append(cargo);
        sb.append("\n  ");
        
        if (driver != null) {
            sb.append(driver);
        } else {
            sb.append("Водитель: не назначен");
        }

        return sb.toString();
    }
}
