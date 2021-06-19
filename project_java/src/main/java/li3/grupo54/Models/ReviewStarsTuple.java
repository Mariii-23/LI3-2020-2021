package li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;

public class ReviewStarsTuple extends StarsTuple {
  private final Set<String> reviews;


  public ReviewStarsTuple() {
    super();
    reviews = new HashSet<>();
  }

  public ReviewStarsTuple(Review review) {
    super(review.getStars(), 1);
    reviews = new HashSet<>();
  }

  public void updateAverage(Review review) {
    super.update(review.getStars());
    reviews.add(review.getReviewId());
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
}
