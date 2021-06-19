package li3.grupo54.Models;


import li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.Utils.MyTriple;

import java.io.IOException;
import java.net.URISyntaxException;
import java.util.*;
import java.util.stream.Collectors;

public class GestReviews {
  private CatalogoUsers catalogoUsers;
  private CatalogoBusinesses catalogoBusinesses;
  private CatalogoReviews catalogoReviews;
  private Stats stats;

  public GestReviews() {}

  public GestReviews(FileTriple triple) throws  IOException, URISyntaxException {
    this(triple.getUsersFile(), triple.getBusinessesFile(), triple.getReviewsFile());
  }

  public GestReviews(String users, String businesses, String reviews) throws  IOException, URISyntaxException {
    this();
    this.load(users, businesses, reviews);
  }

  public void load(String users, String businesses, String reviews) throws IOException, URISyntaxException {
    this.stats = new Stats();
    try {
      this.catalogoUsers = new CatalogoUsers();
      this.catalogoBusinesses = new CatalogoBusinesses();
      this.catalogoReviews = new CatalogoReviews();
      catalogoUsers.populateFromFile(stats, users, null,null);
      System.out.println("Finished reading users\n");
      catalogoBusinesses.populateFromFile(stats, businesses ,null,null);
      System.out.println("Finished reading businesses\n");
      // atualiza negocios nao avaliados e tal
      catalogoReviews.populateFromFile(stats,reviews,catalogoUsers,catalogoBusinesses);
      System.out.println("Finished reading reviews\n");
    }
   catch (Exception e){

    }

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

  // nomes de negocios por ordem decrescente de numero de avaliacoes que o user fez e quantos no total
  // para quantidades iguais, ordem alfabetica de negocios
  public List<MyPair<String,Integer>> query5(String userId){
    Comparator<MyPair<String,Integer>> c = (par1,par2) ->  {
      if(par1.getY().equals(par2.getY())) {
        return par1.getX().compareTo(par2.getX());
      }
      else {
        return par1.getY().compareTo(par2.getY());
      }
    };
    return stats.pairBusinessIdAndTheirReviews(userId).stream().map(par -> {
      try {
        par.setX(this.catalogoBusinesses.getName(par.getX()));
      } catch (BusinessNotFoundException e) {
        e.printStackTrace();
      }
      return new MyPair<String, Integer>(par);
    }).sorted(c).collect(Collectors.toList());
  }

  public List<MyTriple<Integer,Integer,Float>> query3(String userId){
    return  this.stats.query3(userId);
  }

  public List<MyTriple<Integer,Integer,Float>> query4(String businessId){
    return this.stats.query4(businessId);
  }

  public List<MyTriple<String,String,Integer>> query7(){
    return stats.query7();
  }
}

