package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query5Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query5View;

public class Query5 implements IQueryController {
  GestReviews model;
  Query5View view;

  public Query5(GestReviews model, Query5View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() throws Exception {
    return new Query5Results(model.query5(view.getUserId()));
  }
}
