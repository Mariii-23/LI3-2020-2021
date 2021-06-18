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
import li3.grupo54.Models.Queries.Query2Results;

import java.util.HashMap;
import java.util.Map;

public class Query5View implements IQueryViewFX {
  private TextField userId;

  private ValidationCallback callback;
  private NodeCallback resultsCallback;

  private boolean validUserId;

  private String userIdString;

  public Query5View() {
    userId = new TextField();

    userId.textProperty().addListener((o, oldVal, newVal) -> {
      // Remover tudo o que não são números
      if (!newVal.matches("\\d*"))
        userId.setText(newVal.replaceAll("[^\\d]", ""));

      try {
        double d = Double.parseDouble(userId.getText());
        validUserId = true;
        userIdString = userId.getText();
      } catch (NumberFormatException nfe) {
        validUserId= false;
      }
    });
  }


  //TODO
  @Override
  public String getName() {
    return "???";
  }

  @Override
  public String getDescription() {
    return "Dado um código de utilizador, determinar, para cada mês, quantas reviews fez," +
         "quantos negócios distintos avaliou e que nota média atribuiu";
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
    // TODO
   // Query2Results res = (Query2Results) results;

   // var pair = res.getResults();

   // VBox panel = new VBox();
   // panel.setPadding(new Insets(5));

   // panel.setSpacing(5);
   // panel.getChildren().add(new Label("Total reviews: " +pair.getX()+" Total users distintos: "+pair.getY()));
   // if (this.resultsCallback != null)
   //   resultsCallback.run(panel);

  }
  @Override
  public void addShowResultsCallback(NodeCallback callback) {
    this.resultsCallback = callback;
  }

  public String getUserId() {
    return this.userIdString;
  }
}
