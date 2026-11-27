package logistics.policy;

import logistics.cargo.Cargo;


public interface CargoPolicy {
    boolean accepts(Cargo cargo, double capacityTons);
}
