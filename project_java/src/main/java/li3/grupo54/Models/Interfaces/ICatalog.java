package li3.grupo54.Models.Interfaces;

import li3.grupo54.Models.*;
import li3.grupo54.Models.Exceptions.*;

import java.io.*;
import java.nio.charset.StandardCharsets;

public interface ICatalog<T> {
  T callConstructor(String[] line) throws  BusinessNotFoundException, InvalidUserLineException,
          InvalidBusinessLineException, InvalidReviewLineException,
          InvalidUserLineException, InvalidBusinessLineException,
          InvalidReviewLineException;

  int size();

  void add(T t);

  T getById(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

  void delete(String id) throws UserNotFoundException, BusinessNotFoundException,ReviewNotFoundException ;

  void addInvalid();

  public default void populateFromFile(Stats stats, String filename) throws IOException {
    File file = new File(filename);
    InputStream is = new FileInputStream(file);
    BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
    char delim = Leitura.determineDelimiter(reader.readLine());

    String nextLine;
    String [] parsedLine ;
    while ((nextLine = reader.readLine()) != null)  {
      try {
        parsedLine  = nextLine.split(String.valueOf(delim));
        // constructor vai validar e lancar excecao se der erro
        T newEntity = callConstructor(parsedLine);
        this.add(newEntity);
        stats.atualiza(newEntity);


      } catch (InvalidUserLineException | BusinessNotFoundException | InvalidBusinessLineException | InvalidReviewLineException  e) {
        // alterarar estatisticas de linhsa invalidaas
        this.addInvalid();
      }
    }
    reader.close();
    is.close();
  }
}