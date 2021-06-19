package li3.grupo54.Models.Exceptions;

/**
 * Thrown when no review exists in the provided date
 */

public class DateNotFoundException extends Exception {
    public DateNotFoundException() {
    }

    public DateNotFoundException(String message) {
        super(message);
    }
}
