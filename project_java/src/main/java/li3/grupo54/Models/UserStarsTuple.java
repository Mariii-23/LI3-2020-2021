package li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;
import java.io.Serializable;

public class UserStarsTuple extends StarsTuple implements Serializable {
  private final Set<String> reviews;
  private Set<String> business;

  public UserStarsTuple() {
    super();
    reviews = new HashSet<>();
    business = new HashSet<>();
  }

  public UserStarsTuple(Review review) {
    super(review.getStars(), 1);
    reviews = new HashSet<>();
    reviews.add(review.getReviewId());
    business = new HashSet<>();
    business.add(review.getBusinessId());
  }

  public void updateAverage(Review review) {
    super.update(review.getStars());
    reviews.add(review.getReviewId());
    business.add(review.getBusinessId());
  }

  public double getCurrentAverage() {
    return super.getCurrentAverage();
  }

  public int getReviewsNumber() {
    return super.getNumberTotal();
  }

  public int getBusinessNumberDistint() {
    return this.business.size();
  }

  public Set<String> getReviews() {
    return new HashSet<>(reviews);
  }

  public Set<String> getBusiness() {
    return new HashSet<>(business);
  }
}
