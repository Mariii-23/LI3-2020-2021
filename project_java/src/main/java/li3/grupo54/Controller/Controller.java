package li3.grupo54.Controller;

import com.opencsv.exceptions.CsvValidationException;
import li3.grupo54.Controller.Queries.IQueryController;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.View.IView;

import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

public class Controller implements IController {
  private GestReviews model;
  private IView view;

  private List<IQueryController> queries;

  public Controller(GestReviews model, IView view) {
    this.model = model;
    this.view = view;
    this.queries = new ArrayList<>();
    this.view.setOpenCallback(this::loadTriple);
  }

  @Override
  public void addQuery(IQueryController controller) {
    view.addQuery(controller.getView(), controller::executeAndShow);
    queries.add(controller);
  }

  @Override
  public void executa() {
    view.show();
    FileTriple triple = this.view.getFileTriple();
    if (triple != null) {
      loadTriple(triple);
    }
  }

  private void loadTriple(FileTriple triple) {
    try {
      model.load(triple.getUsersFile(), triple.getBusinessesFile(), triple.getReviewsFile());
    } catch (IOException | URISyntaxException | CsvValidationException e) {
      view.showError("Error opening file", e.getMessage());
    }
  }
}
