package li3.grupo54.Models.Exceptions;

public class ReviewNotFoundException extends Exception {
  public ReviewNotFoundException() {
    super();
  }

  public ReviewNotFoundException(String s) {
    super("Avaliacao com id '" + s + "' nao existe");
  }
}

