package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query5Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query5View;

/**
 * Class responsible for executing Query5 and returning an IQueryResults
 */
public class Query5 implements IQueryController {
    /**
     * Modelo
     */
    GestReviews model;

    /**
     * View desta classe.
     */
    Query5View view;

    /**
     * Construstor Query 5.
     *
     * @param model Modelo
     * @param view  View
     */
    public Query5(GestReviews model, Query5View view) {
        this.model = model;
        this.view = view;
    }

    /**
     * Devolve a View.
     *
     * @return View relacionada com a query 5.
     */
    @Override
    public IQueryView getView() {
        return view;
    }

    /**
     * Método que executa a query 5.
     *
     * @return Query 5
     */
    @Override
    public IQueryResults execute() throws Exception {
        return new Query5Results(model.query5(view.getUserId()));
    }
}
