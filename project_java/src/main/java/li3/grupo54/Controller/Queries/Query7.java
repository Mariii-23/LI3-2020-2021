package li3.grupo54.Controller.Queries;


import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query7Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query7View;

/**
 *
 *  Class responsible for executing Query7 and returning an IQueryResults
 */

public class Query7 implements IQueryController {
  GestReviews model;
  Query7View view;

  public Query7(GestReviews model, Query7View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() {
    return new Query7Results(model.query7());
  }
}
