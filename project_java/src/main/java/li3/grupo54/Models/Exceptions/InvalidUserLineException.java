package li3.grupo54.Models.Exceptions;

/**
 * Thrown when the line read from users.csv does not have the right amount of fields to create a users
 */

public class InvalidUserLineException extends Exception {
    public InvalidUserLineException() {
        super();
    }

    public InvalidUserLineException(String m) {
        super(m);
    }

}
