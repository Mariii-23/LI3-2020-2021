package li3.grupo54.View.Queries;

import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.control.TextField;
import li3.grupo54.Controller.NodeCallback;
import li3.grupo54.Controller.ValidationCallback;
import li3.grupo54.Models.MyPair;
import li3.grupo54.Models.Queries.IQueryResults;
import li3.grupo54.Models.Queries.Query2Results;

import java.util.HashMap;
import java.util.Map;

public class Query2View implements IQueryViewFX {
    private TextField monthInput;
    private TextField yearInput;

    private ValidationCallback callback;
    private NodeCallback resultsCallback;

    private boolean validAno;
    private boolean validMes;

    private Integer ano;
    private Integer mes;

public Integer getAno(){
    return ano;
}

    public Integer getMes(){
        return mes;
    }
    public Query2View() {
        ano=-1;
        mes=-1;
        monthInput = new TextField();
        yearInput = new TextField();

        monthInput.textProperty().addListener((o, oldVal, newVal) -> {
            // Remover tudo o que não são números
            if (!newVal.matches("\\d*"))
                monthInput.setText(newVal.replaceAll("[^\\d]", ""));

            try {
                int v = Integer.parseInt(monthInput.getText());
                if (v > 0 && v <= 12) {
                    mes=v;
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
                    ano=v;
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

    @Override
    public String getName() {
        return "Reviews num mês";
    }

    @Override
    public String getDescription() {
        return "Dado um mês e um ano (válidos), determinar o número total global de reviews realizadas e o número total de users distintos que as realizaram.";
    }

    @Override
    public Map<String, Node> getConfigOptionsNode() {
        Map<String, Node> map = new HashMap<>();
        map.put("Ano", yearInput);
        map.put("Mês", monthInput);
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
        Query2Results res = (Query2Results) results;

         MyPair<Integer,Integer> pair = res.getResults();

        VBox panel = new VBox();
        panel.setPadding(new Insets(5));

        panel.setSpacing(5);
        panel.getChildren().add(new Label("Total reviews: " +pair.getX()+" Total users distintos: "+pair.getY()));
                if (this.resultsCallback != null)
            resultsCallback.run(panel);

    }
    @Override
    public void addShowResultsCallback(NodeCallback callback) {
        this.resultsCallback = callback;
    }
}
