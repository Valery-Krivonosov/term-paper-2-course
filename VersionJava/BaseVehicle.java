import java.util.Objects;

public abstract class BaseVehicle {
    public enum State {
        AVAILABLE, ON_TRIP, IN_REPAIR
    }

    private static int lightCounter = 1000;
    private static int heavyCounter = 5000;

    private int id;
    private State state;
    private String docs; 

    protected String plateNumber;
    protected double capacity;


    public BaseVehicle(String plateNumber, double capacity) {
        this.plateNumber = plateNumber;
        this.capacity = capacity;
        this.id = generateId(capacity);
        this.state = State.AVAILABLE;
        this.docs = "Пусто";
        System.out.println("[BaseVehicle] constructor: id=" + id);
    }

    public BaseVehicle(BaseVehicle other) {
        this.plateNumber = other.plateNumber;
        this.capacity = other.capacity;
        this.id = other.id;
        this.state = other.state;
        this.docs = other.docs; 
        System.out.println("[BaseVehicle] copy constructor: id=" + id);
    }

    private static int generateId(double capacity) {
        if (capacity > 5.0) {
            return ++heavyCounter;
        }
        return ++lightCounter;
    }

    protected String header() {
        String stateStr = switch (state) {
            case AVAILABLE -> "Свободен";
            case ON_TRIP -> "В рейсе";
            case IN_REPAIR -> "В ремонте";
        };
        return "ID: " + id + ", Госномер: " + plateNumber +
               ", Тоннаж: " + capacity + "т, Состояние: " + stateStr;
    }

    public abstract String getType();
    public abstract boolean passInspection();
    public abstract BaseVehicle cloneVehicle();

    public String describe() {
        return header();
    }

    public int getId() { 
        return id; 
    }

    public String getPlateNumber() { 
        return plateNumber; 
    }
    
    public double getCapacity() { 
        return capacity; 
    }
    
    public State getState() { 
        return state; 
    }
    
    public void setState(State state) { 
        this.state = state; 
    }

    public String getDocs() { 
        return docs; 
    }
    
    public void setDocs(String doc) { 
        this.docs = doc; 
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BaseVehicle that = (BaseVehicle) o;
        return Objects.equals(plateNumber, that.plateNumber);
    }

    @Override
    public int hashCode() {
        return Objects.hash(plateNumber);
    }
}