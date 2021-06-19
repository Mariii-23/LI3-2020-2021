package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query9Results;
import li3.grupo54.Models.Review;
import li3.grupo54.Models.StarsTuple;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.Query9View;


import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.HashMap;
import java.util.Map;

public class Query9 implements IQueryController {
    GestReviews model;
    Query9View view;

    public Query9(GestReviews model, Query9View view) {
        this.model = model;
        this.view = view;
    }

    @Override
    public IQueryView getView() {
        return view;
    }

    @Override
    public IQueryResults execute() {
        final var bid = this.view.getBusinessId();
        final var top = this.view.getTop();
        final var result = new HashMap<String, StarsTuple>();
        this.model.getReviewsOfBusiness(bid).forEach(r -> {
            result.computeIfAbsent(r.getUserId(), (k) -> new StarsTuple()).update(r.getStars());
        });
        return new Query9Results(
                result
                        .entrySet()
                        .stream()
                        .sorted(Comparator.comparingInt(
                                (Map.Entry<String, StarsTuple> e) -> e.getValue().getNumberTotal()).reversed()
                        )
                        .limit(top)
                        .map(kv -> new MyPair<>(kv.getKey(), kv.getValue().getCurrentAverage()))
                        .collect(Collectors.toList())
        );
    }
}
