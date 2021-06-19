package li3.grupo54.Controller.Queries;


import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query3Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query4View;

public class Query4 implements IQueryController {
  GestReviews model;
  Query4View view;

  public Query4(GestReviews model, Query4View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() {
    return new Query3Results(model.query4(view.getUserID()));
  }
}
