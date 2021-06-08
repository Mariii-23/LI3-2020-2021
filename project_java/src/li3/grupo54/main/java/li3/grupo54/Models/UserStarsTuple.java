package li3.grupo54.main.java.li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;

public class UserStarsTuple extends StarsTuple{
  // possivelmente este pode ser eliminado
  private  Set<String> reviews;
  private  Set<String> business;

  public UserStarsTuple(){
    super();
    reviews = new HashSet<>();
    business = new HashSet<>();
  }

  public UserStarsTuple(Review review){
    super(review.getStars(), 1);
    reviews = new HashSet<>();
    reviews.add(review.getReviewId());
    business.add(review.getBusinessId());
  }

  public void updateAverage(Review review){
    super.update(review.getStars());
    reviews.add(review.getReviewId());
    business.add(review.getBusinessId());
  }

  public double getCurrentAverrage() {
    return super.getCurrentAverrage();
  }

  public int getReviewsNumber(){
    return super.getNumberTotal();
  }

  public Set<String> getReviews() {
    Set<String> reviewsClonned = new HashSet<>(reviews);
    return reviewsClonned;
  }

  public Set<String> getBusiness() {
    Set<String> businessClonned = new HashSet<>(business);
    return businessClonned;
  }
}
