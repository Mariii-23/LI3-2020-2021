package li3.grupo54.View.Queries;



import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.geometry.Insets;
import javafx.scene.control.TextField;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query3Results;

import java.time.Month;
import java.util.ArrayList;
import java.util.List;

import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyFour;
import li3.grupo54.Utils.MyTriple;
import java.util.HashMap;
import java.util.Map;

public class Query4View implements IQueryViewFX {
  private TextField businessId;

  private ValidationCallback callback;
  private NodeCallback resultsCallback;


  private String userIdString;

  public Query4View() {
    businessId = new TextField();

    businessId.textProperty().addListener((o, oldVal, newVal) -> {
      userIdString = businessId.getText();
      setValid(true);
    });
  }

  @Override
  public String getName() {
    return "Query 4";
  }

  @Override
  public String getDescription() {
    return "Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado, por " +
        "quantos users diferentes e a média de classificação";
  }

  @Override
  public Map<String, Node> getConfigOptionsNode() {
    Map<String, Node> map = new HashMap<>();
    map.put("Business Id", businessId);
    //map.put("Mês", monthInput);
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
    Query3Results res = (Query3Results) results;
    double time = Crono.stop();

    List<MyTriple<Integer,Integer,Float>> res1 = ((Query3Results) results).getResults();

    List<MyFour<Month,Integer,Integer,Float>> apresentar = new ArrayList<>(12);
    int i=1;
    for(MyTriple<Integer,Integer,Float> triple :res1){
      apresentar.add(i-1,new MyFour<>(Month.of(i),triple));
      i++;
    }

    VBox panel = new VBox();
    panel.setPadding(new Insets(5));

    panel.setSpacing(5);
    panel.getChildren().add(new Label("Query 4"));

    panel.getChildren().add(new Label("Query Time: " +time ));

    TableView<MyFour<Month,Integer,Integer,Float>> reviewsTableView = new TableView<>();

    TableColumn<MyFour<Month,Integer,Integer,Float>,String> mesesColumn = new TableColumn<>("Mes");
    mesesColumn.setCellValueFactory(new PropertyValueFactory<>("first"));
    reviewsTableView.getColumns().add(mesesColumn);

    TableColumn<MyFour<Month,Integer,Integer,Float>,String> reviewsIdColumn = new TableColumn<>("Number business total");
    reviewsIdColumn.setCellValueFactory(new PropertyValueFactory<>("left"));

    reviewsTableView.getColumns().add(reviewsIdColumn);

  TableColumn<MyFour<Month,Integer,Integer,Float>,String> businessIdColumn = new TableColumn<>("Number users distinct");
    businessIdColumn.setCellValueFactory(new PropertyValueFactory<>("middle"));

    reviewsTableView.getColumns().add(businessIdColumn);

    TableColumn<MyFour<Month,Integer,Integer,Float>, String> meanIdColumn = new TableColumn<>("Average");
    meanIdColumn.setCellValueFactory(new PropertyValueFactory<>("right"));
    reviewsTableView.getColumns().add(meanIdColumn);

    reviewsTableView.getItems().addAll(apresentar);

    VBox.setVgrow(reviewsTableView, Priority.ALWAYS);
    panel.getChildren().add(reviewsTableView);

    if (this.resultsCallback != null)
      resultsCallback.run(panel);

  }
  @Override
  public void addShowResultsCallback(NodeCallback callback) {
    this.resultsCallback = callback;
  }

  public String getUserID(){
    return this.userIdString;
  }
}
