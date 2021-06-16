package li3.grupo54.View;

import li3.grupo54.Models.FileTriple;

import java.io.IOException;

public interface IView {
  public void show();

  public FileTriple getFileTriple();
  public void showError(String title, String description);
}
