package li3.grupo54.Models.Exceptions;

/**
 * Thrown when the Review is null
 */

public class NullReviewException extends Exception {
    public NullReviewException() {
    }

    public NullReviewException(String message) {
        super(message);
    }
}
