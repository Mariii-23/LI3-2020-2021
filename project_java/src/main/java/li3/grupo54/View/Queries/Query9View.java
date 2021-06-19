package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.control.TextField;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query9Results;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyPair;

import java.util.HashMap;
import java.util.Map;

public class Query9View implements IQueryViewFX {
    private TextField businessIdTextField;
    private TextField topTextField;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    private boolean validTop;
    private boolean validBid;

    private String businessId;
    private Integer top;

    public String getBusinessId() {
        return businessId;
    }

    public Integer getTop() {
        return top;
    }

    public Query9View() {
        this.businessId = null;
        this.top = -1;
        this.businessIdTextField = new TextField();
        this.topTextField = new TextField();

        this.topTextField.textProperty().addListener((o, oldVal, newVal) -> {
            // Remover tudo o que não são números
            if (!newVal.matches("\\d*"))
                this.topTextField.setText(newVal.replaceAll("[^\\d]", ""));

            try {
                this.top = Integer.parseInt(this.topTextField.getText());
                this.validTop = true;
                setValid(this.validBid);
            } catch (NumberFormatException e) {
                this.validTop = false;
                setValid(false);
            }
        });

        this.businessIdTextField.textProperty().addListener((o, oldVal, newVal) -> {
            this.businessId = this.businessIdTextField.getText();
            this.validBid = this.businessId.isBlank();
            setValid(this.validTop);
        });
    }

    @Override
    public String getName() {
        return "Query 9";
    }

    @Override
    public String getDescription() {
        return "Dado o código de um negócio, determinar o conjunto dos X users que mais o" +
                "avaliaram e, para cada um, qual o valor médio de classificação";
    }

    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("Id de negocio", businessIdTextField);
        map.put("Numero", topTextField);
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
        Query9Results res = (Query9Results) results;
        double time= Crono.stop();

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);

        panel.getChildren().add(new Label("Query Time: " +time ));
        TableView<MyPair<String, Double>> tableView = new TableView<>();
        TableColumn<MyPair<String, Double>, String> usersColumn = new TableColumn<>("Utilizador");
        usersColumn.setCellValueFactory(new PropertyValueFactory<>("x"));
        tableView.getColumns().add(usersColumn);

        TableColumn<MyPair<String, Double>, String> ratingColumn = new TableColumn<>("Valor de classificação medio");
        ratingColumn.setCellValueFactory(new PropertyValueFactory<>("y"));
        tableView.getColumns().add(ratingColumn);

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
