package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query2Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query2View;

/**
 * Classe da Query 2
 */
public class Query2 implements IQueryController {
  /**
   * Modelo
   */
  GestReviews model;

  /**
   * View desta classe.
   */
  Query2View view;

  /**
   * Construstor Query 2.
   * @param model Modelo
   * @param view View
   */
  public Query2(GestReviews model, Query2View view) {
    this.model = model;
    this.view = view;
  }

  /**
   * Devolve a View.
   * @return View relacionada com a query 2.
   */
  @Override
  public IQueryView getView() {
    return view;
  }

  /**
   * Método que executa a query 2.
   * @return Query 2
   */
  @Override
  public IQueryResults execute() throws Exception {
    return new Query2Results(model.getCatalogoReviews().getNumberReviewsAndDistinctUsers(view.getAno(), view.getMes()));
  }
}
