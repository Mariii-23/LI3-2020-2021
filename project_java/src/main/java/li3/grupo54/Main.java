package li3.grupo54;

import javafx.application.Application;
import javafx.stage.Stage;
import li3.grupo54.Controller.Controller;
import li3.grupo54.Controller.IController;
import li3.grupo54.View.DesktopView;

public class Main extends Application {
    public static void main(String[] args) {
        launch();
    }

    public void start(Stage s) {
        IController c = new Controller();
        DesktopView v = new DesktopView(c, s);
        v.show();
    }
}
