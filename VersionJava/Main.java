public class Main {

    public static void main(String[] args) {
        System.out.println("==================== 1. Создание объектов ====================");
        Truck truck1 = new Truck("A111AA", 10.0, 4, 2022);
        Truck truck2 = new Truck("B222BB", 7.0, 2, 2020);
        Van van1 = new Van("C333CC", 3.0, 2023, 12.5);
        Van van2 = new Van("D444DD", 1.5, 2010, 8.0);

        truck1.setState(BaseVehicle.State.IN_REPAIR);

        System.out.println("\n==================== 2. Массив базовых классов ====================");
        BaseVehicle[] fleet = new BaseVehicle[4];
        fleet[0] = truck1;
        fleet[1] = truck2;
        fleet[2] = van1;
        fleet[3] = van2;

        for (BaseVehicle vehicle : fleet) {
            System.out.println("--- " + vehicle.getType() + " ---");
            String desc = vehicle.describe();
            System.out.println(desc);

            int pos = desc.indexOf("Госномер: ");
            if (pos != -1) {
                int start = pos + 10;
                int end = desc.indexOf(',', start);
                if (end != -1) {
                    String plate = desc.substring(start, end).trim();
                    System.out.println("[Анализ строки] найден номер: '" + plate + "'");
                }
            }

            System.out.println("Результат ТО: " + 
                (vehicle.passInspection() ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") + "\n");
        }

        System.out.println("==================== 3. Клонирование ====================");
        BaseVehicle clonedVan = fleet[2].cloneVehicle();
        System.out.println("Оригинал: " + fleet[2].describe());
        System.out.println("Клон: " + clonedVan.describe() + "\n");

        System.out.println("==================== 4. Копирование ====================");
        System.out.println("1. ГЛУБОКОЕ КОПИРОВАНИЕ:");
        Truck originalTruck = new Truck("T777TT", 8.0, 3, 2021);
        originalTruck.setDocs("Лист №1");

        Truck deepCopy = new Truck(originalTruck); 

        System.out.println("Оригинал: " + originalTruck.getDocs());
        System.out.println("Копия: " + deepCopy.getDocs());

        deepCopy.setDocs("Лист №2");

        System.out.println("После изменения копии:");
        System.out.println("Оригинал: " + originalTruck.getDocs());
        System.out.println("Копия: " + deepCopy.getDocs() + "\n");

        System.out.println("2. ПОВЕРХНОСТНОЕ КОПИРОВАНИЕ:");
        Truck sharedTruck = new Truck("P888PP", 6.0, 2, 2020);
        sharedTruck.setDocs("Лист №3");

        Truck shallowCopy = sharedTruck; 

        System.out.println("Оригинал: " + sharedTruck.getDocs());
        System.out.println("Копия: " + shallowCopy.getDocs());

        shallowCopy.setDocs("Лист №4");

        System.out.println("После изменения копии:");
        System.out.println("Оригинал: " + sharedTruck.getDocs());
        System.out.println("Копия: " + shallowCopy.getDocs() + "\n");

        System.out.println("==================== 5. equals() и hashCode() ====================");
        Truck t1 = new Truck("X999XX", 6.0, 3, 2020);
        Truck t2 = new Truck("X999XX", 6.0, 4, 2022);
        System.out.println("t1 и t2 одна и та же машина? " + t1.equals(t2));
        System.out.println("у t1 и t2 одинаковый хеш? " + (t1.hashCode() == t2.hashCode()));
    }
}
