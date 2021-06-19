package li3.grupo54.View.Queries;

import javafx.scene.Node;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;

import java.util.Map;

/**
 * A interface the uma query em JavaFX
 */
public interface IQueryViewFX extends IQueryView {
  /**
   * A configuracao dos inputs da query
   */
  public default Map<String, Node> getConfigOptionsNode() {
    return null;
  }

  /**
   *  Configura o callback que vai apresentar os resultados
   * @param callback o callback
   */
  public void addShowResultsCallback(NodeCallback callback);

  /**
   * Obtém o callback configurado that will verify the input
   */
  public ValidationCallback getValidationCallback();

  /**
   *  Configura o callback que vai validar os inputs da query
   * @param callback o callback
   */
  public void setValidationCallback(ValidationCallback callback);

  /**
   *  Marca os inputs como validos ou invalidos, usando o callback de validacao se ele existir
   *  @param valid se os inputs sao ou nao validos
   */
  public default void setValid(boolean valid) {
    if (getValidationCallback() != null) {
      getValidationCallback().setValid(valid);
    }
  }
}
