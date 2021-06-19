package li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;

/**
 * Classe que guarda e atualiza uma média consoante uma dada Review.
 * Guardará também um set de ids de reviews (e dos seus users id) recebidas até ao momento.
 */
public class BusinessStarsTuple extends StarsTuple {
  /**
   * Guarda todos os ids de reviews analisadas.
   */
  private final Set<String> reviews;
  /**
   * Guarda todos os ids dos users de cada reviews analisadas.
   */
  private final Set<String> users;

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

  /**
   * Atualiza os campos dos sets consoante a informação contida na review dada e da sua média.
   * @param review Review a ser analisada
   */
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
    return new HashSet<>(reviews);
  }
}
