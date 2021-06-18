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
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query1Results;

import java.util.HashMap;
import java.util.Map;

public class Query1View implements IQueryViewFX {
    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    @Override
    public String getName() {
        return "Negócios nunca avaliados";
    }

    @Override
    public String getDescription() {
        return "Lista ordenada alfabeticamente com os identificadores dos negócios nunca " +
               "avaliados e o seu respetivo total.";
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

        Query1Results res = (Query1Results) results;

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);

        panel.getChildren().add(new Label("Total: " + res.getBusinesses().size()));

        TableView<IBusiness> businessTableView = new TableView<>();
        TableColumn<IBusiness, String> businessIdColumn = new TableColumn<>("ID");
        businessIdColumn.setCellValueFactory(new PropertyValueFactory<>("id"));

        businessTableView.getColumns().add(businessIdColumn);
        businessTableView.getItems().addAll(res.getBusinesses());

        VBox.setVgrow(businessTableView, Priority.ALWAYS);

        panel.getChildren().add(businessTableView);

        if (this.resultsCallback != null)
            resultsCallback.run(panel);
    }

    @Override
    public void addShowResultsCallback(NodeCallback callback) {
        this.resultsCallback = callback;
    }
}
