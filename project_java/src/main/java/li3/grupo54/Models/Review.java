package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.InvalidReviewLineException;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Review implements IReview {
  private final String reviewId;
  private final String userId;
  private final String businessId;
  private final float stars;
  private final int useful;
  private final int funny;
  private final int cool;
  private final LocalDateTime date;
  private final String text;

  public Review(String reviewId, String userId, String businessId, float stars, int useful, int funny, int cool, LocalDateTime date, String text) {
    this.reviewId = reviewId;
    this.userId = userId;
    this.businessId = businessId;
    this.stars = stars;
    this.useful = useful;
    this.funny = funny;
    this.cool = cool;
    this.date = date;
    this.text = text;
  }

  public Review(Review that) {
    this.reviewId = that.getReviewId();
    this.userId = that.getUserId();
    this.businessId = that.getBusinessId();
    this.stars = that.getStars();
    this.useful = that.getUseful();
    this.funny = that.getFunny();
    this.cool = that.getCool();
    this.date = that.getDate();
    this.text = that.getText();
  }

  public Review(String[] linhaSplit) throws InvalidReviewLineException {
    if (linhaSplit.length != 9) {
      throw new InvalidReviewLineException();
    } else {
      this.reviewId = linhaSplit[0];
      this.userId = linhaSplit[1];
      this.businessId = linhaSplit[2];
      this.stars = Float.parseFloat(linhaSplit[3]);
      this.useful = Integer.parseInt(linhaSplit[4]);
      this.funny = Integer.parseInt(linhaSplit[5]);
      this.cool = Integer.parseInt(linhaSplit[6]);
      this.date = LocalDateTime.parse(linhaSplit[7], DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
      this.text = linhaSplit[8];
    }
  }

  public boolean impact(){
    return this.cool +this.useful+this.funny==0;
  }

  @Override
  public String getReviewId() {
    return reviewId;
  }

  @Override
  public String getText() {
    return text;
  }

  @Override
  public String getUserId() {
    return userId;
  }

  @Override
  public String getBusinessId() {
    return businessId;
  }

  @Override
  public float getStars() {
    return stars;
  }

  @Override
  public int getUseful() {
    return useful;
  }

  @Override
  public int getFunny() {
    return funny;
  }

  @Override
  public int getCool() {
    return cool;
  }

  @Override
  public LocalDateTime getDate() {
    return date;
  }

  @Override
  public Review clone() {
    return new Review(this);
  }
}
