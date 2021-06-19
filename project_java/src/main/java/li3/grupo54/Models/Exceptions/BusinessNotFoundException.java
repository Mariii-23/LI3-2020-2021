package li3.grupo54.Models.Exceptions;

/**
 * Thrown when a Business with a certain id could not be found
 */
public class BusinessNotFoundException extends Exception {
    public BusinessNotFoundException() {
        super();
    }

    public BusinessNotFoundException(String s) {
        super("Negocio com id '" + s + "' nao existe");
    }
}

