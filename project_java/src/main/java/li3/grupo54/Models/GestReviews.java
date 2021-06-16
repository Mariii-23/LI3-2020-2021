package li3.grupo54.Models;

import com.opencsv.exceptions.CsvValidationException;

import java.io.IOException;
import java.net.URISyntaxException;

public class GestReviews {
  private CatalogoUsers catalogoUsers;
  private CatalogoBusinesses catalogoBusinesses;
  private CatalogoReviews catalogoReviews;
  private Stats stats;

  public GestReviews() {}

  public GestReviews(FileTriple triple) throws CsvValidationException, IOException, URISyntaxException {
    this(triple.getUsersFile(), triple.getBusinessesFile(), triple.getReviewsFile());
  }

  public GestReviews(String users, String businesses, String reviews) throws CsvValidationException, IOException, URISyntaxException {
    this();
    this.load(users, businesses, reviews);
  }

  public void load(String users, String businesses, String reviews) throws IOException, URISyntaxException, CsvValidationException{
    this.catalogoUsers = new CatalogoUsers();
    this.catalogoBusinesses = new CatalogoBusinesses();
    this.catalogoReviews = new CatalogoReviews();
    catalogoUsers.populateFromFile(users);
    catalogoBusinesses.populateFromFile(businesses);
    catalogoReviews.populateFromFile(reviews);

    this.stats = new Stats();
  }

  public CatalogoUsers getCatalogoUsers() {
    return catalogoUsers;
  }

  public void setCatalogoUsers(CatalogoUsers catalogoUsers) {
    this.catalogoUsers = catalogoUsers;
  }

  public CatalogoBusinesses getCatalogoBusinesses() {
    return catalogoBusinesses;
  }

  public void setCatalogoBusinesses(CatalogoBusinesses catalogoBusinesses) {
    this.catalogoBusinesses = catalogoBusinesses;
  }

  public CatalogoReviews getCatalogoReviews() {
    return catalogoReviews;
  }

  public void setCatalogoReviews(CatalogoReviews catalogoReviews) {
    this.catalogoReviews = catalogoReviews;
  }

  public Stats getStats() {
    return stats;
  }

  public void setStats(Stats stats) {
    this.stats = stats;
  }
}

