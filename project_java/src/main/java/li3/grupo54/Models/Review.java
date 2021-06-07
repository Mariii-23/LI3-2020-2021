package main.java.li3.grupo54.Models;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Review implements IReview{
    String reviewId;
    String userId;
    String businessId;
    float stars;
    int useful;
    int funny;
    int cool;
    LocalDateTime date;
    String text;

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

    public Review(String[] linhaSplit) throws InvalidReviewLineExpcetion {
        if(linhaSplit.length != 9) {
             throw new InvalidReviewLineExpcetion();
        }
        else {
            this.reviewId = linhaSplit[0];
            this.userId = linhaSplit[1];
            this.businessId = linhaSplit[2];
            this.stars = Float.parseFloat(linhaSplit[3]);
            this.useful = Integer.parseInt(linhaSplit[4]);
            this.funny = Integer.parseInt(linhaSplit[5]);
            this.cool = Integer.parseInt(linhaSplit[6]);
            this.date = LocalDateTime.parse(linhaSplit[7],DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
            this.text = linhaSplit[8];
        }
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
}
