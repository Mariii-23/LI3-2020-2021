package li3.grupo54.Models;

import com.carrotsearch.junitbenchmarks.AbstractBenchmark;
import li3.grupo54.Models.Interfaces.ICatalog;
import org.junit.Assert;
import org.junit.Test;

public class CatalogoUsersTest extends AbstractBenchmark {
  public final ICatalog<User> catalog = new CatalogoUsers();

  @Test
  public void testOne() throws Exception {
    final var u = new User("userid", "nome");
    catalog.add(u);
    Assert.assertEquals(u, catalog.getById("userid"));
  }

  @Test
  public void insert_10_000_000_Users() {
    for (int i = 0; i < 10000000; ++i) {
      catalog.add(new User(i + "", "name"));
    }
  }
}
