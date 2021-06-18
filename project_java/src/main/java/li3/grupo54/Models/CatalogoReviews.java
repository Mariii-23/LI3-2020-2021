package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.*;
import li3.grupo54.Models.Interfaces.ICatalog;

import javax.swing.plaf.synth.SynthTextAreaUI;
import java.time.LocalDateTime;
import java.time.Year;
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
    Set <Review> s =  null;
      if( listaAnos== null ) {
          listaAnos = new ArrayList<>(12);
          for (int i = 0; i < 12; i++) {
              if(i == mes ) {
                s = new HashSet<>();
                listaAnos.add(i,s);
              }
              else {
                listaAnos.add(i,null);
              }
          }
          this.anoToReviewsPerMonth.put(ano,listaAnos);
      }
      else {
          s = listaAnos.get(mes);
      }

      Review reviewClone = review.clone();
      if(s != null) s.add(reviewClone);
      else{
        s = new HashSet<>();
        s.add((reviewClone));
        listaAnos.add(mes,s);
      }
      if(review.impact())
        this.zeroImpact++;

      this.byReviewId.put(review.getReviewId(), reviewClone);
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
  public void delete(String id) throws ReviewNotFoundException {
    // TODO

  }

 // public Set<Review> getReviews(Integer year, Integer month) throws DateNotFoundException {
 //   List<Set<Review>> listOfReviews = null;
 //   if ((listOfReviews = this.anoToReviewsPerMonth.get(year)) == null)
 //     throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
 //   Set<Review> reviews = null;
 //   if ((reviews = listOfReviews.get(month - 1)) == null)
 //     throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
 //   Set<Review> result = new HashSet<>();
 //   for (Review review : reviews)
 //     result.add(review.clone());
 //   return result;
 // }

  public Integer getNumberReviewsDate(Integer year, Integer month) throws DateNotFoundException {
    if(this.anoToReviewsPerMonth.size()==0)
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

  public Integer getNumberDistinctUsers(Integer year,Integer month) throws DateNotFoundException {
    List<Set<Review>> listOfReviews = null;
    if ((listOfReviews = this.anoToReviewsPerMonth.get(year)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);
    Set<Review> reviews = null;
    if ((reviews = listOfReviews.get(month - 1)) == null)
      throw new DateNotFoundException("Date not found. Year: " + year + " month: " + month);

    HashSet<String> users = new HashSet<>();
    for(Review review:reviews)
      users.add(review.getUserId());

    return users.size();
  }

  private int getNumberDistinctUsers() {
    // TODO Verificar
    Set<String> distintUsers = new HashSet<>();
    for (Map.Entry<Integer, List<Set<Review>>> elem : anoToReviewsPerMonth.entrySet()) {
      for (Set<Review> reviews : elem.getValue())
        if(reviews != null) {
          for (Review review : reviews)
            distintUsers.add(review.getUserId());
        }
    }
    return distintUsers.size();
  }

  //private int getNumberDistinctUsers(Integer year, Integer month) throws DateNotFoundException {
  //  Set<String> distintUsers = new HashSet<>();
  //  Set<Review> reviews = this.getReviews(year, month);
  //  if(reviews==null)
  //    throw  new DateNotFoundException("Date Not Found -> year: "+year+" month "+month );
  //  for (Review review : reviews)
  //    distintUsers.add(review.getUserId());
  //  return distintUsers.size();
  //}

  // numero total de reviews e quantos users distintos as realizaram
  // para a query 2
  public MyPair<Integer, Integer> getNumberReviewsAndDistinctUsers(Integer year, Integer month) {
    int reviews = 0;
    int users = 0;
    try {
      reviews = getNumberReviewsDate(year, month);
      users =  getNumberDistinctUsers(year,month);
    }
    catch (DateNotFoundException ignored) {
      System.out.println("Data not found year: "+year+" month: "+month);
    }
    return new MyPair<>(reviews,users);
    }
}
