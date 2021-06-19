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
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Interfaces.IBusiness;

import java.util.List;
import li3.grupo54.Utils.MyTriple;
import java.util.HashMap;
import java.util.Map;

public class Query3View implements IQueryViewFX {
    private TextField userId;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;


    private String userIdString;

    public Query3View() {
        userId = new TextField();

        userId.textProperty().addListener((o, oldVal, newVal) -> {
            userIdString = userId.getText();
            setValid(true);
        });
    }

    @Override
    public String getName() {
        return "Query 3";
    }

    @Override
    public String getDescription() {
        return "Dado um código de utilizador, determinar, para cada mês, quantas reviews fez, quantos " +
                "negócios distintos avaliou e que nota média atribuiu";
    }

    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("User Id", userId);
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
            // TODO
        Query3Results res = (Query3Results) results;

        List<MyTriple<Integer,Integer,Float>> list = res.getResults();
        System.out.println(list);

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);
        panel.getChildren().add(new Label("Query 3"));


        TableView<String> reviewsTableView = new TableView<>();
        TableColumn<String, String> reviewsIdColumn = new TableColumn<>("Number reviews");
        reviewsIdColumn.setCellValueFactory(new PropertyValueFactory<>("id"));

        reviewsTableView.getColumns().add(reviewsIdColumn);
        reviewsTableView.getItems().addAll(res.getNumberReviews());

        //TableView<String> businessTableView = new TableView<>();
        //TableColumn<String, String> businessIdColumn = new TableColumn<>("Number business");
        //businessIdColumn.setCellValueFactory(new PropertyValueFactory<>("Number business"));

        //businessTableView.getColumns().add(businessIdColumn);
        //businessTableView.getItems().addAll(res.getNumberBusiness());

        //TableView<String> meanTableView = new TableView<>();
        //TableColumn<String, String> meanIdColumn = new TableColumn<>("Mean");
        //meanIdColumn.setCellValueFactory(new PropertyValueFactory<>("mean"));

        //meanTableView.getColumns().add(meanIdColumn);
        //meanTableView.getItems().addAll(res.getMean());

        //VBox.setVgrow(businessTableView, Priority.ALWAYS);
        VBox.setVgrow(reviewsTableView, Priority.ALWAYS);
        //VBox.setVgrow(meanTableView, Priority.ALWAYS);

        //panel.getChildren().add(businessTableView);
        panel.getChildren().add(reviewsTableView);
        //panel.getChildren().add(meanTableView);

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
