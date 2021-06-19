package li3.grupo54.Models.Exceptions;

/**
 * Thrown when the line read from reviews.csv does not have the right amount of fields to create a review
 */
public class InvalidReviewLineException extends Exception {
    public InvalidReviewLineException() {
        super();
    }

    public InvalidReviewLineException(String m) {
        super(m);
    }
}
