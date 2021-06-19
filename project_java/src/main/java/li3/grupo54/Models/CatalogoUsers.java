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
  /**
   * Number of invalid users received so far
   */
  private int invalidUsers;

  /**
   * The last input file used
   */
  private String inputFileName = "users.csv";

  public CatalogoUsers() {
    this.byUserId = new HashMap<>();
    this.invalidUsers = 0;
  }

  /**
   * Função que chama o construtor do User passando-lhe a linha parsed como parametro
   * @param line
   * @return Novo user
   * @throws InvalidUserLineException
   */
  @Override
  public User callConstructor(String[] line) throws InvalidUserLineException {
    return new User(line);
  }

  /**
   *
   * @return Numero de Users no catálogo
   */
  public int size() {
    return this.byUserId.size();
  }

  /**
   * Devolve o numero de users invalidos
   * @return Numero Users Invalidos
   */
  @Override
  public int getInvalidCount() {
    return invalidUsers;
  }

  /**
   * Devolve um utilizador dado um id
   * @param id
   * @return User
   */
  public User getById(String id) {
    return byUserId.get(id).clone();
  }

  /**
   *  Adiciona um user ao catálogo
   * @param user
   */
  public void add(User user) {
    this.byUserId.put(user.getId(), user.clone());
  }

  /**
   * Apaga um user do catálogo
   * @param id
   * @throws UserNotFoundException
   */
  public void delete(String id) throws UserNotFoundException {
    if (this.byUserId.get(id) == null) throw new UserNotFoundException();
    else {
      byUserId.remove(id);
    }
  }

  /**
   * Incrementa o número de users invalidos
   */
  public void addInvalid() {
    this.invalidUsers++;
  }

  /**
   * Devolve o numero de users invalidos
   * @return Users Invalidos
   */
  public int getInvalidUsers() {
    return invalidUsers;
  }

  /**
   * Verifica se um determinado user existe consoante o seu id.
   * @param userId User id
   * @return Caso exista retorna true, caso contrário false.
   */
  public boolean containsUserById(String userId) {
    return this.byUserId.containsKey(userId);
  }
  /**
   *  Devolve o nome do ficheiro de input utilizado para popular este catalogo
   * @return Nome do Ficheiro
   */
  public String getInputFileName() {
    return inputFileName;
  }

  /**
   * Altera o nome do ultimo ficeiro usado como input para construir o catalogo.
   * @param inputFileName
   */
  public void setInputFileName(String inputFileName) {
    this.inputFileName = inputFileName;
  }
}