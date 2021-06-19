package li3.grupo54.View;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;
import li3.grupo54.Models.FileTriple;

import java.io.File;
import java.io.IOException;
import java.io.UncheckedIOException;

public class OpenFileDialog {
  private FXMLLoader loader;
  private Stage stage;

  private File users;
  private File businesses;
  private File reviews;

  private File directory;

  private boolean ok;

  @FXML
  private Button btnUsers;
  @FXML
  private Button btnBusinesses;
  @FXML
  private Button btnReviews;
  @FXML
  private Button btnOpen;
  @FXML
  private Button btnDefault;

  public OpenFileDialog(Stage parent) {
    stage = new Stage();
    stage.initModality(Modality.WINDOW_MODAL);
    stage.initOwner(parent);
    stage.setTitle("Abrir ficheiros");
    loader = new FXMLLoader(getClass().getResource("/open_dialog.fxml"));
    loader.setController(this);
    ok = false;
  }

  public FileTriple showAndWait() {
    try {
      stage.setScene(new Scene(loader.load()));
    } catch (IOException e) {
      // Mesmo raciocinio que em DesktopView
      throw new UncheckedIOException(e);
    }

    stage.showAndWait();

    String fUser = "users.csv";
    String fReview = "reviews.csv";
    String fBusiness = "businesses.csv";
    if(users != null && reviews != null && businesses != null) {
      fUser = users.getAbsolutePath();
      fReview = reviews.getAbsolutePath();
      fBusiness = businesses.getAbsolutePath();
    }
    if (!ok)
      return null;
    return new FileTriple(fUser,fBusiness, fReview);
  }

  private File showDialog(String title) {
    FileChooser fc = new FileChooser();
    fc.setTitle("Escolher ficheiro de " + title);
    fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("Ficheiros CSV", "*.csv"));
    if (directory != null)
      fc.setInitialDirectory(directory);
    File file = fc.showOpenDialog(this.stage);
    if (file != null)
      directory = file.getParentFile();
    return file;
  }

  private void updateUI() {
    int count = 0;
    if (users != null) {
      btnUsers.setText(users.getName());
      count++;
    }
    if (businesses != null) {
      btnBusinesses.setText(businesses.getName());
      count++;
    }
    if (reviews != null) {
      btnReviews.setText(reviews.getName());
      count++;
    }

    ok = count == 3;
    btnOpen.setDisable(!ok);
  }

  @FXML
  private void pickUsers() {
    File f = showDialog("utilizadores");
    if (f != null)
      this.users = f;
    updateUI();
  }

  @FXML
  private void pickBusinesses() {
    File f = showDialog("negócios");
    if (f != null)
      this.businesses = f;
    updateUI();
  }

  @FXML
  private void pickReviews() {
    File f = showDialog("reviews");
    if (f != null)
      this.reviews = f;
    updateUI();
  }

  @FXML
  private void open() {
    if (users != null && businesses != null && reviews != null)
      stage.close();
  }
  @FXML
  private void defaultBt() {
    stage.close();
    ok = true;
  }
}
