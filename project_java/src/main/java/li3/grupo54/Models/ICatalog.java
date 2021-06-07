package main.java.li3.grupo54.Models;

import com.opencsv.CSVReader;
import main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Paths;

public interface ICatalog<T> {
    public T callConstructor(String [] line) throws InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineExpcetion;
    public int size();
    public void add(T t);
    public T getById(String id);
    public void delete(String id);
    public default void populateFromFile(String filename)  {
         try {
            BufferedReader reader = Files.newBufferedReader(Paths.get(ClassLoader.getSystemResource(filename).toURI()));
            char delim = Leitura.determineDelimiter(reader.readLine());
            CSVReader csvReader = new CSVReader(reader,delim);
            String [] nextLine ;
            while(((nextLine = csvReader.readNext()) != null)) {
                try {
                    this.add(callConstructor(nextLine));
                }
                catch(InvalidUserLineException | InvalidBusinessLineException | InvalidReviewLineExpcetion e) {
                    // alterarar estatisticas de linhsa invalidaas
                }
            }
            reader.close();
            csvReader.close();
        }
        // probably passar este try catch para outro sitio
        catch (IOException | URISyntaxException e) {
            System.out.println("Error reading file");
        }
    }
}
