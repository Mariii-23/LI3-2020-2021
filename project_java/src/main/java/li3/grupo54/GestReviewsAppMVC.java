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
    controller.addQuery(new Query4(model, new Query4View()));
    controller.addQuery(new Query5(model, new Query5View()));
    controller.addQuery(new Query6(model, new Query6View()));
    controller.addQuery(new Query7(model, new Query7View()));
    controller.addQuery(new Query8(model, new Query8View()));
    controller.addQuery(new Query9(model, new Query9View()));
    controller.addQuery(new Query10(model, new Query10View()));
    controller.addQuery(new Stats(model, new StatsView()));
    controller.executa();
  }
}
