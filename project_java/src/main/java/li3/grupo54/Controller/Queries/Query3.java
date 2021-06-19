package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query3Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query3View;

/**
 * Classe da Query 3
 */
public class Query3 implements IQueryController {
  /**
   * Modelo
   */
  GestReviews model;

  /**
   * View desta classe.
   */
  Query3View view;

  /**
   * Construstor Query 3.
   * @param model Modelo
   * @param view View
   */
  public Query3(GestReviews model, Query3View view) {
    this.model = model;
    this.view = view;
  }

  /**
   * Devolve a View.
   * @return View relacionada com a query 3.
   */
  @Override
  public IQueryView getView() {
    return view;
  }

  /**
   * Método que executa a query 3.
   * @return Query 3
   */
  @Override
  public IQueryResults execute() throws Exception {
    return new Query3Results(model.query3(view.getUserID()));
  }
}
