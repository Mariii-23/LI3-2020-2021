package li3.grupo54.Controller;

import li3.grupo54.Controller.Queries.IQueryController;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.View.IView;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

/**
 * Controller
 */
public class Controller implements IController {
  /**
   * Model
   */
  private final GestReviews model;
  /**
   * View
   */
  private final IView view;

  /**
   * Lista das Queries que poderam ser executadas
   */
  private final List<IQueryController> queries;

  public Controller(GestReviews model, IView view) {
    this.model = model;
    this.view = view;
    this.queries = new ArrayList<>();
    this.view.setOpenCallback(this::loadTriple);
    this.view.setOnSave(this::saveObjectFile);
    this.view.setOnRestore(this::readObjectFile);
  }

  /**
   * Adicionar uma determinada Query
   * @param controller Controller
   */
  @Override
  public void addQuery(IQueryController controller) {
    view.addQuery(controller.getView(), controller::executeAndShow);
    queries.add(controller);
  }

  /**
   * Executar o controller
   */
  @Override
  public void executa() {
    view.show();
    //FileTriple triple = this.view.getFileTriple();
    //if (triple != null) {
    //  loadTriple(triple);
    //}
  }

  /**
   * Guarda o model como objeto num dado ficheiro.
   * @param file Ficherio a escrever
   * @throws IOException
   */
  public void saveObjectFile(File file) throws IOException {
    this.model.onSave(file.getAbsolutePath());
  }

  /**
   * Método que efetua o load do model a partir do caminho para três ficheiros.
   * User, Business e Reviews.
   * @param triple FileTriple
   */
  private void loadTriple(FileTriple triple) {
    try {
      model.load(triple.getUsersFile(), triple.getBusinessesFile(), triple.getReviewsFile());
      view.disableQueries(false);
    } catch (IOException | URISyntaxException e) {
      view.disableQueries(true);
      view.showError("Error opening file", e.getMessage());
    }
  }

  /**
   * Lê um determinado ficheiro de objetos, colocando isso no model.
   * @param file Ficheiro a ler
   */
   private void readObjectFile(File file) {
     try {
       this.model.onRestore(file.getAbsolutePath());
       view.disableQueries(false);
     } catch (IOException | ClassNotFoundException e) {
       view.disableQueries(true);
       view.showError("Error opening file", e.getMessage());
     }

   }
}
