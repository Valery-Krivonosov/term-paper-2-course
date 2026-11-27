package logistics;

import logistics.cargo.Cargo;


public interface Assignable {
    boolean canTake(Cargo cargo);
    void assignTo(long orderId);
    void completeTrip();
    boolean isAvailable();
}
