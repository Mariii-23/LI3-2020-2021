package li3.grupo54.Models.Interfaces;

import java.util.List;

public interface IUser {
  public String getId();

  public String getName();

  public List<String> getFriends();

  public IUser clone();
}
