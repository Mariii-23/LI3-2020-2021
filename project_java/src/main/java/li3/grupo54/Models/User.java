package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.InvalidUserLineException;
import li3.grupo54.Models.Interfaces.IUser;

import java.util.List;
import java.util.Objects;

public class User implements IUser {
  private String userId;
  private String name;

  public User(String userId, String name) {
    this.userId = userId;
    this.name = name;
  }

  public User(User that) {
    this.userId = that.getId();
    this.name = that.getName();
  }

  public User(String[] linhaSplit) throws InvalidUserLineException {
    // apesar de os amigos serem ignorados, o campo tem que existir
    if (linhaSplit.length != 3) {
      throw new InvalidUserLineException();
    } else {
      this.userId = linhaSplit[0];
      this.name = linhaSplit[1];
    }
  }

  public void setUserId(String userId) {
    this.userId = userId;
  }

  @Override
  public String getId() {
    return userId;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  public List<String> getFriends() {
    return null;
  }

  public User clone() {
    return new User(this);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    User user = (User) o;
    return this.getId().equals(user.getId()) && getName().equals(user.getName());
  }

  @Override
  public int hashCode() {
    return Objects.hash(getId(), getName());
  }

  @Override
  public String toString() {
    return "User{" +
        "userId='" + userId + '\'' +
        ", name='" + name + '\'' +
        '}';
  }
}
