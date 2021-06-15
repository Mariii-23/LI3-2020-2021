package li3.grupo54.main.java.li3.grupo54.Models;

import com.opencsv.CSVReader;
import com.opencsv.exceptions.CsvValidationException;
import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Paths;

public interface ICatalog<T> {
  T callConstructor(String[] line) throws  BusinessNotFoundException, InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineException;

  int size();

  void add(T t);

  T getById(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

  void delete(String id) throws BusinessNotFoundException;

  void addInvalid();

  public default void populateFromFile(String filename) throws IOException, URISyntaxException, CsvValidationException {
    BufferedReader reader = Files.newBufferedReader(Paths.get(ClassLoader.getSystemResource(filename).toURI()));
    char delim = Leitura.determineDelimiter(reader.readLine());
    CSVReader csvReader = new CSVReader(reader, delim);

    String[] nextLine;
    while (((nextLine = csvReader.readNext()) != null)) {
      try {
        this.add(callConstructor(nextLine));
      } catch (InvalidUserLineException | BusinessNotFoundException | InvalidBusinessLineException | InvalidReviewLineException e) {
        // alterarar estatisticas de linhsa invalidaas
        this.addInvalid();
      }
    }
    reader.close();
    csvReader.close();
  }
}
