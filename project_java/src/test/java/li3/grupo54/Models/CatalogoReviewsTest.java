package li3.grupo54.Models;

import com.carrotsearch.junitbenchmarks.AbstractBenchmark;
import li3.grupo54.Models.Interfaces.ICatalog;
import org.junit.Test;
import org.junit.Assert;

import java.time.LocalDateTime;

public class CatalogoReviewsTest extends AbstractBenchmark {
    private final ICatalog<Review> catalog = new CatalogoReviews();

    @Test
    public void testOne() throws Exception {
        final Review r = new Review("id", "userid", "businessId", 4.2f, 0, 0, 0, LocalDateTime.now(), "text");
        catalog.add(r);
        Assert.assertEquals(r, catalog.getById("id"));
    }

    @Test
    public void add_1_000_000_reviews() {
        for (int i = 0; i < 1000000; ++i) {
            catalog.add(
                    new Review(i + "", "userid", "businessId", 4.2f, 0, 0, 0, LocalDateTime.now(), "text")
            );
        }
    }
}
