package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query2Results;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query3View;
import org.apache.commons.lang3.tuple.Triple;

public class Query3 implements IQueryController{
    GestReviews model;
    Query3View view;

    public Query3(GestReviews model, Query3View view) {
        this.model = model;
        this.view = view;
    }

    @Override
    public IQueryView getView() {
        return view;
    }

    @Override
    public IQueryResults execute() {
        // mudar para triple
            return new Query2Results(model.getCatalogoReviews().getNumberReviewsAndDistinctUsers(view.getAno(),view.getMes()));
    }
}
