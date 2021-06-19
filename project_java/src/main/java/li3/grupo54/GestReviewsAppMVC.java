package li3.grupo54;

import javafx.application.Application;
import javafx.stage.Stage;
import li3.grupo54.Controller.Controller;
import li3.grupo54.Controller.IController;
import li3.grupo54.Controller.Queries.*;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.View.DesktopView;
import li3.grupo54.View.Queries.*;


public class GestReviewsAppMVC extends Application {
  public static void main(String[] args) {
    launch();
  }

  public void start(Stage s) {
      DesktopView view = new DesktopView(s);
      GestReviews model = new GestReviews();
      IController controller = new Controller(model, view);

      controller.addQuery(new Query1(model, new Query1View()));
      controller.addQuery(new Query2(model, new Query2View()));
      controller.addQuery(new Query3(model, new Query3View()));
      controller.addQuery(new Query5(model, new Query5View()));
      //view.addQuery(new Query2View());
      controller.executa();
  }
}
