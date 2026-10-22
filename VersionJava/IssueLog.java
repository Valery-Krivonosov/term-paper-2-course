public class IssueLog implements AutoCloseable {
    private final String title;
    private boolean open = true;

    public IssueLog(String title) {
        this.title = title;
        System.out.println("[+] журнал открыт: " + title);
    }

    public void write(String line) {
        if (!open) {
            System.out.println("[!] журнал уже закрыт, запись невозможна: " + line);
            return;
        }
        System.out.println("    " + line);
    }

    @Override
    public void close() {
        if (!open) {
            return;
        }
        open = false;
        System.out.println("[-] журнал закрыт: " + title);
    }
}
