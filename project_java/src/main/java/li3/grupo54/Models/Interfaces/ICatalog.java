package li3.grupo54.Models.Interfaces;

import li3.grupo54.Models.CatalogoBusinesses;
import li3.grupo54.Models.CatalogoUsers;
import li3.grupo54.Models.Exceptions.*;
import li3.grupo54.Models.Leitura;
import li3.grupo54.Models.Stats;

import java.io.*;
import java.nio.charset.StandardCharsets;

/**
 *  Interface which all three catalogs need to implement. It is essentially a small database which provides methods for storing and acessing values.
 */

public interface ICatalog<T> extends Serializable {
  String getInputFileName();
  void setInputFileName(String inputFileName);
  T callConstructor(String[] line) throws BusinessNotFoundException, InvalidUserLineException,
      InvalidBusinessLineException, InvalidReviewLineException,
      InvalidUserLineException, InvalidBusinessLineException,
      InvalidReviewLineException;

  int size();

  int getInvalidCount();

  void add(T t);

  T getById(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

  void delete(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

  void addInvalid();

  public default void populateFromFile(Stats stats, String filename, CatalogoUsers catalogoUsers, CatalogoBusinesses catalogoBusinesses) throws IOException {
    setInputFileName(filename);
    File file = new File(filename);
    InputStream is = new FileInputStream(file);
    BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
    char delim = Leitura.determineDelimiter(reader.readLine());

    String nextLine;
    String[] parsedLine;
    while ((nextLine = reader.readLine()) != null) {
      try {
        parsedLine = nextLine.split(String.valueOf(delim));
        // constructor vai validar e lancar excecao se der erro
        T newEntity = callConstructor(parsedLine);

        if (newEntity instanceof IReview) {
          if (catalogoBusinesses.containsBusinessById(((IReview) newEntity).getBusinessId()) &&
              catalogoUsers.containsUserById(((IReview) newEntity).getUserId())) {
            this.add(newEntity);
            stats.atualiza(newEntity, catalogoUsers, catalogoBusinesses);
          }
        } else {
          this.add(newEntity);
          stats.atualiza(newEntity, catalogoUsers, catalogoBusinesses);
        }

      } catch (InvalidUserLineException | BusinessNotFoundException | InvalidBusinessLineException | InvalidReviewLineException e) {
        // alterarar estatisticas de linhsa invalidaas
        this.addInvalid();
      }
    }
    reader.close();
    is.close();
  }
}
