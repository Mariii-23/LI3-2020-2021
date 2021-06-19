package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.time.LocalDateTime;

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
