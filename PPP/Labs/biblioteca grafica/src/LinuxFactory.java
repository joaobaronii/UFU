public class LinuxFactory extends GUIFactory {
    public Button createButton() {
        return new LinuxButton();
    }

    public Scrollbar createScrollbar() {
        return new LinuxScrollbar();
    }

    public Checkbox createCheckbox() {
        return new LinuxCheckbox();
    }
}
