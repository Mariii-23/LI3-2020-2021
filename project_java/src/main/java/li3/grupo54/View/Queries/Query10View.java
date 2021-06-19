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
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query10Results;
import li3.grupo54.Utils.Crono;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * A view da query 10
 */
public class Query10View implements IQueryViewFX {
    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    /**
     * @return o nome da query
     */
    @Override
    public String getName() {
        return "Query 10";
    }

    /**
     * @return a descrição da query
     */
    @Override
    public String getDescription() {
        return "Classificação media de cada negocio, agrupada por estado e cidade";
    }

    /**
     * A configuracao dos parametros da query
     *
     * @return neste caso um map vazio
     */
    @Override
    public Map<String, Node> getConfigOptionsNode() {
        return new HashMap<>();
    }

    /**
     * @return o callback de validacao
     */
    @Override
    public ValidationCallback getValidationCallback() {
        return callback;
    }

    /**
     * Configura o callback de validacao dos parametros
     *
     * @param callback o callback
     */
    @Override
    public void setValidationCallback(ValidationCallback callback) {
        this.callback = callback;
        setValid(true);
    }

    /**
     * Apresenta os resultados da query
     *
     * @param results os dados a apresentar
     */
    @Override
    public void showResults(IQueryResults results) {

        Crono.start();
        Query10Results res = (Query10Results) results;
        double time = Crono.stop();

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);

        panel.getChildren().add(new Label("Query Time: " + time));

        TableView<Query10Results.Result> businessTableView = new TableView<>();
        TableColumn<Query10Results.Result, String> stateColumn = new TableColumn<>("Estado");
        stateColumn.setCellValueFactory(new PropertyValueFactory<>("state"));
        businessTableView.getColumns().add(stateColumn);

        TableColumn<Query10Results.Result, String> cityColumn = new TableColumn<>("Cidade");
        cityColumn.setCellValueFactory(new PropertyValueFactory<>("city"));
        businessTableView.getColumns().add(cityColumn);

        TableColumn<Query10Results.Result, String> businessIdColumn = new TableColumn<>("Negocio");
        businessIdColumn.setCellValueFactory(new PropertyValueFactory<>("businessId"));
        businessTableView.getColumns().add(businessIdColumn);

        TableColumn<Query10Results.Result, String> averageRatingColumn = new TableColumn<>("Negocio");
        averageRatingColumn.setCellValueFactory(new PropertyValueFactory<>("averageRating"));
        businessTableView.getColumns().add(averageRatingColumn);

        businessTableView.getItems().addAll(res.getResults().collect(Collectors.toList()));

        VBox.setVgrow(businessTableView, Priority.ALWAYS);

        panel.getChildren().add(businessTableView);

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

}
