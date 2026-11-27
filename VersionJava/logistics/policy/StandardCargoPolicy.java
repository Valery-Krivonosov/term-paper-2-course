package logistics.policy;

import logistics.cargo.Cargo;


public class StandardCargoPolicy implements CargoPolicy {
    @Override 
    public boolean accepts(Cargo cargo, double capasityTons) {
        return cargo.getWeightKg() <= capasityTons * 1000.0;
    }
}
