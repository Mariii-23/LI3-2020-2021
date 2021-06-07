package li3.grupo54.main.java.li3.grupo54.Models;

import com.opencsv.CSVReader;
import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Paths;

public interface ICatalog<T> {
    public T callConstructor(String [] line) throws InvalidUserLineException, BusinessNotFoundException, InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineExpcetion, InvalidReviewLineException;
    public int size();
    public void add(T t);
    public T getById(String id) throws UserNotFoundException, BusinessNotFoundException, ReviewNotFoundException;
    public void delete(String id) throws BusinessNotFoundException;
    public default void populateFromFile(String filename) throws IOException, URISyntaxException {
        BufferedReader reader = Files.newBufferedReader(Paths.get(ClassLoader.getSystemResource(filename).toURI()));
        char delim = Leitura.determineDelimiter(reader.readLine());
        CSVReader csvReader = new CSVReader(reader,delim);

        String [] nextLine ;
        while(((nextLine = csvReader.readNext()) != null)) {
            try {
                this.add(callConstructor(nextLine));
            }
            catch(InvalidUserLineException | BusinessNotFoundException | InvalidBusinessLineException e) {
                // alterarar estatisticas de linhsa invalidaas
            }
        }
        reader.close();
        csvReader.close();
    }

}
