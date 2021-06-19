package li3.grupo54.Models;

//import org.junit.Test;

import li3.grupo54.Models.User;
import li3.grupo54.Models.Interfaces.ICatalog;

public class CatalogoUsersTest {
    private final ICatalog<User> catalog = new CatalogoUsers();

 //   @Test
    public void testOne() {
        catalog.add(new User("userid", "nome"));
    }
}
