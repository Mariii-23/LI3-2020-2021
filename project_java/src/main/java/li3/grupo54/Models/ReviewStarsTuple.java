package li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;

public class ReviewStarsTuple extends StarsTuple {
  private final Set<String> reviews;
  private final Set<String> users;
  private final Set<String> business;


  public ReviewStarsTuple() {
    super();
    reviews = new HashSet<>();
    users = new HashSet<>();
    business = new HashSet<>();
  }

  public ReviewStarsTuple(Review review) {
    super(review.getStars(), 1);
    reviews = new HashSet<>();
    users = new HashSet<>();
    business = new HashSet<>();
  }

  public void updateAverage(Review review) {
    super.update(review.getStars());
    reviews.add(review.getReviewId());
    users.add(review.getUserId());
    business.add(review.getBusinessId());
  }

  public double getCurrentAverage() {
    return super.getCurrentAverage();
  }

  public int getReviewsNumber() {
    return super.getNumberTotal();
  }

  public Set<String> getReviews() {
    return new HashSet<>(reviews);
  }

  public Integer getUserDistints(){
    return this.users.size();
  }

  public Integer getBusinessDistints() {
    return this.business.size();
  }
}
