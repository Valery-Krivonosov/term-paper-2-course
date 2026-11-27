package logistics.vehicle;

public class RepairVehicle extends BaseVehicle {
    public RepairVehicle(String plateNumber, double capacity, int year) {
        super(plateNumber, capacity, year);
        setState(State.IN_REPAIR);
        System.out.println("[RepairVehicle] constructor: id=" + getId());
    }

    @Override 
    public String getType() {
        return "Ремонтная единица";
    }

    @Override 
    public boolean passInspection() {
        return false;
    }

    @Override
    public String describe() {
        return "Ремонтная единица, Госномер: " + getPlateNumber()
                + " (на рейс не назначается)";
    }

    @Override 
    public String getKind() { 
        return "ремонтная единица"; 
    }

    @Override
    public BaseVehicle cloneVehicle() {
        return new RepairVehicle(getPlateNumber(), getCapacity(), getYear());
    }
}
