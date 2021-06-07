package main.java.li3.grupo54.Models;

import main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

import java.util.HashMap;
import java.util.Map;

public class CatalogoUsers implements ICatalog<User> {
    private Map<String, User> byUserId;

    @Override
    public User callConstructor(String [] line) throws InvalidUserLineException {
        return new User(line);

    }
    public CatalogoUsers() {
        this.byUserId = new HashMap<String, User>();
    }
    public CatalogoUsers(String [] line ) {
    }
    public int size() {
        return this.byUserId.size();
    }
    public User getById(String id) {
        return byUserId.get(id).clone();
    }
    public void add(User user) {
        this.byUserId.put(user.getUserId(),user.clone());
    }
    public void delete(String id) {
        byUserId.remove(id);
    }
}