package li3.grupo54.main.java.li3.grupo54.View;

import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import li3.grupo54.main.java.li3.grupo54.Controller.IController;

public class DesktopView implements IView {
    private Stage stage;
    private IController controller;

    public DesktopView(IController c, Stage s) {
        this.stage = s;
        this.controller = c;
    }

    public void show() {
        this.start(stage);
    }

    public void show(Object o) {}

    public void start(Stage stage) {
        Label l = new Label("Hello world");
        Scene s = new Scene(new StackPane(l), 640, 480);
        stage.setTitle("Sistema de Gestão de Reviews [EMPTY]");
        stage.setScene(s);
        stage.show();
    }

}
