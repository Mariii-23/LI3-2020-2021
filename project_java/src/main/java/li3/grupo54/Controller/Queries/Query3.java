package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query3Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query3View;

public class Query3 implements IQueryController {
  GestReviews model;
  Query3View view;

  public Query3(GestReviews model, Query3View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  public IQueryResults execute() {
    return new Query3Results(model.query3(view.getUserID()));
  }
}
