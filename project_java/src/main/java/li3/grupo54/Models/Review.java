package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.InvalidReviewLineException;
import li3.grupo54.Models.Interfaces.IReview;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Objects;

public final class Review implements IReview, Serializable {
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

    /**
     * Checks if the review has any impact in business rating
     *
     * @return
     */
    public boolean impact() {
        return this.cool + this.useful + this.funny == 0;
    }

    /**
     * Get ReviewId
     *
     * @return Review Id
     */
    @Override
    public String getReviewId() {
        return reviewId;
    }

    /**
     * Returns field text of review
     *
     * @return
     */
    @Override
    public String getText() {
        return text;
    }

    /**
     * Returns the userId of the user which made this review
     *
     * @return
     */
    @Override
    public String getUserId() {
        return userId;
    }

    /**
     * Returns the businesses id of the business which was rated in this review
     *
     * @return
     */
    @Override
    public String getBusinessId() {
        return businessId;
    }

    /**
     * Get Number of stars of the review
     *
     * @return
     */
    @Override
    public float getStars() {
        return stars;
    }

    /**
     * Get useful field of review
     *
     * @return
     */
    @Override
    public int getUseful() {
        return useful;
    }

    /**
     * Get funny field of review
     *
     * @return
     */
    @Override
    public int getFunny() {
        return funny;
    }

    /**
     * *  Get cool field of review
     *
     * @return
     */
    @Override
    public int getCool() {
        return cool;
    }

    /**
     * *  Get date of the review
     *
     * @return
     */
    @Override
    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public Review clone() {
        return new Review(this);
    }

    @Override
    public String toString() {
        return "Review{" +
                "reviewId='" + reviewId + '\'' +
                ", userId='" + userId + '\'' +
                ", businessId='" + businessId + '\'' +
                ", stars=" + stars +
                ", useful=" + useful +
                ", funny=" + funny +
                ", cool=" + cool +
                ", date=" + date +
                ", text='" + text + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Review review = (Review) o;
        return Float.compare(review.stars, stars) == 0 && useful == review.useful && funny == review.funny && cool == review.cool && Objects.equals(reviewId, review.reviewId) && Objects.equals(userId, review.userId) && Objects.equals(businessId, review.businessId) && Objects.equals(date, review.date) && Objects.equals(text, review.text);
    }

    @Override
    public int hashCode() {
        return Objects.hash(reviewId, userId, businessId, stars, useful, funny, cool, date, text);
    }

}

