package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.View.Queries.IQueryView;

/**
 * Interface For Query controller
 */
public interface IQueryController {
    /**
     * Devolverá a View relaciona com o próprio objeto.
     *
     * @return View
     */
    public IQueryView getView();

    /**
     * Este método está responsável pela execução da query em questão.
     *
     * @return
     * @throws Exception
     */
    public IQueryResults execute() throws Exception;

    /**
     * Método responsável pela sua execução e a respetiva apresentação
     *
     * @throws Exception
     */
    public default void executeAndShow() throws Exception {
        getView().showResults(execute());
    }
}
