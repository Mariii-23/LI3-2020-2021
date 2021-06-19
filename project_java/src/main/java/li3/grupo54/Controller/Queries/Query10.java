package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query10Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query10View;

/**
 *
 *  Class responsible for executing Query10 and returning an IQueryResults
 */

public class Query10 implements IQueryController {

  GestReviews model;
  Query10View view;

  public Query10(GestReviews model, Query10View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() {
    return new Query10Results(model.getStats().getAverageByStateBusiness());
  }
}
