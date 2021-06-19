package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query2Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query2View;

public class Query2 implements IQueryController {
  GestReviews model;
  Query2View view;

  public Query2(GestReviews model, Query2View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() throws Exception {
    return new Query2Results(model.getCatalogoReviews().getNumberReviewsAndDistinctUsers(view.getAno(), view.getMes()));
  }
}
