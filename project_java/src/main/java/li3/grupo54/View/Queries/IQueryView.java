package li3.grupo54.View.Queries;

import li3.grupo54.Models.Queries.IQueryResults;

/**
 * A view de uma query
 */
public interface IQueryView {
    /**
     * @return O nome da query
     */
    public String getName();

    /**
     * @return A descrição da query
     */
    public String getDescription();

    /**
     * Apresenta os resultados da query
     *
     * @param results os dados a apresentar
     */
    public void showResults(IQueryResults results);
}
