package li3.grupo54.Models;

import com.carrotsearch.junitbenchmarks.AbstractBenchmark;
import li3.grupo54.Models.Interfaces.IStats;
import org.junit.Before;
import org.junit.Test;

import java.time.LocalDateTime;
import java.util.HashSet;

public class StatsTest extends AbstractBenchmark {
    public final IStats stats = new Stats();
    private CatalogoUsers catalogoUsers;
    private CatalogoBusinesses catalogoBusinesses;

    @Before
    public void setUp() {
        this.catalogoUsers = new CatalogoUsers();
        for (int i = 0; i < 10000; ++i) {
            catalogoUsers.add(new User(i + "", "John Doe"));
        }
        this.catalogoBusinesses = new CatalogoBusinesses();
        for (int i = 0; i < 10000; ++i) {
            catalogoBusinesses.add(new Business(i + "", "name", "city", "state", new HashSet<>()));
        }
    }

    @Test
    public void updateOne() throws Exception {
        final Review r = new Review("id", "userid", "businessId", 4.2f, 0, 3, 4, LocalDateTime.now(), "text");
        this.stats.atualiza(r, this.catalogoUsers, this.catalogoBusinesses);
    }

    @Test
    public void updateDueToReview() throws Exception {

        Review r;
        for (int i = 0; i < 10000; ++i) {
            r = new Review(i + "", "userid", "businessId", 4.2f, 0, 3, 4, LocalDateTime.now(), "text");
            this.stats.atualiza(r, this.catalogoUsers, this.catalogoBusinesses);
        }
    }

    @Test
    public void updateDueToBusiness() throws Exception {
        Business r;
        for (int i = 0; i < 10000; ++i) {
            r = new Business(i + "", "name", "city", "state", new HashSet<String>());
            this.stats.atualiza(r, null, null);
        }
    }

    @Test
    public void updateDueToUser() throws Exception {
        User r;
        for (int i = 0; i < 10000; ++i) {
            r = new User(i + "", "John Doe");
            this.stats.atualiza(r, null, null);
        }
    }
}
