package li3.grupo54;

import com.opencsv.exceptions.CsvValidationException;
import li3.grupo54.Models.CatalogoUsers;

import java.io.IOException;
import java.net.URISyntaxException;

public class GestReviewsAppMVC {
  public static void main(String[] args) throws IOException, URISyntaxException, CsvValidationException {
    CatalogoUsers c = new CatalogoUsers();

    c.populateFromFile("test.csv");


    //launch();
  }

  //public void start(Stage s) {
  //    IController c = new Controller();
  //    DesktopView v = new DesktopView(c, s);
  //    v.show();
  //}
}
