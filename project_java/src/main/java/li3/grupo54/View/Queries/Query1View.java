package li3.grupo54.View.Queries;

import javafx.scene.Node;
import li3.grupo54.Controller.ValidationCallback;

import java.util.HashMap;
import java.util.Map;

public class Query1View implements IQueryViewFX {
    private ValidationCallback callback;

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
}
