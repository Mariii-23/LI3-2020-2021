package li3.grupo54.Models.Interfaces;

import li3.grupo54.Models.CatalogoBusinesses;
import li3.grupo54.Models.CatalogoUsers;
import li3.grupo54.Models.Exceptions.*;
import li3.grupo54.Models.Leitura;
import li3.grupo54.Models.Stats;

import java.io.*;
import java.nio.charset.StandardCharsets;

/**
 * Interface which all three catalogs need to implement. It is essentially a small database which provides methods for storing and acessing values.
 */

public interface ICatalog<T> extends Serializable {
    /**
     * Returns the filename of the file which was used to populate the catalog
     *
     * @return File Name
     */
    String getInputFileName();

    /**
     * Sets the filename of the file which was used to populate the catalog
     *
     * @param inputFileName
     */
    void setInputFileName(String inputFileName);

    /**
     * Calls the appropriate constructor , depending on the class of the catalog's members, which takes a parsed line read froma file.
     *
     * @param line
     * @return
     * @throws InvalidUserLineException
     * @throws InvalidBusinessLineException
     * @throws InvalidReviewLineException
     */
    T callConstructor(String[] line) throws InvalidUserLineException,
            InvalidBusinessLineException, InvalidReviewLineException;

    /**
     * @return Number of elements in catalog
     */
    int size();

    /**
     * Returns number of invalid elements
     *
     * @return
     */
    int getInvalidCount();

    /**
     * Adds entity to catalog
     *
     * @param t
     */
    void add(T t);

    /*+
    Return element of the catalog given its id
     */
    T getById(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

    /*+
    Delete element of the catalog given its id
     */
    void delete(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;

    /**
     * Incremente number of invalid members
     */
    void addInvalid();

    /**
     * Default method to populate the catalog by reading a file and instantiating new members
     *
     * @param stats
     * @param filename
     * @param catalogoUsers
     * @param catalogoBusinesses
     * @throws IOException
     */
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

            } catch (InvalidUserLineException | InvalidBusinessLineException | InvalidReviewLineException e) {
                // alterarar estatisticas de linhsa invalidaas
                this.addInvalid();
            }
        }
        reader.close();
        is.close();
    }
}
