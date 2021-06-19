package li3.grupo54.Controller;

import li3.grupo54.Controller.Queries.IQueryController;

/**
 * Interface do Controller
 */
public interface IController {

  /**
   * Método que permite adicionar uma query.
   * @param controller Controller
   */
  void addQuery(IQueryController controller);

  /**
   * Método que permite a execução do controller.
   */
  void executa();
}
