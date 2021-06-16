package li3.grupo54;

import javafx.application.Application;
import javafx.stage.Stage;
import li3.grupo54.Controller.Controller;
import li3.grupo54.Controller.IController;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.View.DesktopView;


public class GestReviewsAppMVC extends Application {
  public static void main(String[] args) {
    launch();
  }

  public void start(Stage s) {
      DesktopView view = new DesktopView(s);
      GestReviews model = new GestReviews();
      IController controller = new Controller(model, view);
      controller.executa();
  }
}
