public final class Van extends BaseVehicle {
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
}