package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.Models.Exceptions.NullReviewException;
import li3.grupo54.Models.Exceptions.UserNotFoundException;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Interfaces.IStats;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.Utils.MyTriple;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class Stats implements IStats, Serializable  {
  // User id ->  mes a mes -> UserStarsTuple
  /**
   * Um Hash Map que irá de user id para uma lista de 12 elementos em que a cada índice irá corresponder um dado mês e
   * o seu elemento corresponderá um UsersStarsTuple
   */
  private final Map<String, List<UserStarsTuple>> averageByUserId;

  // Business id ->  mes a mes -> BusinessStarsTuple
  /**
   * Um Hash Map que irá de business id para uma lista de 12 elementos em que a cada índice irá corresponder um dado mês e
   * o seu elemento corresponderá a um BusinessStasrTuple
   */
  private final Map<String, List<BusinessStarsTuple>> averageByBusinessId;

  // Review Id -> mes a mes -> ReviewStarsTuple
  /**
   * Um Hash Map que irá de review id para uma lista de 12 elementos em que a cada índice irá corresponder um dado mês e
   * o seu elemento corresponderá a um ReviewStarsTuple.
   */
  private final Map<String, List<ReviewStarsTuple>> averageByReviewID;

  // State -> City -> BusinessId -> Average
  /**
   * Um Hash Map que irá de um Estado para um outro Hash Map. Aqui este irá de cidade para um outro Hash Map, business
   * id para StarsTuple.
   */
  private final Map<String, Map<String, Map<String, StarsTuple>>> averageByStateBusiness;

  /**
   * Aqui serão guardados todos os negócios que nunca foram avalidados, ordenados por ordem alfabética.
   * Business Id para Business
   */
  private final TreeMap<String, IBusiness> negociosNuncaAvaliados;
  /**
   * Um Hash Map que armazenará apenas os negócios que foram avalidados.
   * Businees Id para Business.
   */
  private final Map<String, IBusiness> negociosAvaliados;

  public Stats() {
    averageByUserId = new HashMap<>();
    averageByBusinessId = new HashMap<>();
    averageByStateBusiness = new HashMap<>();
    averageByReviewID = new HashMap<>();
    negociosAvaliados = new HashMap<>();
    negociosNuncaAvaliados = new TreeMap<>();
  }

  public void updateStats(Review review, Business business) throws NullReviewException {
    if (review == null)
      throw new NullReviewException("Null Review Exception");
    updateAverageBusiness(review);
    updateAverageUser(review);
    updateAverageReview(review);
    updateAveragebyState(review, business);
  }

  public void updateAveragebyState(Review review, IBusiness business) {
    if (!review.getBusinessId().equals(business.getId()))
      return;
    String state = business.getState();
    String city = business.getCity();
    Map<String, Map<String, StarsTuple>> map;

    if ((map = this.averageByStateBusiness.get(state)) == null) {
      map = new HashMap<>();
      Map<String, StarsTuple> mapCity = new HashMap<>();
      mapCity.put(business.getId(), new BusinessStarsTuple(review));
      map.put(city, mapCity);
      this.averageByStateBusiness.put(state, map);
    } else {
      Map<String, StarsTuple> mapCity = map.get(city);
      if (mapCity == null) {
        mapCity = new HashMap<>();
        mapCity.put(business.getId(), new BusinessStarsTuple(review));
        map.put(city, mapCity);
      } else {
        StarsTuple starTuple = mapCity.get(business.getId());
        if (starTuple == null) {
          starTuple = new StarsTuple();
        }
        starTuple.update(review.getStars());
        mapCity.put(business.getId(), starTuple);
      }
    }
  }

  public void updateAverageUser(Review review) {
    String userId = review.getUserId();
    int month = review.getDate().getMonthValue() - 1;
    List<UserStarsTuple> list = null;

    if ((list = this.averageByUserId.get(userId)) == null) {
      list = new ArrayList<>(12);
      for (int i = 0; i < 12; i++) {
        list.add(i, null);
      }
      list.set(month, new UserStarsTuple(review));
      this.averageByUserId.put(userId, list);

    } else {
      UserStarsTuple userStarsTuple = list.get(month);
      if (userStarsTuple == null)
        userStarsTuple = new UserStarsTuple();
      userStarsTuple.updateAverage(review);
      list.set(month, userStarsTuple);
    }
  }

  public void updateAverageBusiness(Review review) {
    String businessId = review.getBusinessId();
    int month = review.getDate().getMonthValue() - 1;
    List<BusinessStarsTuple> list = null;

    if ((list = this.averageByBusinessId.get(businessId)) == null) {
      list = new ArrayList<>(12);
      for (int i = 0; i < 12; i++) {
        list.add(null);
      }
      list.set(month, new BusinessStarsTuple(review));
      this.averageByBusinessId.put(businessId, list);

    } else {
      BusinessStarsTuple userStarsTuple = list.get(month);
      if (userStarsTuple == null)
        userStarsTuple = new BusinessStarsTuple();
      userStarsTuple.updateAverage(review);
      list.set(month, userStarsTuple);
    }
  }

  public void updateAverageReview(Review review) {
    String reviewId = review.getReviewId();
    int month = review.getDate().getMonthValue() - 1;
    List<ReviewStarsTuple> list = null;

    if ((list = this.averageByReviewID.get(reviewId)) == null) {
      list = new ArrayList<>(12);
      for (int i = 0; i < 12; i++) {
        list.add(null);
      }
      list.set(month, new ReviewStarsTuple(review));
      this.averageByReviewID.put(reviewId, list);

    } else {
      ReviewStarsTuple starsTuple = list.get(month);
      if (starsTuple == null)
        starsTuple = new ReviewStarsTuple();
      starsTuple.updateAverage(review);
      list.set(month, starsTuple);
    }
  }

  /**
   * Query 5
   * Devolve uma lista com pares, sendo que cada par conterá um Business Id e quantas reviews é que avaliou. Isto em
   * função de um dado user ID.
   * @param userId User Id
   * @return List
   */
  List<MyPair<String, Integer>> pairBusinessIdAndTheirReviews(String userId) throws UserNotFoundException {
    List<MyPair<String, Integer>> list = new ArrayList<>();
    // guardar todos os id's dos business correspondestes a esse user
    Set<String> businessIDs = new HashSet<>();
    var userAverage = this.averageByUserId.get(userId);
    if (userAverage == null) throw new UserNotFoundException(userId);
    userAverage.forEach(e -> {
      if (e != null)
        businessIDs.addAll(e.getBusiness());
    });

    // ir a cada business id e ir buscar o set de reviews
    // colocar isso num par (id,set)
    // assim depois pra query 5, bast trocar o id pelo nome e ordenar
    businessIDs.forEach(e -> {
      Set<String> reviews = new HashSet<>();
      this.averageByBusinessId.get(e).forEach(l -> {
        if (l != null) reviews.addAll(l.getReviews());
      });
      list.add(new MyPair<>(e, reviews.size()));
      // devolve uma lista de de (business_id, numero reviews=
    });
    return list;
  }

  public <T> void atualiza(T newEntity, CatalogoUsers catalogoUsers, CatalogoBusinesses catalogoBusinesses) {
    if (newEntity instanceof Business) {
      // inicializar a lista de businesses nunca avaliados
      this.negociosNuncaAvaliados.put(((Business) newEntity).getId(), ((Business) newEntity).clone());
    } else if (newEntity instanceof Review) {
      String businessId = ((Review) newEntity).getBusinessId();
      IBusiness b;
      if ((b = this.negociosNuncaAvaliados.remove(businessId)) != null) {
        this.negociosAvaliados.put(businessId, b);
      }

      try {
        this.updateStats((Review) newEntity, (Business) catalogoBusinesses.getBusiness(((Review) newEntity).getBusinessId()));
      } catch (Exception e) {
        e.getMessage();
      }
    }

  }

  public Set<String> getAllReviews(String businessId) {
    Set<String> allReviews = new HashSet<>();
    List<BusinessStarsTuple> list = averageByBusinessId.get(businessId);
    if (list != null) {
      for (BusinessStarsTuple tuple : list) {
        if (tuple != null)
          allReviews.addAll(tuple.getReviews());
      }
    }
    return allReviews;
  }

  // para a query 1

  /**
   * Query 1
   * @return Devolve uma lista de todos os Business que nunca foram avalidos, clonando-os.
   */
  public List<IBusiness> getNegociosNuncaAvaliadosOrdered() {
    return this.negociosNuncaAvaliados.values().stream().map(IBusiness::clone).collect(Collectors.toList());
  }

  // para a query 10
  public Map<String, Map<String, Map<String, StarsTuple>>> getAverageByStateBusiness() {
    return this.averageByStateBusiness;
  }

  /**
   * Query 3
   * Este método, consoante um user id devolve uma lista de 12 elementos, em que cada índice corresponderá a um més, e a cada posicão,
   * corresponderá um triplo com quantas reviews fez, quantosa negócios distintos avaliou e a sua nota média.
   * @param userId User id
   * @return Lista
   */
  public List<MyTriple<Integer, Integer, Double>> query3(String userId) throws UserNotFoundException {
    List<UserStarsTuple> list = this.averageByUserId.get(userId);

    if (list == null)
      throw new UserNotFoundException(userId);

    List<MyTriple<Integer, Integer, Double>> result = new ArrayList<>(12);
    for (int i = 0; i < 12; i++) {
      result.add(i, null);
    }
    int i = 0;
    for (UserStarsTuple tuple : list) {
      int numReviews = 0;
      int businessDist = 0;
      double mean = 0;
      if (tuple != null) {
        numReviews = tuple.getReviewsNumber();
        businessDist = tuple.getBusinessNumberDistint();
        mean = tuple.getCurrentAverage();
      }
      //if(numReviews!=-1 && businessDist!= -1 && mean!=-1)
      result.set(i, new MyTriple<>(numReviews, businessDist, mean));
      i++;
    }
    return result;
  }


  /**
   * Query 4
   * Este método, consoante um business id devolve uma lista de 12 elementos, em que cada índice corresponderá a um més, e a cada posicão,
   * corresponderá um triplo com quantas reviews fez, quantos users distintos avaliou e a sua nota média.
   * @param businessId business id
   * @return Lista
   */
  public List<MyTriple<Integer, Integer, Double>> query4(String businessId) throws BusinessNotFoundException {
    List<BusinessStarsTuple> list = this.averageByBusinessId.get(businessId);

    if (list == null)
      throw new BusinessNotFoundException(businessId);

    List<MyTriple<Integer, Integer, Double>> result = new ArrayList<>(12);
    for (int i = 0; i < 12; i++) {
      result.add(i, null);
    }
    int i = 0;
    for (BusinessStarsTuple tuple : list) {
      int numReviews = 0;
      int userDist = 0;
      double mean = 0;
      if (tuple != null) {
        numReviews = tuple.getReviewsNumber();
        userDist = tuple.getUsersNumber();
        mean = tuple.getCurrentAverage();
      }
      //if(numReviews!=-1 && businessDist!= -1 && mean!=-1)
      result.set(i, new MyTriple<>(numReviews, userDist, mean));
      i++;
    }
    return result;
  }

  // cidade | id negocio | numero de reviews

  /**
   * Query 7
   * Método que devolve uma lista com os três maiores negócios em termos de números de reviews em cada cidade.
   * @return Devolve um lista com um triplo, em que cada informação corresponderá à cidade, id do negócio e o número
   * de reviews efetuadas.
   */
  public List<MyTriple<String, String, Integer>> query7() {
    List<MyTriple<String, String, Integer>> r = new ArrayList<>();

    for (Map<String, Map<String, StarsTuple>> entry : averageByStateBusiness.values()) {
      if (entry == null) continue;
      for (Map.Entry<String, Map<String, StarsTuple>> entryCity : entry.entrySet()) {
        if (entryCity == null) continue;
        String city = entryCity.getKey();
        List<MyTriple<String, String, Integer>> aux = new ArrayList<>();
        for (Map.Entry<String, StarsTuple> elem : entryCity.getValue().entrySet()) {
          if (elem == null) continue;
          aux.add(new MyTriple<String, String, Integer>(city, elem.getKey(), elem.getValue().getNumberTotal()));
        }
        Comparator<MyTriple<String, String, Integer>> c = (e1, e2) -> e2.getRight() - e1.getRight();
        aux.sort(c);

        for (int i = 0; i < aux.size() && i < 3; i++) {
          MyTriple<String, String, Integer> elem = aux.get(i);
          if (elem != null) {
            r.add(elem);
          }
        }
      }
    }
    return r;
  }

  /**
   * Query 8
   * @param x Número
   * @return Devolve uma Lista  de X pares, contedo o user id e o número de negócios distintos, oredenado pela ordem
   * decrescente do número de negócios.
   */
  public List<MyPair<String, Integer>> query8(Integer x) {
    List<MyPair<String, Integer>> r = new ArrayList<>();

    for (Map.Entry<String, List<UserStarsTuple>> entry : averageByUserId.entrySet()) {
      if (entry == null) continue;
      for (UserStarsTuple elem : entry.getValue()) {
        if (elem != null)
          r.add(new MyPair<>(entry.getKey(), elem.getBusinessNumberDistint()));
      }
    }

    Comparator<MyPair<String, Integer>> c = (e1, e2) -> e2.getY() - e1.getY();
    r.sort(c);

    if (x < r.size()) {
      int size = r.size();
      for (int i = size - 1; i >= x; i--)
        r.remove(i);
    }
    return r;
  }
}

