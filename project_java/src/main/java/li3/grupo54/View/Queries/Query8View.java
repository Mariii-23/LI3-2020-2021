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
import li3.grupo54.Models.Queries.Query8Results;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyPair;

import java.util.HashMap;
import java.util.Map;

/**
 * A view da query 8
 */
public class Query8View implements IQueryViewFX {
    private TextField numberInput;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    private boolean validNumber;

    private Integer number;

    /**
     * Constrói a view
     */
    public Query8View() {
        numberInput = new TextField();

        numberInput.textProperty().addListener((o, oldVal, newVal) -> {
            // Remover tudo o que não são números
            if (!newVal.matches("\\d*"))
                numberInput.setText(newVal.replaceAll("[^\\d]", ""));
            try {
                number = Integer.parseInt(numberInput.getText());
                validNumber = true;
                setValid(true);
            } catch (NumberFormatException e) {
                validNumber = false;
                setValid(false);
            }
        });
    }

    /**
     * @return O nome da query
     */
    @Override
    public String getName() {
        return "Query 8";
    }

    /**
     * @return A descrição da query
     */
    @Override
    public String getDescription() {
        return "Determinar os códigos dos X utilizadores (sendo X dado pelo utilizador) que" +
                "avaliaram mais negócios diferentes, indicando quantos, sendo o critério de ordenação " +
                "a ordem decrescente do número de negócios.";
    }

    /**
     * A configuração dos parâmetros da query
     *
     * @return neste caso um mapa com um numero X
     */
    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("X", numberInput);
        return map;
    }

    /**
     * @return o callback de validação
     */
    @Override
    public ValidationCallback getValidationCallback() {
        return callback;
    }

    /**
     * Configura o callback de validação dos parâmetros
     *
     * @param callback o callback
     */
    @Override
    public void setValidationCallback(ValidationCallback callback) {
        this.callback = callback;
    }

    /**
     * Apresenta os resultados ey
     *
     * @param results os dados a apresentar
     */
    @Override
    public void showResults(IQueryResults results) {
        Crono.start();
        Query8Results res = (Query8Results) results;
        double time = Crono.stop();

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));
        panel.setSpacing(5);

        panel.getChildren().add(new Label("Query Time: " + time));
        panel.getChildren().add(new Label("Total number users: " + res.getResults().size()));

        TableView<MyPair<String, Integer>> tableView = new TableView<>();
        TableColumn<MyPair<String, Integer>, String> column1 = new TableColumn<>("User id");
        column1.setCellValueFactory(new PropertyValueFactory<>("x"));

        tableView.getColumns().add(column1);

        TableColumn<MyPair<String, Integer>, String> column2 = new TableColumn<>("Business Number");
        column2.setCellValueFactory(new PropertyValueFactory<>("y"));

        tableView.getColumns().add(column2);

        tableView.getItems().addAll(res.getResults());

        VBox.setVgrow(tableView, Priority.ALWAYS);
        panel.getChildren().add(tableView);

        if (this.resultsCallback != null)
            resultsCallback.run(panel);

    }

    /**
     * Configura o callback de mostragem dos dados
     *
     * @param callback o callback
     */
    @Override
    public void addShowResultsCallback(NodeCallback callback) {
        this.resultsCallback = callback;
    }

    /**
     * @return o atual parâmetro da query
     */
    public Integer getNumber() {
        return number;
    }
}
