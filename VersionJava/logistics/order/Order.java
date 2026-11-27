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

    public boolean assignDriver(Driver driver) {
        if (driver == null) {
            System.out.println("[Order] отказ: водителя нет");
            return false;
        }

        if (driver.getState() == Driver.State.ON_TRIP) {
            System.out.println("[Order] отказ: водитель '" + driver.getFullName() +
                        "' уже занят другим заказом");
            return false;
        }

        if (driver.getState() == Driver.State.RESTING) {
            System.out.println("[Order] отказ: водитель '" + driver.getFullName() +
                        "' отдыхает, нельзя назначить на заказ id=" + id);
            return false;
        }

        if (this.driver != null && this.driver != driver) {
            releaseDriver();
        }

        this.driver = driver;
        state = State.ASSIGNED;
        driver.setState(Driver.State.ON_TRIP);

       System.out.println("[Order] заказ id=" + id +
                    " назначен на водителя '" + driver.getFullName() + "'");
        return true;
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

    public boolean startTransit() {
        if (driver == null || state != State.ASSIGNED) {
            System.out.println("[Order] отказ: заказ id=" + id +
                        " не может перейти 'в пути' без назначенного водителя");
            return false;
        }

        state = State.IN_TRANSIST;
        System.out.println("[Order] заказ id=" + id + " в пути");

        return true;
    }

    public boolean deliver() {
        if (state != State.IN_TRANSIST) {
            System.out.println("[Order] отказ: заказ id=" + id +
                        " не в пути, нельзя доставить");
            return false;
        }

        state = State.DELIVERED;

        if (driver != null) {
            driver.finishTrip();
            System.out.println("[Order] заказ id=" + id +
                        " доставлен, водитель '" + driver.getFullName() + "' освобождён");
            driver = null;
        }

        return true;
    }

    public boolean cancel() {
        if (state == State.DELIVERED) {
            System.out.println("[Order] отказ: заказ id=" + id +
                        " уже доставлен, нельзя отменить");
            return false;
        }

        if (state == State.CANCALED) {
            System.out.println("[Order] отказ: заказ id=" + id + " уже отменён");
            return false;
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
        return true;
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
