package li3.grupo54.Models.Exceptions;

/**
 * Thrown when the line read from businsses.csv does not have the right amount of fields to create a business
 */
public class InvalidBusinessLineException extends Exception {
    public InvalidBusinessLineException() {
        super();
    }

    InvalidBusinessLineException(String m) {
        super(m);
    }
}
