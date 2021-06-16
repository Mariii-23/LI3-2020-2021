package li3.grupo54.Controller;

import com.opencsv.exceptions.CsvValidationException;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.ICatalog;
import li3.grupo54.View.IView;

import java.io.IOException;
import java.net.URISyntaxException;

public class Controller implements IController {
  private GestReviews model;
  private IView view;

  public Controller(GestReviews model, IView view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public void executa() {
    this.view.show();
    FileTriple triple = this.view.getFileTriple();
    if (triple != null) {
      try {
        this.model.load(triple.getUsersFile(), triple.getBusinessesFile(), triple.getReviewsFile());
      } catch (IOException | URISyntaxException | CsvValidationException e) {
        e.printStackTrace();
      }
    }
  }
}
