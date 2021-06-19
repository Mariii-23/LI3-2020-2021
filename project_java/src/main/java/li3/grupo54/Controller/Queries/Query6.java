package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query6Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query6View;

public class Query6 implements IQueryController{
    GestReviews model;
    Query6View view;

  public Query6(GestReviews model, Query6View view) {
    this.model = model;
    this.view = view;
  }

    @Override
    public IQueryView getView() {
        return view;
    }

    @Override
    public IQueryResults execute() {
        return new Query6Results(this.model.query6(this.view.getX()));
    }
}
