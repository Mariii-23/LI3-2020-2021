package main.java.li3.grupo54.Models;

import main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

import java.util.Objects;

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

    public User(String[] linhaSplit) throws InvalidUserLineException {
      // apesar de os amigos serem ignorados, o campo tem que existir
      if(linhaSplit.length != 3) {
        throw new InvalidUserLineException();
      }
      else {
        this.userId = linhaSplit[0];
        this.name = linhaSplit[1];
      }
    }

    public String getUserId() {
    return userId;
  }

  public String getName() {
    return name;
  }

  public void setUserId(String userId) {
    this.userId = userId;
  }

  public void setName(String name) {
    this.name = name;
  }
  public User clone(){
    return new User(this);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    User user = (User) o;
    return Objects.equals(getUserId(), user.getUserId()) && Objects.equals(getName(), user.getName());
  }

  @Override
  public int hashCode() {
    return Objects.hash(getUserId(), getName());
  }
  @Override
  public String toString() {
    return "User{" +
            "userId='" + userId + '\'' +
            ", name='" + name + '\'' +
            '}';
  }
}
