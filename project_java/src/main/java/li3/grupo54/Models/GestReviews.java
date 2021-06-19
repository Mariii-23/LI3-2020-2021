package li3.grupo54.Models;


import li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.Utils.MyTriple;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.URISyntaxException;
import java.util.*;
import java.util.function.ToIntFunction;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class GestReviews implements Serializable {
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
      Crono.start();
      catalogoUsers.populateFromFile(stats, users, null,null);
      double timeTotal=0;
      double time =Crono.stop();
      timeTotal+=time;
      System.out.println("\nFinished reading users");
      System.out.println("Time: "+time+"\n");

      Crono.start();
      catalogoBusinesses.populateFromFile(stats, businesses ,null,null);
      time =Crono.stop();
      timeTotal+=time;
      System.out.println("Finished reading businesses");
      System.out.println("Time: "+time+"\n");

      // atualiza negocios nao avaliados e tal
      Crono.start();
      catalogoReviews.populateFromFile(stats,reviews,catalogoUsers,catalogoBusinesses);
      time =Crono.stop();
      timeTotal+=time;
      System.out.println("Finished reading businesses");
      System.out.println("Time: "+time+"\n");
      System.out.println("\nTotal Time: "+timeTotal+"\n");
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

 public int getNumberReviewsInYearBusiness(String businessId, int ano) {
    return Math.toIntExact(this.stats.getAllReviews(businessId).stream().map(r -> catalogoReviews.getReviewById(r)).filter(r -> r.getDate().getYear() == ano).count());
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

    public Map<Integer,List<MyPair<IBusiness, Integer>>> query6(int n) {
      Map<Integer, Map<String, List<Review>>> b = this.catalogoReviews.getAnoToReviewsPerMonth().entrySet().stream()
              .collect(
                      Collectors.toMap(
                              Map.Entry::getKey,
                              e -> e.getValue().stream().filter(Objects::nonNull).flatMap(Collection::stream).collect(Collectors.groupingBy(Review::getBusinessId))
              ));
      Map<Integer, List<MyPair<IBusiness, Integer>>> c = new HashMap<>();
      for(final var yy: b.entrySet()) {
        for(final var business: yy.getValue().entrySet()) {
          final var list = c.computeIfAbsent(yy.getKey(), (k) -> new ArrayList<>());
          try {
            list.add(new MyPair<>(this.catalogoBusinesses.getById(business.getKey()), business.getValue().size()));
          } catch (BusinessNotFoundException ignored) { }
          list.sort(Comparator.comparingInt((ToIntFunction<MyPair<IBusiness, Integer>>) MyPair::getY).reversed());
          if(list.size() > n) {
            list.remove(list.size() - 1);
          }
        }
      }
      c.forEach((key, list) -> {
        for(int i = 0; i < list.size(); ++i) {
          final var oldPair = list.get(i);
          final var distinctUsers = (int) b.get(key).get(oldPair.getX().getId()).stream().map(Review::getUserId).distinct().count();
          list.set(i, new MyPair<>(oldPair.getX(), distinctUsers));
        }
      });
      return c;
  }

  public Stream<Review> getReviewsOfBusiness(String businessId) {
    return this.catalogoReviews.getByReviewId()
            .values()
            .stream()
            .filter(r -> r.getBusinessId().equals(businessId));
  }

  public List<MyPair<String,Integer>>  query8(Integer x) {
    return stats.query8(x);
  }
  public void onSave(String filename) throws IOException{
        FileOutputStream fos = new FileOutputStream(filename);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this);
        oos.close();
  }
}

