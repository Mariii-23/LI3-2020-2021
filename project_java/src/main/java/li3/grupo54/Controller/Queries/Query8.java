package li3.grupo54.Controller.Queries;


import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query8Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query8View;

/**
 * Class responsible for executing Query8 and returning an IQueryResults
 */
public class Query8 implements IQueryController {
    /**
     * Modelo
     */
    GestReviews model;
    /**
     * View desta classe.
     */
    Query8View view;

    /**
     * Construstor Query 8.
     *
     * @param model Modelo
     * @param view  View
     */
    public Query8(GestReviews model, Query8View view) {
        this.model = model;
        this.view = view;
    }

    /**
     * Devolve a View.
     *
     * @return View relacionada com a query 8.
     */
    @Override
    public IQueryView getView() {
        return view;
    }

    /**
     * Método que executa a query 8.
     *
     * @return Query 8
     */
    @Override
    public IQueryResults execute() {
        return new Query8Results(model.query8(view.getNumber()));
    }
}
