package li3.grupo54.main.java.li3.grupo54.Models;

import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.InvalidUserLineException;

import java.util.HashMap;
import java.util.Map;

public class CatalogoUsers implements ICatalog<User> {
    private Map<String, User> byUserId;

    public CatalogoUsers() {
        this.byUserId = new HashMap<String, User>();
    }
    @Override
    public User callConstructor(String [] line) throws InvalidUserLineException {
        return new User(line);

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