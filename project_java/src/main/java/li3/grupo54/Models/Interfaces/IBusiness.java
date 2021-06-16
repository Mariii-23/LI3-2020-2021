package li3.grupo54.Models.Interfaces;

import java.util.Set;

public interface IBusiness {
  public String getId();

  public String getName();

  public String getCity();

  public String getState();

  public Set<String> getCategories();

  public IBusiness clone();
}
