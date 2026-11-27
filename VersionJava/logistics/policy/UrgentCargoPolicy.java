package logistics.policy;

import logistics.cargo.Cargo;


public class UrgentCargoPolicy implements CargoPolicy {
    @Override 
    public boolean accepts(Cargo cargo, double capacityTons){
        return cargo.getWeightKg() >= capacityTons * 1000.0 * 1.10;
    }
}
