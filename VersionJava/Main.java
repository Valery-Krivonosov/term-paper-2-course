import java.lang.ref.WeakReference;

public class Main {

    public static void main(String[] args) {

        System.out.println("\n==================== 1. Композиция ====================");
        {
            Order order = new Order(1, true, 1500.0, "Барнаул");
            System.out.println(order);
            System.out.println("  Вес груза через заказ: "
                        + order.getCargo().getWeightKg() + " кг");
        }

        System.out.println("\n==================== 2. Агрегация ====================");
        Driver sharedDriver = new Driver(101, "Иванов И. И.");
        {
            Order order = new Order(2, true, 800.0, "Бийск");
            order.assignDriver(sharedDriver);
            order.startTransit();
            order.deliver();
        }
        System.out.println("\n-- после уничтожения Order водитель жив --");
        System.out.println(sharedDriver);

        System.out.println("\n========== 3. Проверка правила: отдыхающий водитель ==========");
        Driver resting = new Driver(102, "Петров П. П.");
        resting.goToRest();

        Order order3 = new Order(3, false, 500.0, "Омск");
        order3.assignDriver(resting);
        System.out.println(order3);

        System.out.println("\n==================== 4. Ссылки и копии  ====================");
        Driver first  = new Driver(201, "Сидоров С. С.");
        Driver second = first;
        System.out.println("  first  до изменения: " + first);
        System.out.println("  second до изменения: " + second);

        second.setState(Driver.State.RESTING);
        System.out.println("\n  меняем состояние водителя через вторую ссылку: ");
        System.out.println("  first  = " + first);
        System.out.println("  second = " + second);
        System.out.println(" обе ссылки ведут на один и тот же объект? " + (first == second));

        System.out.println("\n==================== 5. Освобождение ресурса ====================");
        IssueLog outsideLog;
        try (IssueLog log = new IssueLog("Второй журнал")) {
            outsideLog = log;
            log.write("какая-то запись");
        }
        System.out.println("\n-- после try пытаемся писать в закрытый журнал --");
        outsideLog.write("эта запись не должна пройти");

        System.out.println("\n==================== 6. Сборщик мусора ====================");
        Driver temp = new Driver(301, "Временный Т. Т.");
        WeakReference<Driver> watcher = new WeakReference<>(temp);

        System.out.println("  до обнуления ссылки: объект жив? "
                        + (watcher.get() != null));

        temp = null;
        System.gc();
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) { }

        System.out.println(" после сборщика мусора объект жив? "
                        + (watcher.get() != null));
    }
}
