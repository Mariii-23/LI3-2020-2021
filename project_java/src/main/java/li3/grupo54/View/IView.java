package li3.grupo54.View;

import li3.grupo54.Controller.CallbackFileTriple;
import li3.grupo54.Controller.SaveCallback;
import li3.grupo54.Controller.ExecuteCallback;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.View.Queries.IQueryView;

import java.io.File;

public interface IView {
  public void show();

  public FileTriple getFileTriple();

  public void showError(String title, String description);

  public void setOpenCallback(CallbackFileTriple callback);

  public void addQuery(IQueryView query, ExecuteCallback callback);

  public void setOnSave(SaveCallback callback);

  //public void setStatus();

  public File getSaveLocation();

  public void disableQueries(boolean disable);

  void setOnRestore(SaveCallback callback);
}
