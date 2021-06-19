package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query1Results;
import li3.grupo54.Utils.Crono;

import java.util.HashMap;
import java.util.Map;

/**
 * A view a query 1
 */
public class Query1View implements IQueryViewFX {
  private ValidationCallback callback;
  private NodeCallback resultsCallback;

  /** O nome da query */
  @Override
  public String getName() {
    return "Query 1";
  }

  /** A descrição da query */
  @Override
  public String getDescription() {
    return "Lista ordenada alfabeticamente com os identificadores dos negócios nunca " +
        "avaliados e o seu respetivo total.";
  }

  /** Os parametros da query, neste caso nenhums */
  @Override
  public Map<String, Node> getConfigOptionsNode() {
    return new HashMap<>();
  }

  /** Obtém o callback de validacao */
  @Override
  public ValidationCallback getValidationCallback() {
    return callback;
  }

  /** Configura o callback de validacao */
  @Override
  public void setValidationCallback(ValidationCallback callback) {
    this.callback = callback;
    setValid(true);
  }

  /** Aprensenta os resultados desta query */
  @Override
  public void showResults(IQueryResults results) {
    Crono.start();
    Query1Results res = (Query1Results) results;
    double time = Crono.stop();

    VBox panel = new VBox();
    panel.setPadding(new Insets(5));

    panel.setSpacing(5);

    panel.getChildren().add(new Label("Total: " + res.getBusinesses().size()));
    panel.getChildren().add(new Label("Query Time: " + time));

    TableView<IBusiness> tableView = new TableView<>();
    TableColumn<IBusiness, String> column1 = new TableColumn<>("ID");
    column1.setCellValueFactory(new PropertyValueFactory<>("id"));

    tableView.getColumns().add(column1);
    tableView.getItems().addAll(res.getBusinesses());

    VBox.setVgrow(tableView, Priority.ALWAYS);

    panel.getChildren().add(tableView);

    if (this.resultsCallback != null)
      resultsCallback.run(panel);
  }

  /** Configura o callback usado para apresentar */
  @Override
  public void addShowResultsCallback(NodeCallback callback) {
    this.resultsCallback = callback;
  }
}
