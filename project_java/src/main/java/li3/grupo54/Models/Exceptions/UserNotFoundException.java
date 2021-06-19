package li3.grupo54.Models.Exceptions;

/**
 * Thrown when the user associated with a given id could not be found
 */

public class UserNotFoundException extends Exception {
    public UserNotFoundException() {
        super();
    }

    public UserNotFoundException(String s) {
        super("Utilizador com id '" + s + "' nao existe");
    }
}

