package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.time.LocalDateTime;


/**
 *  Interface whose methods need be implemented by any class which wants to have the behaviour of a review.
 */

public interface IReview extends Serializable {
  public String getReviewId();

  public String getUserId();

  public String getBusinessId();

  public float getStars();

  public int getUseful();

  public int getFunny();

  public int getCool();

  public LocalDateTime getDate();

  public String getText();

  public IReview clone();
}
