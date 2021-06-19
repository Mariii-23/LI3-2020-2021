package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.time.LocalDateTime;


/**
 * Interface whose methods need be implemented by any class which wants to have the behaviour of a review.
 */

public interface IReview extends Serializable {
    /**
     * Get ReviewId
     *
     * @return Review Id
     */
    public String getReviewId();

    /**
     * Returns the userId of the user which made this review
     *
     * @return User ID
     */
    public String getUserId();

    /**
     * Returns the businesses id of the business which was rated in this review
     *
     * @return Business ID
     */
    public String getBusinessId();

    /**
     * Get Number of stars of the review
     *
     * @return Starts
     */
    public float getStars();

    /**
     * Get useful field of review
     *
     * @return Useful
     */
    public int getUseful();

    /**
     * Get funny field of review
     *
     * @return Funny
     */
    public int getFunny();

    /**
     * Get cool field of review
     *
     * @return Cool
     */
    public int getCool();

    /**
     * Get date of the review
     *
     * @return Date
     */
    public LocalDateTime getDate();

    /**
     * Returns field text of review
     *
     * @return Text
     */
    public String getText();

    public IReview clone();
}
