public class Driver {
    public enum State {
        AVAILABLE,
        ON_TRIP,
        RESTING
    }

    private final long id;
    private final String fullName;
    private State state = State.AVAILABLE;

    public Driver(long id, String fullName) {
        this.id = id;
        this.fullName = fullName;
    }

    public long getId() {
        return id;
    }

    public String getFullName() {
        return fullName;
    }

    public State getState() {
        return state;
    }

    public boolean isAvailable() {
        return state == State.AVAILABLE;
    }

    public void setState(State state) {
        this.state = state;
    }

    public void goToRest() {
        if (state == State.ON_TRIP) {
            System.out.println("[Driver] ошибка: водитель '" + fullName +
                    "' в рейсе, нельзя уйти на отдых");
            return;
        }
        state = State.RESTING;
        System.out.println("[Driver] водитель '" + fullName + "' ушёл на отдых");
    }

    public void finishTrip() {
        state = State.AVAILABLE;
        System.out.println("[Driver] водитель '" + fullName +
                "' завершил рейс и доступен");
    }

    @Override
    public String toString() {
        return "Водитель id=" + id + ", ФИО='" + fullName + "', состояние=" + stateToStr();
    }

    private String stateToStr() {
        return switch (state) {
            case AVAILABLE -> "доступен";
            case ON_TRIP   -> "в рейсе";
            case RESTING   -> "отдыхает";
        };
    }
}
