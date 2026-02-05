public class Application {
    private Button button;
    private Checkbox checkbox;
    private Scrollbar scrollbar;

    public Application(GUIFactory factory){
        this.button = factory.createButton();
        this.checkbox = factory.createCheckbox();
        this.scrollbar = factory.createScrollbar();
    }

    public void renderUI(){
        button.paint();
        checkbox.paint();
        scrollbar.paint();
    }
}
