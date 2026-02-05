public class MacOSFactory extends GUIFactory {
    public Button createButton() {
        return new MacOSButton();
    }

    public Checkbox createCheckbox() {
        return new MacOSCheckbox();
    }

    public Scrollbar createScrollbar() {
        return new MacOSScrollbar();
    }
}
