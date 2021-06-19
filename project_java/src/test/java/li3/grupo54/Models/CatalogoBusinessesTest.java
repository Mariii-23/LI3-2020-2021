package li3.grupo54.Models;

import com.carrotsearch.junitbenchmarks.AbstractBenchmark;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Interfaces.ICatalog;
import org.junit.Test;

import java.util.HashSet;

public class CatalogoBusinessesTest extends AbstractBenchmark {
  private final ICatalog<IBusiness> catalog = new CatalogoBusinesses();

  @Test
  public void add_10_000_000_businesses() throws Exception {
    for (int i = 0; i < 10000000; ++i) {
      catalog.add(new Business(i + "", "name", "city", "state", new HashSet<>()));
    }
  }
}
