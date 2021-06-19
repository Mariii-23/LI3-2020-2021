package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query6Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query6View;

/**
 *
 *  Class responsible for executing Query6 and returning an IQueryResults
 */
public class Query6 implements IQueryController {
  /**
   * Modelo
   */
  GestReviews model;
  /**
   * View desta classe.
   */
  Query6View view;

  /**
   * Construstor Query 6.
   * @param model Modelo
   * @param view View
   */
  public Query6(GestReviews model, Query6View view) {
    this.model = model;
    this.view = view;
  }

  /**
   * Devolve a View.
   * @return View relacionada com a query 6.
   */
  @Override
  public IQueryView getView() {
    return view;
  }

  /**
   * Método que executa a query 6.
   * @return Query 6
   */
  @Override
  public IQueryResults execute() {
    return new Query6Results(this.model.query6(this.view.getX()));
  }
}
