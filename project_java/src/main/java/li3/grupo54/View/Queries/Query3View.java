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
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyFour;
import li3.grupo54.Utils.MyTriple;

import java.time.Month;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * A view da query 3
 */
public class Query3View implements IQueryViewFX {
    private TextField userId;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;


    private String userIdString;

    /**
     * Constrói a view
     */
    public Query3View() {
        userId = new TextField();

        userId.textProperty().addListener((o, oldVal, newVal) -> {
            userIdString = userId.getText();
            setValid(true);
        });
    }

    /**
     * @return o nome da query
     */
    @Override
    public String getName() {
        return "Query 3";
    }

    /**
     * @return A descrição da query
     */
    @Override
    public String getDescription() {
        return "Dado um código de utilizador, determinar, para cada mês, quantas reviews fez, quantos " +
                "negócios distintos avaliou e que nota média atribuiu";
    }

    /**
     * A configuracao dos parametros da query
     *
     * @return Neste caso um unico campo chamado user id
     */
    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("User Id", userId);
        //map.put("Mês", monthInput);
        return map;
    }

    /**
     * @return O callback de validacao
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
        Crono.start();
        Query3Results res = (Query3Results) results;
        double time = Crono.stop();

        List<MyTriple<Integer, Integer, Double>> res1 = ((Query3Results) results).getResults();

        List<MyFour<Month, Integer, Integer, Double>> apresentar = new ArrayList<>(12);
        int i = 1;
        for (MyTriple<Integer, Integer, Double> triple : res1) {
            apresentar.add(i - 1, new MyFour<>(Month.of(i), triple));
            i++;
        }

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);
        panel.getChildren().add(new Label("Query 3"));
        panel.getChildren().add(new Label("Query Time: " + time));

        TableView<MyFour<Month, Integer, Integer, Double>> tableView = new TableView<>();
        TableColumn<MyFour<Month, Integer, Integer, Double>, String> mesesColumn = new TableColumn<>("Mes");
        mesesColumn.setCellValueFactory(new PropertyValueFactory<>("first"));
        tableView.getColumns().add(mesesColumn);

        TableColumn<MyFour<Month, Integer, Integer, Double>, String> column2 = new TableColumn<>("Number reviews total");
        column2.setCellValueFactory(new PropertyValueFactory<>("left"));

        tableView.getColumns().add(column2);

        TableColumn<MyFour<Month, Integer, Integer, Double>, String> column3 = new TableColumn<>("Number business distinct");
        column3.setCellValueFactory(new PropertyValueFactory<>("middle"));

        tableView.getColumns().add(column3);

        TableColumn<MyFour<Month, Integer, Integer, Double>, String> meanIdColumn = new TableColumn<>("Average");
        meanIdColumn.setCellValueFactory(new PropertyValueFactory<>("right"));
        tableView.getColumns().add(meanIdColumn);

        tableView.getItems().addAll(apresentar);

        VBox.setVgrow(tableView, Priority.ALWAYS);
        panel.getChildren().add(tableView);

        if (this.resultsCallback != null)
            resultsCallback.run(panel);

    }

    /**
     * Configura o callback de apresentação
     *
     * @param callback o callback
     */
    @Override
    public void addShowResultsCallback(NodeCallback callback) {
        this.resultsCallback = callback;
    }

    /**
     * @return O UserId que esta no parametro
     */
    public String getUserID() {
        return this.userIdString;
    }
}