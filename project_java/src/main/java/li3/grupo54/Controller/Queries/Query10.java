package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query10Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query10View;

/**
 * Classe da Query 10
 */
public class Query10 implements IQueryController {

  /**
   * Modelo
   */
  GestReviews model;

  /**
   * View desta classe.
   */
  Query10View view;

  /**
   * Construtor da Query 10.
   * @param model Modelo
   * @param view View
   */
  public Query10(GestReviews model, Query10View view) {
    this.model = model;
    this.view = view;
  }

  /**
   * Devolve a View.
   * @return View relacionada com a query 10.
   */
  @Override
  public IQueryView getView() {
    return view;
  }

  /**
   * Método que executa a query 10.
   * @return Query 10
   */
  @Override
  public IQueryResults execute() {
    return new Query10Results(model.getStats().getAverageByStateBusiness());
  }
}
