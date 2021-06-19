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
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import li3.grupo54.Controller.CallbackFileTriple;
import li3.grupo54.Controller.SaveCallback;
import li3.grupo54.Controller.ExecuteCallback;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.View.Queries.IQueryView;
import li3.grupo54.View.Queries.IQueryViewFX;

import java.io.File;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DesktopView implements IView {
  private Stage stage;
  private FXMLLoader loader;
  private List<Map.Entry<IQueryViewFX, ExecuteCallback>> queries;

  @FXML
  private Accordion queryAccordion;
  @FXML
  private Tab statsTab;
  @FXML
  private TabPane resultsTabs;

//  @FXML
//  private Tab statsTab;

  private int nQueries;

  private CallbackFileTriple callback;
  private SaveCallback saveCallback;
  private SaveCallback restoreCallback;

  public DesktopView(Stage s) {
    this.stage = s;
    this.queries = new ArrayList<>();
    loader = new FXMLLoader(getClass().getResource("/main_ui.fxml"));
    loader.setController(this);
    nQueries = 0;
  }

  public void show() {
    stage.setTitle("Sistema de Gestão de Reviews");
    try {
      stage.setScene(new Scene(loader.load(), 1280, 768));
    } catch (IOException e) {
      // Fazemos isto porque, desde que o programa tenha sido bem compilado, é impossível de acontecer
      throw new UncheckedIOException(e);
    }

    queryAccordion.setDisable(true);
    queryAccordion.getPanes().clear();

    for (Map.Entry<IQueryViewFX, ExecuteCallback> query : queries) {
      TitledPane pane = new TitledPane();
      ScrollPane scrollPane = new ScrollPane();
      VBox box = new VBox();
      Label descricao = new Label("Descrição");
      TextFlow flow = new TextFlow();
      Text text = new Text(query.getKey().getDescription());
      Button execute = new Button("Executar");
      execute.setOnAction(e -> {
        try {
          query.getValue().run();
        } catch (Exception ex) {
          showError("Failed to run query '" + query.getKey().getName(), ex.getMessage());
        }
      });
      execute.setMaxWidth(Double.MAX_VALUE);
      execute.setMaxHeight(Double.MAX_VALUE);
      execute.setDisable(true);
      HBox.setHgrow(execute, Priority.ALWAYS);

      query.getKey().setValidationCallback(valid -> {
        execute.setDisable(!valid);
      });

      GridPane grid = new GridPane();

      int i = 0;
      for (Map.Entry<String, Node> entry : query.getKey().getConfigOptionsNode().entrySet()) {
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
      pane.setText(query.getKey().getName());
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
  public File getSaveLocation() {
    FileChooser fc = new FileChooser();
    fc.setInitialFileName("gestReviews.dat");
    fc.setTitle("Save object file");
    return fc.showSaveDialog(this.stage);
  }

  @Override
  public void showError(String title, String description) {
    Alert error = new Alert(Alert.AlertType.ERROR);
    error.setTitle(title);
    error.setHeaderText(description);
    error.showAndWait();
  }

  @Override
  public void setOpenCallback(CallbackFileTriple callback) {
    this.callback = callback;
  }

  @Override
  public void addQuery(IQueryView query, ExecuteCallback callback) {
    if (query instanceof IQueryViewFX) {
      queries.add(new AbstractMap.SimpleEntry<>((IQueryViewFX) query, callback));
      ((IQueryViewFX) query).addShowResultsCallback(node -> {
        nQueries++;
        Tab tab = new Tab("Resultado (" + nQueries + ")");
        tab.setContent(node);
        tab.setClosable(true);
        resultsTabs.getTabs().add(tab);
      });
    }
  }

  public void setOnSave(SaveCallback onGravar) {
    this.saveCallback = onGravar;
  }

  @FXML
  private void openFile() {
    if (callback != null) {
      FileTriple t = getFileTriple();
      if (t != null) {
        callback.run(t);
      }
    }
  }

  @FXML
  private void onSave() throws IOException {
    if (saveCallback != null) {
      File f = getSaveLocation();
      if (f != null)
          saveCallback.run(f);
    }
  }

  @FXML
  private void onRestore() throws IOException {
    if(restoreCallback != null) {
        FileChooser s = new FileChooser();
        final var f = s.showOpenDialog(stage);
        if (f != null)
           restoreCallback.run(new File(f.getAbsolutePath()));
    }
  }

  @Override
  public void disableQueries(boolean disable) {
    queryAccordion.setDisable(disable);
  }

  public void setOnRestore(SaveCallback callback) {
      this.restoreCallback = callback;

  }
}
