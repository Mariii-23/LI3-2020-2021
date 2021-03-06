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
import li3.grupo54.Models.Queries.Query6Results;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyTriple;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

/**
 * A view da query 6
 */
public class Query6View implements IQueryViewFX {
    private TextField numeroNegocios;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    private int x;


    /**
     * Constroi a view
     */
    public Query6View() {
        numeroNegocios = new TextField();
        numeroNegocios.textProperty().addListener((o, oldVal, newVal) -> {
            if (!newVal.matches("\\d*"))
                numeroNegocios.setText(newVal.replaceAll("[^\\d]", ""));
            try {
                x = Integer.parseInt(numeroNegocios.getText());
                setValid(true);
            } catch (NumberFormatException e) {
                setValid(false);
            }
        });
    }

    /**
     * @return o nome da query
     */
    @Override
    public String getName() {
        return "Query 6";
    }

    /**
     * @return a descricao da query
     */
    @Override
    public String getDescription() {
        return "Determinar o conjunto dos X negócios mais avaliados (com mais reviews) em " +
                "cada ano, indicando o número total de distintos utilizadores que o avaliaram " +
                "( X é um inteiro dado pelo utilizador)";
    }

    /**
     * A configuracao dos parametros da query
     *
     * @return Neste caso apenas um numero "N"
     */
    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("N", numeroNegocios);
        //map.put("Mês", monthInput);
        return map;
    }

    /**
     * @return Obtem o callback de validacao
     */
    @Override
    public ValidationCallback getValidationCallback() {
        return callback;
    }

    /**
     * Configura o callback de validacao
     *
     * @param callback o callback
     */
    @Override
    public void setValidationCallback(ValidationCallback callback) {
        this.callback = callback;
    }

    /**
     * Apresenta os dados da query
     *
     * @param results os dados a apresentar
     */
    @Override
    public void showResults(IQueryResults results) {
        // TODO
        Crono.start();
        double time = Crono.stop();
        Query6Results res = (Query6Results) results;

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);
        panel.getChildren().add(new Label("Query 6"));

        panel.getChildren().add(new Label("Query Time: " + time));
        panel.getChildren().add(new Label("Total number business: " + res.getBusinesses().size()));

        TableView<MyTriple<Integer, String, Integer>> tableView = new TableView<>();

        TableColumn<MyTriple<Integer, String, Integer>, String> yearColumn = new TableColumn<>("Ano");
        yearColumn.setCellValueFactory(new PropertyValueFactory<>("left"));
        tableView.getColumns().add(yearColumn);

        TableColumn<MyTriple<Integer, String, Integer>, String> businessIdColumn = new TableColumn<>("Business");
        businessIdColumn.setCellValueFactory(new PropertyValueFactory<>("middle"));
        tableView.getColumns().add(businessIdColumn);

        TableColumn<MyTriple<Integer, String, Integer>, String> distinctUsers = new TableColumn<>("Numero de utilizadores unicos");
        distinctUsers.setCellValueFactory(new PropertyValueFactory<>("right"));
        tableView.getColumns().add(distinctUsers);

        final var buz = res.getBusinesses();
        buz.sort(Comparator.comparingInt(MyTriple::getLeft));
        tableView.getItems().addAll(buz);

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
     * @return O atual parametro da query
     */
    public int getX() {
        return this.x;
    }
}
