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


  //TODO
  @Override
  public String getName() {
    return "Query 5";
  }

  @Override
  public String getDescription() {
    return "Dado o código de um utilizador determinar a lista de nomes de negócios que mais avaliou (equantos)," +
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
    Query5Results res = (Query5Results) results;

    VBox panel = new VBox();
    panel.setPadding(new Insets(5));

    panel.setSpacing(5);

    TableView<MyPair<String,Integer>> reviewsTableView = new TableView<>();
    TableColumn<MyPair<String,Integer>, String> reviewsIdColumn = new TableColumn<>("Name reviews");
    reviewsIdColumn.setCellValueFactory(new PropertyValueFactory<>("x"));

    reviewsTableView.getColumns().add(reviewsIdColumn);

    TableColumn<MyPair<String,Integer>, String> numberIdColumn = new TableColumn<>("Mean");
    numberIdColumn.setCellValueFactory(new PropertyValueFactory<>("y"));
    reviewsTableView.getColumns().add(numberIdColumn);

    reviewsTableView.getItems().addAll(res.getResults());

    VBox.setVgrow(reviewsTableView, Priority.ALWAYS);
    panel.getChildren().add(reviewsTableView);
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
