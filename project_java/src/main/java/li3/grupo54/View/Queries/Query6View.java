package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query3Results;
import li3.grupo54.Utils.MyTriple;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Query6View implements IQueryViewFX {
  private TextField numeroNegocios;

  private ValidationCallback callback;
  private NodeCallback resultsCallback;

  private int x;


    public Query6View() {
        numeroNegocios = new TextField();
        numeroNegocios.textProperty().addListener((o, oldVal, newVal) -> {
        x = Integer.parseInt(numeroNegocios.getText());
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
        map.put("Id",numeroNegocios );
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
        panel.getChildren().add(new Label("Query 6"));


        TableView<MyTriple<Integer,Integer,Float>> reviewsTableView = new TableView<>();
        TableColumn<MyTriple<Integer,Integer,Float>,String> reviewsIdColumn = new TableColumn<>("Number reviews");
        reviewsIdColumn.setCellValueFactory(new PropertyValueFactory<>("left"));

        reviewsTableView.getColumns().add(reviewsIdColumn);

        TableColumn<MyTriple<Integer,Integer,Float>,String> businessIdColumn = new TableColumn<>("Number business");
        businessIdColumn.setCellValueFactory(new PropertyValueFactory<>("middle"));

        reviewsTableView.getColumns().add(businessIdColumn);

        TableColumn<MyTriple<Integer,Integer,Float>, String> meanIdColumn = new TableColumn<>("Mean");
        meanIdColumn.setCellValueFactory(new PropertyValueFactory<>("right"));
        reviewsTableView.getColumns().add(meanIdColumn);

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

    public int getX() {
        return this.x;
    }
}
