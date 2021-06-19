package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.InvalidUserLineException;
import li3.grupo54.Models.Exceptions.UserNotFoundException;
import li3.grupo54.Models.Interfaces.ICatalog;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

/**
 * Classe responsável por armazenar um conjunto de Users
 */
public class CatalogoUsers implements ICatalog<User>, Serializable {

  /**
   * Hash Map de user id para o seu respetivo User.
   */
  private final Map<String, User> byUserId;
  private int invalidUsers;

  public CatalogoUsers() {
    this.byUserId = new HashMap<>();
    this.invalidUsers = 0;
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
    if (this.byUserId.get(id) == null) throw new UserNotFoundException();
    else {
      byUserId.remove(id);
    }
  }

  public void addInvalid() {
    this.invalidUsers++;
  }

  public int getInvalidUsers() {
    return invalidUsers;
  }

  /**
   * Verifica se um determinado user existe consoante o seu id.
   * @param userId User id
   * @return Caso exista retorna true, caso contrário false.
   */
  public boolean containsUserById(String userId) {
    return this.byUserId != null && this.byUserId.containsKey(userId);
  }
}