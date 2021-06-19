package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.util.Set;

/**
 *  Interface whose methods need be implemented by any class which wants to have the behaviour of a business.
 */
public interface IBusiness extends Serializable {
  public String getId();

  public String getName();

  public String getCity();

  public String getState();

  public Set<String> getCategories();

  public IBusiness clone();
}
