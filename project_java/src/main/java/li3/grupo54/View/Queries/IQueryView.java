package li3.grupo54.View.Queries;

import li3.grupo54.Models.Queries.IQueryResults;

/**
 * A view the corresponds to a query
 */
public interface IQueryView {
  /** The name of the query */
  public String getName();

  /** The query's description */
  public String getDescription();

  /**
   * Present the query's results
   * @param results the data to present
   */
  public void showResults(IQueryResults results);
}
