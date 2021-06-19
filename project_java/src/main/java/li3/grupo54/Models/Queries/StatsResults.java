package li3.grupo54.Models.Queries;

import li3.grupo54.Models.CatalogoBusinesses;
import li3.grupo54.Models.CatalogoReviews;
import li3.grupo54.Models.CatalogoUsers;
import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Interfaces.ICatalog;
import li3.grupo54.Utils.MyFive;

import java.time.Month;
import java.util.List;


public class StatsResults implements IQueryResults {

    private final Statistics results;

    public StatsResults(GestReviews results) {
        this.results = new Statistics(results);
    }

    public Statistics getResults() {
        return this.results;
    }

    public static final class Statistics {
        public final BusinessCatalog businessCatalog;
        public final UsersCatalog usersCatalog;
        public final ReviewCatalog reviewCatalog;
        public final List<MyFive<Month, Integer, Float, Integer, Integer>> averageReviews;

        private Statistics(GestReviews self) {
            this.businessCatalog = new BusinessCatalog(self.getCatalogoBusinesses(), self.getBusinessWithReviews());
            this.reviewCatalog = new ReviewCatalog(self.getCatalogoReviews());
            this.usersCatalog = new UsersCatalog(self.getCatalogoUsers(), self.getStats().getUsersNaoAvaliados());
            this.averageReviews = self.getStats().getAverageByMonthReviewAndMore();
        }

        public static abstract class CatalogStats {
            public final int read;
            public final int invalid;
            public final String inputFile;
            public final int totalRead;

            public <T> CatalogStats(ICatalog<T> catalog) {
                this.inputFile = catalog.getInputFileName();
                this.read = catalog.size();
                this.invalid = catalog.getInvalidCount();
                this.totalRead = this.read + this.invalid;
            }
        }

        public static class BusinessCatalog extends CatalogStats {
            public final int reviewed;

            public BusinessCatalog(CatalogoBusinesses catalog, int reviewed) {
                super(catalog);
                this.reviewed = reviewed;
            }
        }

        public static class ReviewCatalog extends CatalogStats {
            public final int zeroImpact;

            public ReviewCatalog(CatalogoReviews catalog) {
                super(catalog);
                this.zeroImpact = catalog.getZeroImpact();
            }
        }

        public static class UsersCatalog extends CatalogStats {
            public final int inactive;

            public UsersCatalog(CatalogoUsers catalog, int inactive) {
                super(catalog);
                this.inactive = inactive;
            }
        }
    }
}
