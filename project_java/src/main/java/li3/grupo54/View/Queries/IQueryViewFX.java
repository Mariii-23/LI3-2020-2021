package li3.grupo54.View.Queries;

import javafx.scene.Node;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;

import java.util.Map;

public interface IQueryViewFX extends IQueryView {
  public Map<String, Node> getConfigOptionsNode();

  public void addShowResultsCallback(NodeCallback callback);

  public ValidationCallback getValidationCallback();

  public void setValidationCallback(ValidationCallback callback);

  public default void setValid(boolean valid) {
    if (getValidationCallback() != null) {
      getValidationCallback().setValid(valid);
    }
  }
}
