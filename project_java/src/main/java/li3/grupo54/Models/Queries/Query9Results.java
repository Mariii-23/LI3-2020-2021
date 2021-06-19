package li3.grupo54.Models.Queries;

import li3.grupo54.Utils.MyPair;

import java.util.List;

public class Query9Results implements IQueryResults {
  private final List<MyPair<String, Double>> results;

  public Query9Results(List<MyPair<String, Double>> results) {
    this.results = results;
  }

  public List<MyPair<String, Double>> getResults() {
    return results;
  }
}
