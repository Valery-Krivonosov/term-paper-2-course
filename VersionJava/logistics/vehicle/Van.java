package logistics.vehicle;

import logistics.Assignable;
import logistics.cargo.Cargo;
import logistics.exception.NoAvailableVehicleException;


public final class Van extends BaseVehicle implements Assignable {
    private double volume;

    public Van(String plateNumber, double capacity, int year, double volume) {
        super(plateNumber, capacity, year);
        this.volume = volume;
        System.out.println("[Van] constructor: " + getType() + " id=" + getId());
    }

    public Van(Van other) {
        super(other);
        this.volume = other.volume;
        System.out.println("[Van] copy constructor: id=" + getId());
    }

    @Override
    public String getType() {
        return "Фургон";
    }

    @Override
    public boolean passInspection() {
        if (getState() == State.IN_REPAIR) return false;
        return (year >= 2015) && (volume > 5.5);
    }

    @Override
    public String describe() {
        return "Фургон, Госномер: " + getPlateNumber() +
               ", Тоннаж: " + getCapacity() + "т, " +
               "Год: " + year + ", " +
               "Объем: " + volume + " кубических метров, " +
               "Состояние: " + (getState() == State.IN_REPAIR ? "В ремонте" : "Готов к работе");
    }

    @Override
    public BaseVehicle cloneVehicle() {
        return new Van(this);
    }

    @Override 
    public String getKind() {
        return "фургон";
    }

    @Override
    public boolean canTake(Cargo cargo) {
        return getState() == State.AVAILABLE
            && cargo.getWeightKg() <= getCapacity() * 1000.0;
    }

    @Override
    public void assignTo(long orderId) {
        if (getState() != State.AVAILABLE) {
            throw new NoAvailableVehicleException("фургон " + getPlateNumber() + " занят");
        }
        
        setState(State.ON_TRIP);
        System.out.println("[Van] " + getPlateNumber() + " назначен на заказ id=" + orderId);
    }

    @Override 
    public void completeTrip() { 
        setState(State.AVAILABLE); 
    }
    
    @Override 
    public boolean isAvailable() { 
        return getState() == State.AVAILABLE; 
    }
}
