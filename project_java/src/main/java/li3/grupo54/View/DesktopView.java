package li3.grupo54.View;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import javafx.stage.Stage;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.IQueryViewFX;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DesktopView implements IView {
  private Stage stage;
  private FXMLLoader loader;
  private List<IQueryViewFX> queries;

  @FXML
  private Accordion queryAccordion;

  public DesktopView(Stage s) {
    this.stage = s;
    this.queries = new ArrayList<>();
    loader = new FXMLLoader(getClass().getResource("main_ui.fxml"));
    loader.setController(this);
  }

  public void show() {
    stage.setTitle("Sistema de Gestão de Reviews");
    try {
      stage.setScene(new Scene(loader.load(), 1280, 768));
    } catch (IOException e) {
      // Fazemos isto porque, desde que o programa tenha sido bem compilado, é impossível de acontecer
      throw new UncheckedIOException(e);
    }

    queryAccordion.getPanes().clear();

    for (IQueryViewFX query : queries) {
      TitledPane pane = new TitledPane();
      ScrollPane scrollPane = new ScrollPane();
      VBox box = new VBox();
      Label descricao = new Label("Descrição");
      TextFlow flow = new TextFlow();
      Text text = new Text(query.getDescription());
      Button execute = new Button("Executar");
      execute.setMaxWidth(Double.MAX_VALUE);
      execute.setMaxHeight(Double.MAX_VALUE);
      execute.setDisable(true);
      HBox.setHgrow(execute, Priority.ALWAYS);

      query.setValidationCallback(valid -> {
        execute.setDisable(!valid);
      });

      GridPane grid = new GridPane();

      int i = 0;
      for (Map.Entry<String, Node> entry : query.getConfigOptionsNode().entrySet()) {
        grid.add(new Label(entry.getKey()), 0, i);
        Node n = entry.getValue();
        grid.add(n, 1, i);
        i++;
      }

      ColumnConstraints gridConstraint = new ColumnConstraints();
      gridConstraint.setFillWidth(true);
      gridConstraint.setHgrow(Priority.ALWAYS);
      grid.getColumnConstraints().addAll(gridConstraint, gridConstraint);
      grid.setVgap(5);

      flow.getChildren().add(text);
      box.setSpacing(5);
      descricao.setFont(new Font("System Bold", 13));

      box.getChildren().addAll(descricao, flow, grid, new HBox(execute));

      scrollPane.setFitToWidth(true);
      scrollPane.setContent(box);
      scrollPane.setPadding(new Insets(5));
      pane.setText(query.getName());
      pane.setContent(scrollPane);

      queryAccordion.getPanes().add(pane);
    }

    stage.show();
  }

  @Override
  public FileTriple getFileTriple() {
    OpenFileDialog dialog = new OpenFileDialog(this.stage);
    return dialog.showAndWait();
  }

  @Override
  public void showError(String title, String description) {
    Alert error = new Alert(Alert.AlertType.ERROR);
    error.setTitle(title);
    error.setHeaderText(description);
    error.showAndWait();
  }

  @Override
  public void addQuery(IQueryView query) {
    if (query instanceof IQueryViewFX)
      queries.add((IQueryViewFX) query);
  }

  @FXML
  private void openFile() {
    getFileTriple();
  }
}
