package li3.grupo54.Models.Interfaces;

import com.opencsv.*;
import com.opencsv.exceptions.*;
import li3.grupo54.Models.Business;
import li3.grupo54.Models.CatalogoReviews;
import li3.grupo54.Models.Exceptions.*;
import li3.grupo54.Models.Leitura;
import li3.grupo54.Models.Review;

import java.io.*;
import java.net.URISyntaxException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Locale;

import static com.opencsv.CSVReader.DEFAULT_VERIFY_READER;

public interface ICatalog<T> {
  T callConstructor(String[] line) throws  BusinessNotFoundException, InvalidUserLineException,
          InvalidBusinessLineException, InvalidReviewLineException,
          InvalidUserLineException, InvalidBusinessLineException,
          InvalidReviewLineException;

  int size();

  void add(T t);

  T getById(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

  void delete(String id) throws BusinessNotFoundException;

  void addInvalid();

  public default void populateFromFile(String filename) throws IOException {
    File file = new File(filename);
    InputStream is = new FileInputStream(file);
    BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
    char delim = Leitura.determineDelimiter(reader.readLine());

    String nextLine;
    String [] parsedLine ;
    while ((nextLine = reader.readLine()) != null)  {
      try {
        parsedLine  = nextLine.split(String.valueOf(delim));
        this.add(callConstructor(parsedLine));

      } catch (InvalidUserLineException | BusinessNotFoundException | InvalidBusinessLineException | InvalidReviewLineException  e) {
        // alterarar estatisticas de linhsa invalidaas
        this.addInvalid();
      }
    }
    reader.close();
    is.close();
  }
}
