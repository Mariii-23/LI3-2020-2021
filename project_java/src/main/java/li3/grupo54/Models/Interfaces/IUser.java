package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.util.List;

/**
 *  Interface whose methods need be implemented by any class which wants to have the behaviour of a user.
 */

public interface IUser extends Serializable {
  public String getId();

  public String getName();

  public List<String> getFriends();

  public IUser clone();
}
