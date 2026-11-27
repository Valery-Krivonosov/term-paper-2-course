package logistics.vehicle;

import logistics.Assignable;
import logistics.cargo.Cargo;
import logistics.policy.CargoPolicy;
import logistics.exception.NoAvailableVehicleException;


public class Truck extends BaseVehicle implements Assignable {
    private int axles;
    private CargoPolicy policy;

    public Truck(String plateNumber, double capacity, int axles, int year, CargoPolicy policy) {
        super(plateNumber, capacity, year);
        this.axles = axles;
        this.policy = policy;
        System.out.println("[Truck] constructor: " + getType() + " id=" + getId());
    }

    public Truck(Truck other) {
        super(other);
        this.axles = other.axles;
        this.policy = other.policy;
        System.out.println("[Truck] copy constructor: id=" + getId());
    }

    @Override
    public String getType() {
        return "Грузовик";
    }

    @Override
    public boolean passInspection() {
        if (getState() == State.IN_REPAIR) return false;
        return (year >= 2015) && (axles >= 3);
    }

    @Override
    public String describe() {
        return super.describe() + ", Осей: " + axles + ", Год: " + year;
    }

    @Override 
    public String getKind() {
        return "грузовик";
    }

    @Override
    public BaseVehicle cloneVehicle() {
        return new Truck(this);
    }

    @Override
    public boolean canTake(Cargo cargo) {
        return getState() == State.AVAILABLE
                && policy != null
                && policy.accepts(cargo, getCapacity());
    }

    @Override
    public void assignTo(long orderId) {
        if (getState() != State.AVAILABLE) {
            throw new NoAvailableVehicleException("грузовик " + getPlateNumber() + " занят");
        }
        setState(State.ON_TRIP);
        System.out.println("[Truck] " + getPlateNumber() + " назначен на заказ id=" + orderId);
    }

    @Override
    public void completeTrip() {
        setState(State.AVAILABLE);
    }

    @Override 
    public boolean isAvailable() {
        return getState() == State.AVAILABLE;
    }

    public void setPolicy(CargoPolicy policy) {
        this.policy = policy;
        System.out.println("[Truck] правило допуска груза изменено");
    }
}