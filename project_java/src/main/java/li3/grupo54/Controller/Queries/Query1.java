package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query1Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query1View;

/**
 * Class responsible for executing Query1 and returning an IQueryResults
 */
public class Query1 implements IQueryController {
    /**
     * Modelo
     */
    GestReviews model;

    /**
     * View desta classe.
     */
    Query1View view;

    /**
     * Construstor Query 1.
     *
     * @param model Modelo
     * @param view  View
     */
    public Query1(GestReviews model, Query1View view) {
        this.model = model;
        this.view = view;
    }

    /**
     * Devolve a View.
     *
     * @return View relacionada com a query 1.
     */
    @Override
    public IQueryView getView() {
        return view;
    }

    /**
     * Método que executa a query 1.
     *
     * @return Query 1
     */
    @Override
    public IQueryResults execute() {
        return new Query1Results(model.getStats().getNegociosNuncaAvaliadosOrdered());
    }
}
