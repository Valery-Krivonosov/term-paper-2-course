public class Cargo {
    private double weightKg;
    private final String destination;

    public Cargo(double weightKg, String destination) {
        this.weightKg = weightKg;
        this.destination = destination;
    }

    public double getWeightKg() {
        return weightKg;
    }

    public String getDestination() {
        return destination;
    }

    public void setWeightKg(double weightKg){
        if (weightKg < 0){
            System.out.println("[Cargo] ошибка: вес не может быть отрицательным");
            return;
        }
        this.weightKg = weightKg;
    }

    @Override
    public String toString() {
        return "Груз: вес = " + weightKg + " кг, пункт назначения = '" + destination + "'";
    }
}