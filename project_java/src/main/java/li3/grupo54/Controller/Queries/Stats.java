package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.StatsResults;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.StatsView;

/**
 *
 *  Class responsible for obtaining statistics related to Review Management System's database.
 */


public class Stats implements IQueryController {

    GestReviews model;
    StatsView view;

    public Stats(GestReviews model, StatsView view) {
      this.model = model;
      this.view = view;
    }

    @Override
    public IQueryView getView() {
      return view;
    }

    @Override
    public IQueryResults execute() {
      return new StatsResults(model);
    }
  }
