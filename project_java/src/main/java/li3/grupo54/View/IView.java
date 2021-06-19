package li3.grupo54.View;

import li3.grupo54.Controller.CallbackFileTriple;
import li3.grupo54.Controller.EmptyCallback;
import li3.grupo54.Controller.ExecuteCallback;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.View.Queries.IQueryView;

import java.io.File;

public interface IView {
  public void show();

  public FileTriple getFileTriple();

  public void showError(String title, String description);

  public void setOpenCallback(CallbackFileTriple callback);

  public void addQuery(IQueryView query, ExecuteCallback callback);

  public void setOnSave(EmptyCallback callback);

  public File getSaveLocation();
}
