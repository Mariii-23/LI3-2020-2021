package main.java.li3.grupo54.Models;

import li3.grupo54.Models.Business;
import main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

public class CatalogoBusinesses implements ICatalog<Business> {
    @Override
    public Business callConstructor(String[] line) throws InvalidUserLineException, InvalidBusinessLineException, InvalidReviewLineExpcetion {
        return null;
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public void add(Business business) {

    }

    @Override
    public Business getById(String id) {
        return null;
    }

    @Override
    public void delete(String id) {

    }
}
