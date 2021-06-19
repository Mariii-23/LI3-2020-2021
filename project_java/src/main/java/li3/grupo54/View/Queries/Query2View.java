package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query2Results;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyPair;

import java.util.HashMap;
import java.util.Map;

/**
 * A view da query 2
 */
public class Query2View implements IQueryViewFX {
    private TextField monthInput;
    private TextField yearInput;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    private boolean validAno;
    private boolean validMes;

    private Integer ano;
    private Integer mes;

    /**
     * Constrói a view
     */
    public Query2View() {
        ano = -1;
        mes = -1;
        monthInput = new TextField();
        yearInput = new TextField();

        monthInput.textProperty().addListener((o, oldVal, newVal) -> {
            // Remover tudo o que não são números
            if (!newVal.matches("\\d*"))
                monthInput.setText(newVal.replaceAll("[^\\d]", ""));

            try {
                int v = Integer.parseInt(monthInput.getText());
                if (v > 0 && v <= 12) {
                    mes = v;
                    validMes = true;
                    setValid(validAno);
                } else {
                    validMes = false;
                    setValid(false);
                }
            } catch (NumberFormatException e) {
                validMes = false;
                setValid(false);
            }
        });

        yearInput.textProperty().addListener((o, oldVal, newVal) -> {
            // Remover tudo o que não são números
            if (!newVal.matches("\\d*"))
                yearInput.setText(newVal.replaceAll("[^\\d]", ""));

            try {
                int v = Integer.parseInt(yearInput.getText());
                if (v > 0) {
                    ano = v;
                    validAno = true;
                    setValid(validMes);
                } else {
                    validAno = false;
                    setValid(false);
                }
            } catch (NumberFormatException e) {
                validAno = false;
                setValid(false);
            }
        });
    }

    /**
     * @return o ano que foi colocado no parametro
     */
    public Integer getAno() {
        return ano;
    }

    /**
     * @return o mes que foi colocado no parametro
     */
    public Integer getMes() {
        return mes;
    }

    /**
     * @return O nome da query
     */
    @Override
    public String getName() {
        return "Query 2";
    }

    /**
     * @return A descricao da query
     */
    @Override
    public String getDescription() {
        return "Dado um mês e um ano (válidos), determinar o número total global de reviews realizadas e o número " +
                "total de users distintos que as realizaram.";
    }

    /**
     * Os parametros da query
     *
     * @return Neste caso u ano e o mes
     */
    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("Ano", yearInput);
        map.put("Mês", monthInput);
        return map;
    }

    /**
     * @return o callback de validacao dos parametros
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
     * Apresenta os resultados da query
     *
     * @param results the data to present
     */
    @Override
    public void showResults(IQueryResults results) {
        Crono.start();
        Query2Results res = (Query2Results) results;
        double time = Crono.stop();

        MyPair<Integer, Integer> pair = res.getResults();

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);
        panel.getChildren().add(new Label("Total reviews: " + pair.getX() + " Total users distintos: " + pair.getY()));
        panel.getChildren().add(new Label("Query Time: " + time));
        if (this.resultsCallback != null)
            resultsCallback.run(panel);

    }

    /**
     * Configura o callback usado para apresentar os resultados
     *
     * @param callback o callback
     */
    @Override
    public void addShowResultsCallback(NodeCallback callback) {
        this.resultsCallback = callback;
    }
}
