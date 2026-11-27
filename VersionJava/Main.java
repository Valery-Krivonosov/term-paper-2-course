import logistics.Assignable;
import logistics.cargo.Cargo;
import logistics.driver.Driver;
import logistics.order.Order;
import logistics.policy.StandardCargoPolicy;
import logistics.policy.UrgentCargoPolicy;
import logistics.vehicle.*;
import logistics.exception.*;

import java.util.Arrays;


public class Main {
    public static void main(String[] args) {
        System.out.println("\n================== 1. Раннее и позднее связывание ==================");
        BaseVehicle v = new Truck("A123BC", 10.0, 4, 2020, new StandardCargoPolicy());
        System.out.println("getKind() (позднее, все методы виртуальны): " + v.getKind());
        System.out.println("getFixedKind() (раннее, final-метод): " + v.getFixedKind());

        System.out.println("\n================== 2. Демонстрация instanceof  ==================");
        BaseVehicle[] fleet = {
            new Truck("B456CD", 8.0, 3, 2021, new StandardCargoPolicy()),
            new Van("D222BB", 3.0, 2023, 12.0),
            new Van("F777FF", 1.0, 2022, 5.0),
            new RepairVehicle("R001RP", 5.0, 2010)
        };

        Cargo cargo = new Cargo(2000.0, "Тверь");
        for (BaseVehicle f : fleet) {
            if (f instanceof Assignable a) {
                if (!tryAssign(a, cargo, 42)) {
                    System.out.println(f.getType() + " не подходит по грузоподъёмности");
                }
            } else {
                System.out.println(f.getType() + " нельзя назначить на рейс");
            }
        }

        System.out.println("\n================== 3. Конфигурирование (смена правила) ==================");
        Truck t = new Truck("E333EE", 5.0, 3, 2021, new StandardCargoPolicy());
        Order heavy = new Order(12, true, 5500.0, "Сочи");

        System.out.println("обычное правило: canTake = " + t.canTake(heavy.getCargo()));
        t.setPolicy(new UrgentCargoPolicy());
        System.out.println("срочное правило: canTake = " + t.canTake(heavy.getCargo()));

        System.out.println("\n================== 4. Исключения: успешное действие ==================");
        Driver driver = new Driver(1, "Иванов");
        try {
            heavy.assignDriver(driver);
            heavy.startTransit();
            heavy.deliver();
            System.out.println("заказ 12 успешно доставлен");
        } catch (DriverUnavailableException e) {
            System.out.println("водитель: " + e.getMessage());
        } catch (InvalidOrderStateException e) {
            System.out.println("состояние: " + e.getMessage());
        } catch (LogisticsException e) {
            System.out.println("ошибка: " + e.getMessage());
        }

        System.out.println("\n================== 5. Исключения: нарушение правил ==================");

        try {
            heavy.deliver();
        } catch (InvalidOrderStateException e) {
            System.out.println("перехвачено: " + e.getMessage());
        } catch (LogisticsException e) {
            System.out.println("ошибка: " + e.getMessage());
        }

        try {
            Truck t2 = new Truck("G555GG", 5.0, 3, 2021, new StandardCargoPolicy());
            if (!t2.canTake(heavy.getCargo())) {
                throw new OverLoadException(heavy.getCargo().getWeightKg(), t2.getCapacity());
            }
        } catch (OverLoadException e) {
            System.out.println("перехвачено: " + e.getMessage());
        } catch (LogisticsException e) {
            System.out.println("ошибка: " + e.getMessage());
        }

        try {
            Cargo bad = new Cargo(100.0, "Омск");
            bad.setWeightKg(-5.0);
        } catch (NegativeWeightException e) {
            System.out.println("перехвачено: " + e.getMessage());
        } catch (LogisticsException e) {
            System.out.println("ошибка: " + e.getMessage());
        }

        try {
            Driver resting = new Driver(2, "Петров");
            resting.setState(Driver.State.ON_TRIP);
            resting.goToRest();
        } catch (DriverUnavailableException e) {
            System.out.println("перехвачено: " + e.getMessage());
        } catch (LogisticsException e) {
            System.out.println("ошибка: " + e.getMessage());
        }

        try {
            if (fleet[0] instanceof Assignable a) {
                a.assignTo(43);
            }
        } catch (NoAvailableVehicleException e) {
            System.out.println("перехвачено: " + e.getMessage());
        } catch (LogisticsException e) {
            System.out.println("ошибка: " + e.getMessage());
        }

        System.out.println("\n================== 6. Comparable: сортировка по госномеру ==================");
        Arrays.sort(fleet);
        for (BaseVehicle f : fleet) {
            System.out.println("  " + f.getType() + " " + f.getPlateNumber());
        }

        System.out.println("\n================== 7. try-with-resources: журнал ==================");
        try (IssueLog log = new IssueLog("журнал лаба5")) {
            log.write("рейс завершён");
            log.write("заказ 12 доставлен");
        }

    }

    private static boolean tryAssign(Assignable item, Cargo cargo, long orderId) {
        if (!item.isAvailable()) {
            return false;
        }
        if (!item.canTake(cargo)) {
            return false;
        }
        
        item.assignTo(orderId);
        return true;
    }
}
