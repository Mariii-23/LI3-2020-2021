package li3.grupo54.main.java.li3.grupo54;

import li3.grupo54.main.java.li3.grupo54.Models.CatalogoUsers;

import java.io.IOException;
import java.net.URISyntaxException;

public class GestReviewsAppMVC {
    public static void main(String[] args) throws IOException, URISyntaxException {
        CatalogoUsers c = new CatalogoUsers();

        c.populateFromFile("teste.csv");

        //launch();
    }

    //public void start(Stage s) {
    //    IController c = new Controller();
    //    DesktopView v = new DesktopView(c, s);
    //    v.show();
    //}
}