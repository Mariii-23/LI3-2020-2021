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
import li3.grupo54.Models.FileTriple;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query10Results;
import li3.grupo54.Models.Queries.StatsResults;
import li3.grupo54.Utils.MyFive;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.Utils.MyTriple;

import java.time.Month;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class StatsView implements IQueryViewFX {

  private ValidationCallback callback;
  private NodeCallback resultsCallback;

  private String userFilename;
  private String businessFilename;
  private String reviewsFilename;

  public StatsView(FileTriple fileTriple) {
   userFilename= fileTriple.getUsersFile();
   businessFilename = fileTriple.getBusinessesFile();
   reviewsFilename = fileTriple.getReviewsFile();
  }

  @Override
  public String getName() {
    return "Estatísticas";
  }

  @Override
  public String getDescription() {
    return "Estatísticas";
  }

  @Override
  public Map<String, Node> getConfigOptionsNode() {
    return new HashMap<>();
  }

  @Override
  public ValidationCallback getValidationCallback() {
    return callback;
  }

  @Override
  public void setValidationCallback(ValidationCallback callback) {
    this.callback = callback;
    setValid(true);
  }

  @Override
  public void showResults(IQueryResults results) {

    StatsResults res = (StatsResults) results;
    GestReviews self = res.getResults();

    VBox panel = new VBox();
    panel.setPadding(new Insets(10));

    panel.setSpacing(10);

    int lidos =self.getCatalogoReviews().size();
    int invalidos =self.getCatalogoReviews().getInvalidReviews();

    panel.getChildren().add(new Label("REVIEWS: "));
    panel.getChildren().add(new Label("\tFile Path: "+reviewsFilename));
    panel.getChildren().add(new Label("\tTotal lidas: " +(lidos+invalidos) + "\n\tInválidas: "+invalidos));
    panel.getChildren().add(new Label("\tReviews com zero impacto: "+self.getCatalogoReviews().getZeroImpact()));

    lidos = self.getCatalogoBusinesses().size();
    invalidos = self.getCatalogoBusinesses().getInvalidBusinesses();
    panel.getChildren().add(new Label("\nBUSINESS: "));
    panel.getChildren().add(new Label("\tFile Path: "+businessFilename));
    panel.getChildren().add(new Label("\tTotal lidas: " +(lidos+invalidos) + "\n\tInválidas: "+invalidos));
    panel.getChildren().add(new Label("\tBusiness com reviews: " +self.getStats().getBusinessWithReviews()));

    lidos= self.getCatalogoUsers().size();
    invalidos = self.getCatalogoUsers().getInvalidUsers();;
    panel.getChildren().add(new Label("\nUSERS: "));
    panel.getChildren().add(new Label("\tFile Path: "+userFilename));
    panel.getChildren().add(new Label("\tTotal lidas: " +(lidos+invalidos) + "\n\tInválidas: "+invalidos));
    panel.getChildren().add(new Label("\tUsers inativos: "+self.getStats().getUsersNaoAvaliados()));


    panel.getChildren().add(new Label("\nReviews average by month"));
    List<MyFive<Month,Integer,Float,Integer,Integer>> averageReviews= self.getStats().getAverageByMonthReviewAndMore();
    TableView<MyFive<Month,Integer,Float,Integer,Integer>> tableViewAverage = new TableView<>();
    TableColumn<MyFive<Month,Integer,Float,Integer,Integer>, String> stateColumn = new TableColumn<>("Mes");
    stateColumn.setCellValueFactory(new PropertyValueFactory<>("first"));
    tableViewAverage.getColumns().add(stateColumn);

    TableColumn<MyFive<Month,Integer,Float,Integer,Integer>, String> numberColumn = new TableColumn<>("Number total of reviews");
    numberColumn.setCellValueFactory(new PropertyValueFactory<>("left"));
    tableViewAverage.getColumns().add(numberColumn);

    TableColumn<MyFive<Month,Integer,Float,Integer,Integer>, String> meanColumn = new TableColumn<>("Average");
    meanColumn.setCellValueFactory(new PropertyValueFactory<>("middle"));
    tableViewAverage.getColumns().add(meanColumn);

    TableColumn<MyFive<Month,Integer,Float,Integer,Integer>, String> businessColumn = new TableColumn<>("Unique Business");
    businessColumn.setCellValueFactory(new PropertyValueFactory<>("right"));
    tableViewAverage.getColumns().add(businessColumn);

    TableColumn<MyFive<Month,Integer,Float,Integer,Integer>, String> usersColumn = new TableColumn<>("Unique Users");
    usersColumn.setCellValueFactory(new PropertyValueFactory<>("five"));
    tableViewAverage.getColumns().add(usersColumn);

    tableViewAverage.getItems().addAll(averageReviews);

    VBox.setVgrow(tableViewAverage, Priority.ALWAYS);

    panel.getChildren().add(tableViewAverage);

    if (this.resultsCallback != null)
      resultsCallback.run(panel);
  }

  @Override
  public void addShowResultsCallback(NodeCallback callback) {
    this.resultsCallback = callback;
  }

}
