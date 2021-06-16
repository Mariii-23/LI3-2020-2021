package li3.grupo54.View;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;
import li3.grupo54.Models.FileTriple;

import java.io.IOException;
import java.io.UncheckedIOException;

public class DesktopView implements IView {
  private Stage stage;
  private FXMLLoader loader;

  public DesktopView(Stage s) {
    this.stage = s;
    loader = new FXMLLoader(getClass().getResource("main_ui.fxml"));
    loader.setController(this);
  }

  public void show() {
    stage.setTitle("Sistema de Gestão de Reviews");
    try {
      stage.setScene(new Scene(loader.load()));
    } catch (IOException e) {
      // Fazemos isto porque, desde que o programa tenha sido bem compilado, é impossível de acontecer
      throw new UncheckedIOException(e);
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

  @FXML
  private void openFile() {
    getFileTriple();
  }
}
