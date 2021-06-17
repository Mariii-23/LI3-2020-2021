package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.View.Queries.IQueryView;

public interface IQueryController {
    public IQueryView getView();
    public IQueryResults execute();

    public default void executeAndShow() {
        getView().showResults(execute());
    }
}
