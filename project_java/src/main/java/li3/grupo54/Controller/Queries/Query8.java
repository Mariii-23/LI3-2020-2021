package li3.grupo54.Controller.Queries;


import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query8Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query8View;

public class Query8 implements IQueryController {
  GestReviews model;
  Query8View view;

  public Query8(GestReviews model, Query8View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() {
    return new Query8Results(model.query8(view.getNumber()));
  }
}
