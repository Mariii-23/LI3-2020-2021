package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.StatsResults;
import li3.grupo54.Utils.MyFive;

import java.time.Month;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StatsView implements IQueryViewFX {

  private ValidationCallback callback;
  private NodeCallback resultsCallback;

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
    StatsResults.Statistics stat = res.getResults();

    VBox panel = new VBox();
    panel.setPadding(new Insets(10));

    panel.setSpacing(10);

    {
      final StatsResults.Statistics.ReviewCatalog s = stat.reviewCatalog;
      final Label l = new Label("Reviews: ");
      l.setFont(new Font("System Bold", 13));
      panel.getChildren().add(l);
      panel.getChildren().add(new Label("\tFile Path: " + s.inputFile));
      panel.getChildren().add(new Label("\tTotal lidas: " + s.totalRead + "\n\tInválidas: " + s.invalid));
      panel.getChildren().add(new Label("\tReviews com zero impacto: " + s.zeroImpact));
    }
    {
      final StatsResults.Statistics.BusinessCatalog s = stat.businessCatalog;
      final Label l = new Label("Businesses: ");
      l.setFont(new Font("System Bold", 13));
      panel.getChildren().add(l);
      panel.getChildren().add(new Label("\tFile Path: " + s.inputFile));
      panel.getChildren().add(new Label("\tTotal lidas: " + s.totalRead + "\n\tInválidas: " + s.invalid));
      panel.getChildren().add(new Label("\tBusiness com reviews: " + s.reviewed));
    }
    {
      final StatsResults.Statistics.UsersCatalog s = stat.usersCatalog;
      final Label l = new Label("Users: ");
      l.setFont(new Font("System Bold", 13));
      panel.getChildren().add(l);
      panel.getChildren().add(new Label("\tFile Path: " + s.inputFile));
      panel.getChildren().add(new Label("\tTotal lidas: " + s.totalRead + "\n\tInválidas: " + s.invalid));
      panel.getChildren().add(new Label("\tUsers inativos: " + s.inactive));
    }


    panel.getChildren().add(new Label("\nReviews average by month"));
    List<MyFive<Month,Integer,Float,Integer,Integer>> averageReviews= stat.averageReviews;
    TableView<MyFive<Month,Integer,Float,Integer,Integer>> tableViewAverage = new TableView<>();
    TableColumn<MyFive<Month,Integer,Float,Integer,Integer>, String> stateColumn = new TableColumn<>("Month");
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
