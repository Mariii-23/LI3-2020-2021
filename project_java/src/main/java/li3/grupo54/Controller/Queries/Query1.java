package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query1Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query1View;

import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

public class Query1 implements IQueryController {
    GestReviews model;
    Query1View view;

    public Query1(GestReviews model, Query1View view) {
        this.model = model;
        this.view = view;
    }

    @Override
    public IQueryView getView() {
        return view;
    }

    @Override
    public IQueryResults execute() {
        return new Query1Results(model.getCatalogoBusinesses().getNegociosNuncaAvaliadosOrdered());
    }
}
