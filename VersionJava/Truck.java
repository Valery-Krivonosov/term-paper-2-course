public class Truck extends BaseVehicle {
    private int axles;
    private int year;

    public Truck(String plateNumber, double capacity, int axles, int year) {
        super(plateNumber, capacity);
        this.axles = axles;
        this.year = year;
        System.out.println("[Truck] constructor: " + getType() + " id=" + getId());
    }

    public Truck(Truck other) {
        super(other);
        this.axles = other.axles;
        this.year = other.year;
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
    public BaseVehicle cloneVehicle() {
        return new Truck(this);
    }
}