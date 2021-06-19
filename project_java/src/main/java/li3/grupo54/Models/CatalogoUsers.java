package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.InvalidUserLineException;
import li3.grupo54.Models.Exceptions.UserNotFoundException;
import li3.grupo54.Models.Interfaces.ICatalog;

import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class CatalogoUsers implements ICatalog<User> {
  private final Map<String, User> byUserId;
  private int invalidUsers;

  public CatalogoUsers() {
    this.byUserId = new HashMap<>();
    this.invalidUsers =0;
  }

  @Override
  public User callConstructor(String[] line) throws InvalidUserLineException {
    return new User(line);
  }

  public int size() {
    return this.byUserId.size();
  }

  public User getById(String id) {
    return byUserId.get(id).clone();
  }

  public void add(User user) {
    this.byUserId.put(user.getId(), user.clone());
  }

  public void delete(String id) throws UserNotFoundException {
    if (this.byUserId.get(id) == null ) throw new UserNotFoundException();
    else {
      byUserId.remove(id);
    }
  }

  public void addInvalid(){
    this.invalidUsers++;
  }

  public int getInvalidUsers() {
    return invalidUsers;
  }

  public boolean containsUserById(String userId){
    return this.byUserId!=null && this.byUserId.containsKey(userId);
  }
}