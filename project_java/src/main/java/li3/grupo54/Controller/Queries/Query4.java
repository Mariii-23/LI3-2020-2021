package li3.grupo54.Controller.Queries;


import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query4Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query4View;

/**
 *
 *  Class responsible for executing Query4 and returning an IQueryResults
 */
public class Query4 implements IQueryController {
  /**
   * Modelo
   */
  GestReviews model;

  /**
   * View desta classe.
   */
  Query4View view;

  /**
   * Construstor Query 4.
   * @param model Modelo
   * @param view View
   */
  public Query4(GestReviews model, Query4View view) {
    this.model = model;
    this.view = view;
  }

  /**
   * Devolve a View.
   * @return View relacionada com a query 4.
   */
  @Override
  public IQueryView getView() {
    return view;
  }

  /**
   * Método que executa a query 4.
   * @return Query 4
   */
  @Override
  public IQueryResults execute() throws Exception {
    return new Query4Results(model.query4(view.getUserID()));
  }
}