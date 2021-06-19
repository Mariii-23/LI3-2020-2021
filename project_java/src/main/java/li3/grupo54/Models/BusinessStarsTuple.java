package li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;

public class BusinessStarsTuple extends StarsTuple {
  private final Set<String> reviews;
  private Set<String> users;

  public BusinessStarsTuple() {
    super();
    reviews = new HashSet<>();
    users = new HashSet<>();
  }

  public BusinessStarsTuple(Review review) {
    super(review.getStars(), 1);
    reviews = new HashSet<>();
    reviews.add(review.getReviewId());
    this.users = new HashSet<>();
    users.add(review.getUserId());
  }

  public void updateAverage(Review review) {
    super.update(review.getStars());
    reviews.add(review.getReviewId());
    users.add(review.getUserId());
  }

  public double getCurrentAverage() {
    return super.getCurrentAverage();
  }

  public int getReviewsNumber() {
    return super.getNumberTotal();
  }

  public int getUsersNumber() {
    return users.size();
  }

  public Set<String> getReviews() {
    Set<String> reviewsClone = new HashSet<>(reviews);
    return reviewsClone;
  }

  public Set<String> getUsers() {
    Set<String> usersClone = new HashSet<>(users);
    return usersClone;
  }
}
