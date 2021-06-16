package li3.grupo54.Models;

import java.util.List;

public interface IBusiness {
  public String getId();

  public String getName();

  public String getCity();

  public String getState();

  public List<String> getCategories();
}
