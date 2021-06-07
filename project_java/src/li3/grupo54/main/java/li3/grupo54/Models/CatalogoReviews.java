package li3.grupo54.main.java.li3.grupo54.Models;

import javafx.util.Pair;
import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.InvalidBusinessLineException;
import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.InvalidReviewLineException;
import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class CatalogoReviews implements ICatalog<Review> {
    Map<Integer, List<Set<Review>>> anoToReviewsPerMonth;
        // ano =>  array de 12 elementos => cada array tem um set de reviews

    public CatalogoReviews()  {
        this.anoToReviewsPerMonth = new HashMap<>();
    }

    @Override
    public Review callConstructor(String[] line) throws InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineException {
        return new Review(line);
    }

    @Override
    public int size() {
        // TODO
        return 0;
    }

    @Override
    public void add(Review review) {

        // TODO
    }

    @Override
    public Review getById(String id) {
        // TODO
        return null;
    }

    @Override
    public void delete(String id) {
        // TODO

    }
    public int getTotalNumberReviews() {
        // TODO
        return 0;

    }
    private int getNumberDistinctUsers() {
        // TODO
        return 0;
    }

    // numero total de reviews e quantos users distintos as realizaram
    // para a query 2
    public Pair<Integer, Integer> getNumberReviewsAndDistinctUsers() {
        return new Pair<>(getTotalNumberReviews(),getNumberDistinctUsers());
    }

}
