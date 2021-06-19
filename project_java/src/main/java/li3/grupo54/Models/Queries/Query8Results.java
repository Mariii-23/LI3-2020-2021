package li3.grupo54.Models.Queries;

import li3.grupo54.Utils.MyPair;

import java.util.List;

public class Query8Results implements IQueryResults {
  List<MyPair<String, Integer>> result;

  public Query8Results(List<MyPair<String, Integer>> result) {
    this.result = result;
  }

  public List<MyPair<String, Integer>> getResults() {
    return result;
  }
}
