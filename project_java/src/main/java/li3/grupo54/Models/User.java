package li3.grupo54.Models;

public class User {
  private String userId;
  private String name;

  public User(String userId, String name) {
    this.userId = userId;
    this.name = name;
  }

  public User(User that) {
    this.userId = that.getUserId();
    this.name = that.getName();
  }
  public String getUserId() {
    return userId;
  }

  public String getName() {
    return name;
  }

  public User clone(User user){
    return new User(user);
  }

  // equals e to string
}
