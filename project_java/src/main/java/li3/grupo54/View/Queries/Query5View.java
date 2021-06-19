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
import javafx.scene.Node;
import javafx.scene.control.TextField;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query5Results;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyPair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Query5View implements IQueryViewFX {
  private TextField userId;

  private ValidationCallback callback;
  private NodeCallback resultsCallback;

  private String userIdString;

  public Query5View() {
   userId = new TextField();
    userId.textProperty().addListener((o, oldVal, newVal) -> {
        userIdString = userId.getText();
        setValid(true);
    });
  }

  @Override
  public String getName() {
    return "Query 5";
  }

  @Override
  public String getDescription() {
    return "Dado o código de um utilizador determinar a lista de nomes de negócios que mais avaliou (e quantos)," +
            "ordenada por ordem decrescente de quantidade e,para quantidades iguais, por ordem alfabética dos negócios";
  }

  @Override
  public Map<String, Node> getConfigOptionsNode() {
    Map<String, Node> map = new HashMap<>();
    map.put("User Id", userId);
    return map;
  }

  @Override
  public void setValidationCallback(ValidationCallback callback) {
    this.callback = callback;
  }

  @Override
  public ValidationCallback getValidationCallback() {
    return callback;
  }

  @Override
  public void showResults(IQueryResults results) {
    Crono.start();
    Query5Results res = (Query5Results) results;
    double time = Crono.stop();

    VBox panel = new VBox();
    panel.setPadding(new Insets(5));

    panel.setSpacing(5);

    panel.getChildren().add(new Label("Query Time: " +time ));

    TableView<MyPair<String,Integer>> tableView = new TableView<>();
    TableColumn<MyPair<String,Integer>, String> column1 = new TableColumn<>("Name reviews");
    column1.setCellValueFactory(new PropertyValueFactory<>("x"));

    tableView.getColumns().add(column1);

    TableColumn<MyPair<String,Integer>, String> meanColumn = new TableColumn<>("Mean");
    meanColumn.setCellValueFactory(new PropertyValueFactory<>("y"));
    tableView.getColumns().add(meanColumn);

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

  public String getUserId() {
    return this.userIdString;
  }
}
