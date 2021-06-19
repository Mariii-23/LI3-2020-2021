package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query7Results;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyTriple;

import java.util.HashMap;
import java.util.Map;

public class Query7View implements IQueryViewFX {
  private ValidationCallback callback;
  private NodeCallback resultsCallback;

  @Override
  public String getName() {
    return "Query 7";
  }

  @Override
  public String getDescription() {
    return "Determinar,para cada cidade, a lista dos três mais famosos negócios em termos de número de reviews";
  }

  @Override
  public Map<String, Node> getConfigOptionsNode() {
    return new HashMap<>();
  }

  @Override
  public void setValidationCallback(ValidationCallback callback) {
    this.callback = callback;
    setValid(true);
  }

  @Override
  public ValidationCallback getValidationCallback() {
    return callback;
  }

  @Override
  public void showResults(IQueryResults results) {
    Crono.start();
    Query7Results res = (Query7Results) results;
    double time = Crono.stop();

    VBox panel = new VBox();
    panel.setPadding(new Insets(5));

    panel.setSpacing(5);

    panel.getChildren().add(new Label("Query Time: " +time ));

    TableView<MyTriple<String,String,Integer>> tableView = new TableView<>();
    TableColumn<MyTriple<String,String,Integer>,String> column1 = new TableColumn<>("City");
    column1.setCellValueFactory(new PropertyValueFactory<>("left"));

    tableView.getColumns().add(column1);

    TableColumn<MyTriple<String,String,Integer>,String> column2 = new TableColumn<>("Business Id");
    column2.setCellValueFactory(new PropertyValueFactory<>("middle"));

    tableView.getColumns().add(column2);

    TableColumn<MyTriple<String,String,Integer>, String> column3 = new TableColumn<>("Business Number total");
    column3.setCellValueFactory(new PropertyValueFactory<>("right"));
    tableView.getColumns().add(column3);

    tableView.getItems().addAll(res.getResults());

    VBox.setVgrow(tableView, Priority.ALWAYS);
    panel.getChildren().add(tableView);

    if (this.resultsCallback != null)
      resultsCallback.run(panel);
  }
  @Override
  public void addShowResultsCallback(NodeCallback callback) {
    this.resultsCallback = callback;
  }
}
