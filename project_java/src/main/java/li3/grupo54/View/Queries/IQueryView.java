package li3.grupo54.View.Queries;

import li3.grupo54.Models.Queries.IQueryResults;

public interface IQueryView {
  public String getName();

  public String getDescription();

  public void showResults(IQueryResults results);
}
