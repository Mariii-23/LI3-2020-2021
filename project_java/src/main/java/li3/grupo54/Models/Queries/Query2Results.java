package li3.grupo54.Models.Queries;

import li3.grupo54.Utils.MyPair;

public class Query2Results implements IQueryResults {
  MyPair<Integer, Integer> result;

  public Query2Results(MyPair<Integer, Integer> result) {
    this.result = result;
  }

  public MyPair<Integer, Integer> getResults() {
    return new MyPair<>(result);
  }
}
