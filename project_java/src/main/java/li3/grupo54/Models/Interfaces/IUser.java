package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.util.List;

public interface IUser extends Serializable {
  public String getId();

  public String getName();

  public List<String> getFriends();

  public IUser clone();
}
