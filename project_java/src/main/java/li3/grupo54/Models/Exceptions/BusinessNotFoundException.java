package li3.grupo54.Models.Exceptions;

public class BusinessNotFoundException extends Exception {
  public BusinessNotFoundException() {
    super();
  }

  public BusinessNotFoundException(String s) {
    super("Negocio com id '" + s + "' nao existe");
  }
}

