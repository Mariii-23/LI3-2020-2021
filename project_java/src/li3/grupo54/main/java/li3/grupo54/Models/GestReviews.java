package li3.grupo54.main.java.li3.grupo54.Models;

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
    } catch (IOException | URISyntaxException e) {
      System.out.println("Error reading file");
    }
    this.stats = new Stats();

  }
}

