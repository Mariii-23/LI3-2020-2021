package li3.grupo54.Models.Exceptions;

/**
 * Thrown when the review associated with a given id could not be found
 */
public class ReviewNotFoundException extends Exception {
    public ReviewNotFoundException() {
        super();
    }

    public ReviewNotFoundException(String s) {
        super("Avaliacao com id '" + s + "' nao existe");
    }
}

