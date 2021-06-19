package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.StatsResults;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.StatsView;

/**
 * Classe das Estatísticas.
 */
public class Stats implements IQueryController {
    /**
     * Modelo
     */
    GestReviews model;
    /**
     * View relacionada com esta classe.
     */
    StatsView view;

    /**
     * Construtor
     *
     * @param model Modelo
     * @param view  View
     */
    public Stats(GestReviews model, StatsView view) {
        this.model = model;
        this.view = view;
    }

    /**
     * Devolve a View das estatísticas.
     *
     * @return
     */
    @Override
    public IQueryView getView() {
        return view;
    }

    /**
     * Método que executa as Estatísticas.
     *
     * @return
     */
    @Override
    public IQueryResults execute() {
        return new StatsResults(model);
    }
}
