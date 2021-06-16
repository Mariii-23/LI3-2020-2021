package li3.grupo54.Models;

import javafx.util.Pair;
import li3.grupo54.Models.Exceptions.DateNotFoundException;
import li3.grupo54.Models.Exceptions.InvalidBusinessLineException;
import li3.grupo54.Models.Exceptions.InvalidReviewLineException;
import li3.grupo54.Models.Exceptions.InvalidUserLineException;

import java.time.LocalDateTime;
import java.util.*;

public class CatalogoReviews implements ICatalog<Review> {
  private final Map<Integer, List<Set<Review>>> anoToReviewsPerMonth;
  // ano =>  array de 12 elementos => cada array tem um set de reviews

  private final Map<String, Review> byReviewId;

  private int invalidUsers;
  private int zeroImpact;

  public CatalogoReviews() {
    this.anoToReviewsPerMonth = new HashMap<>();
    this.byReviewId = new HashMap<>();
     this.invalidUsers =0;
     this.zeroImpact=0;
  }

  @Override
  public Review callConstructor(String[] line) throws InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineException {
    return new Review(line);
  }

  @Override
  public int size() {
    // TODO Verificar
    // int count=0;
    // for(Map.Entry<Integer,List<Set<Review>>> elem : anoToReviewsPerMonth.entrySet()){
    //     for (Set<Review> reviews : elem.getValue())
    //         count+= reviews.size();
    // }
    // return count;
    return this.byReviewId.size();
  }

  @Override
  public void add(Review review) {
    // TODO Verificar
    Review reviewClone = review.clone();

    LocalDateTime date = reviewClone.getDate();
    List<Set<Review>> list = this.anoToReviewsPerMonth.get(date.getYear());
    if (list == null) {
      list = new ArrayList<>(12);
    }
    Set<Review> set = list.get(date.getMonthValue() - 1);
    if (set == null) {
      set = new HashSet<>();
    }
    set.add(review);

    if(reviewClone.impact())
      this.zeroImpact++;

    this.byReviewId.put(reviewClone.getReviewId(), reviewClone);
  }

  public Integer getInvalidUsers() {
    return invalidUsers;
  }

  public void addInvalid(){
    this.invalidUsers++;
  }

  @Override
  public Review getById(String id) {
    return byReviewId.get(id).clone();
  }

  @Override
  public void delete(String id) {
    // TODO

  }

  public Set<Review> getReviews(Integer year, Integer month) throws DateNotFoundException {
    List<Set<Review>> listOfReviews = null;
    if ((listOfReviews = this.anoToReviewsPerMonth.get(year)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    Set<Review> reviews = null;
    if ((reviews = listOfReviews.get(month - 1)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    Set<Review> result = new HashSet<>();
    for (Review review : reviews)
      result.add(review.clone());
    return result;
  }

  public Integer getNumberReviewsDate(Integer year, Integer month) throws DateNotFoundException {
    List<Set<Review>> listOfReviews = null;
    if ((listOfReviews = this.anoToReviewsPerMonth.get(year)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    Set<Review> reviews = null;
    if ((reviews = listOfReviews.get(month - 1)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    return reviews.size();
  }

  private int getNumberDistinctUsers() {
    // TODO Verificar
    Set<String> distintUsers = new HashSet<>();
    for (Map.Entry<Integer, List<Set<Review>>> elem : anoToReviewsPerMonth.entrySet()) {
      for (Set<Review> reviews : elem.getValue())
        for (Review review : reviews)
          distintUsers.add(review.getUserId());
    }
    return distintUsers.size();
  }

  private int getNumberDistinctUsers(Integer year, Integer month) throws DateNotFoundException {
    Set<String> distintUsers = new HashSet<>();
    Set<Review> reviews = this.getReviews(year, month);
    for (Review review : reviews)
      distintUsers.add(review.getUserId());
    return distintUsers.size();
  }

  // numero total de reviews e quantos users distintos as realizaram
  // para a query 2
  public Pair<Integer, Integer> getNumberReviewsAndDistinctUsers(Integer year, Integer month) throws DateNotFoundException {
    return new Pair<>(getNumberReviewsDate(year, month), getNumberDistinctUsers());
    //return new Pair<>(size(),getNumberDistinctUsers());
  }

}
