package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.DateNotFoundException;
import li3.grupo54.Models.Exceptions.InvalidReviewLineException;
import li3.grupo54.Models.Exceptions.ReviewNotFoundException;
import li3.grupo54.Models.Interfaces.ICatalog;
import li3.grupo54.Utils.MyPair;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.*;

/**
 * Catálogo responsável por armazenar um conjunto de reviews.
 */
public class CatalogoReviews implements ICatalog<Review>, Serializable {
  // ano =>  array de 12 elementos => cada array tem um set de reviews
  /**
   * Um hashMap que vai de um determinado ano para uma lista de 12 elementos (cada indice dessa mesma lista
   * corresponderá a um mês). Em que cada posição conterá um set de reviews efetuadas nesse mesmo ano e mês.
   */
  private final Map<Integer, List<Set<Review>>> anoToReviewsPerMonth;
  /**
   * Um hash Map que irá de business id para business.
   */
  private final Map<String, Review> byReviewId;
  /**
   * Representa o número de users inválidos aquando a leitura das reviews.
   */
  private int invalidUsers;
  /**
   * Representa o número das reviews com zero impacto.
   * Ou seja, todas as reviews em que o somatório dos campos cool, funny ou useful dá 0.
   */
  private int zeroImpact;

  public CatalogoReviews() {
    this.anoToReviewsPerMonth = new HashMap<>();
    this.byReviewId = new HashMap<>();
    this.invalidUsers = 0;
    this.zeroImpact = 0;
  }


  @Override
  public Review callConstructor(String[] line) throws InvalidReviewLineException {
    return new Review(line);
  }

  @Override
  public int size() {
    return this.byReviewId.size();
  }

  @Override
  public void add(Review review) {
    LocalDateTime data = review.getDate();
    int ano = data.getYear();
    int mes = data.getMonthValue() - 1;
    // ver se o ano existe
    List<Set<Review>> listaAnos = this.anoToReviewsPerMonth.get(ano);
    // a lista nunca e vazia por isso se e  null e porque a key nao existe
    Set<Review> s = null;
    if (listaAnos == null) {
      listaAnos = new ArrayList<>(12);
      for (int i = 0; i < 12; i++) {
        if (i == mes) {
          s = new HashSet<>();
          listaAnos.add(i, s);
        } else {
          listaAnos.add(i, null);
        }
      }
      this.anoToReviewsPerMonth.put(ano, listaAnos);
    } else {
      s = listaAnos.get(mes);
    }

    Review reviewClone = review.clone();
    if (s != null) s.add(reviewClone);
    else {
      s = new HashSet<>();
      s.add((reviewClone));
      listaAnos.set(mes, s);
    }
    if (review.impact())
      this.zeroImpact++;

    this.byReviewId.put(review.getReviewId(), reviewClone);

  }

  public Integer getInvalidUsers() {
    return invalidUsers;
  }

  public void addInvalid() {
    this.invalidUsers++;
  }

  @Override
  public Review getById(String id) {
    return byReviewId.get(id).clone();
  }

  @Override
  public void delete(String id) throws ReviewNotFoundException {
    // TODfizemos com O

  }

  public Integer getNumberReviewsDate(Integer year, Integer month) throws DateNotFoundException {
    if (this.anoToReviewsPerMonth.size() == 0)
      return 0;
    List<Set<Review>> listOfReviews = null;
    if ((listOfReviews = this.anoToReviewsPerMonth.get(year)) != null) {
      Set<Review> reviews = null;
      if ((reviews = listOfReviews.get(month - 1)) == null)
        throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
      return reviews.size();
    } else {
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    }
  }

  public Integer getNumberDistinctUsers(Integer year, Integer month) throws DateNotFoundException {
    List<Set<Review>> listOfReviews = null;
    if ((listOfReviews = this.anoToReviewsPerMonth.get(year)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    Set<Review> reviews = null;
    if ((reviews = listOfReviews.get(month - 1)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);

    HashSet<String> users = new HashSet<>();
    for (Review review : reviews)
      users.add(review.getUserId());

    return users.size();
  }

  private int getNumberDistinctUsers() {
    Set<String> distintUsers = new HashSet<>();
    for (Map.Entry<Integer, List<Set<Review>>> elem : anoToReviewsPerMonth.entrySet()) {
      for (Set<Review> reviews : elem.getValue())
        if (reviews != null) {
          for (Review review : reviews)
            distintUsers.add(review.getUserId());
        }
    }
    return distintUsers.size();
  }

  /**
   * Auxílicio -> Query 2
   * Retorna um par com o número total de reviews e o número de users distintos que as realizaram.
   * @param year Ano
   * @param month Mês
   * @return Par obtido
   */
  public MyPair<Integer, Integer> getNumberReviewsAndDistinctUsers(Integer year, Integer month) throws  DateNotFoundException {
    int reviews = getNumberReviewsDate(year, month);
    int users = getNumberDistinctUsers(year, month);
    return new MyPair<>(reviews, users);
  }

  public Map<Integer, List<Set<Review>>> getAnoToReviewsPerMonth() {
    return anoToReviewsPerMonth;
  }

  /**
   * Devolve o clone de uma review a partir do seu id
   * @param id Review Id
   * @return Review
   */
  public Review getReviewById(String id) {
    return this.byReviewId.get(id).clone();
  }

  public Map<String, Review> getByReviewId() {
    return byReviewId;
  }

  /**
   * Devolve o número de reviews com zero impacto.
   * @return Inteiro.
   */
  public int getZeroImpact() {
    return zeroImpact;
  }
}

