package li3.grupo54.Models.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Utils.MyPair;

import java.util.List;


public class StatsResults implements IQueryResults {

    private final GestReviews results;

  public StatsResults(GestReviews results) {
    this.results = results;
  }
    public GestReviews getResults() {
      return results;
    }
}
