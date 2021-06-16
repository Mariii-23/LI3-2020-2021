package li3.grupo54.Models;

import com.opencsv.exceptions.CsvValidationException;

import java.io.IOException;
import java.net.URISyntaxException;

public class GestReviews {
  CatalogoUsers catalogoUsers;
  CatalogoBusinesses catalogoBusinesses;
  CatalogoReviews catalogoReviews;
  Stats stats;

  GestReviews() {
    this.catalogoUsers = new CatalogoUsers();
    this.catalogoBusinesses = new CatalogoBusinesses();
    this.catalogoReviews = new CatalogoReviews();
    try {
      catalogoUsers.populateFromFile("users.csv");
      catalogoBusinesses.populateFromFile("businesses.csv");
      catalogoReviews.populateFromFile("reviews.csv");
    } catch (IOException | URISyntaxException | CsvValidationException e) {
      System.out.println("Error reading file");
    }
    this.stats = new Stats();

  }
}

