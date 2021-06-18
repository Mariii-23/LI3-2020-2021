package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query2Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query2View;

    import li3.grupo54.Models.Exceptions.DateNotFoundException;
    import li3.grupo54.Models.GestReviews;
    import li3.grupo54.Models.MyPair;
    import li3.grupo54.Models.Queries.IQueryResults;
    import li3.grupo54.Models.Queries.Query2Results;
    import li3.grupo54.View.Queries.IQueryView;
    import li3.grupo54.View.Queries.Query2View;

public class Query5 implements IQueryController{
  GestReviews model;
  Query2View view;

  public Query5(GestReviews model, Query2View view) {
    this.model = model;
    this.view = view;
  }

  @Override
  public IQueryView getView() {
    return view;
  }

  @Override
  //TODO MUDAR
  public IQueryResults execute() {
    return new Query2Results(model.getCatalogoReviews().getNumberReviewsAndDistinctUsers(view.getAno(),view.getMes()));
  }
}
