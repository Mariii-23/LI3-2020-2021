package main.java.li3.grupo54.Models;

import main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

public class CatalogoReviews implements ICatalog<Review> {
    @Override
    public Review callConstructor(String[] line) throws InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineExpcetion {
        return new Review(line);
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public void add(Review review) {

    }

    @Override
    public Review getById(String id) {
        return null;
    }

    @Override
    public void delete(String id) {

    }
}
