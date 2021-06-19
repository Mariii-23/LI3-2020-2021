package li3.grupo54.Models;


import li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.Models.Exceptions.UserNotFoundException;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Utils.Crono;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.Utils.MyTriple;

import java.io.*;
import java.net.URISyntaxException;
import java.util.*;
import java.util.function.ToIntFunction;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class GestReviews implements Serializable {
  /**
   * catálogo de todos os users lidos.
   */
  private CatalogoUsers catalogoUsers;
  /**
   * catálogo de todos os users lidos.
   */
  private CatalogoBusinesses catalogoBusinesses;
  /**
   * catálogo de todos os users lidos.
   */
  private CatalogoReviews catalogoReviews;
  /**
   * Estatísticas dos dados analisados.
   */
  private Stats stats;

  public GestReviews() {
    this.stats = new Stats();
    this.catalogoUsers = new CatalogoUsers();
    this.catalogoBusinesses = new CatalogoBusinesses();
    this.catalogoReviews = new CatalogoReviews();
  }

  public GestReviews(String users, String businesses, String reviews) throws IOException, URISyntaxException {
    this();
    this.load(users, businesses, reviews);
  }

  public GestReviews(FileTriple triple) throws IOException, URISyntaxException {
    this(triple.getUsersFile(), triple.getBusinessesFile(), triple.getReviewsFile());
  }

  /**
   * Carregamento de 3 ficheiros dados para a classe pretendida
   * @param users Ficheiro do users
   * @param businesses Ficheiros dos business
   * @param reviews FIcheiros das reviews
   * @throws IOException
   * @throws URISyntaxException
   */
  public void load(String users, String businesses, String reviews) throws IOException, URISyntaxException {
    Crono.start();
    catalogoUsers.populateFromFile(stats, users, null, null);
    double timeTotal = 0;
    double time = Crono.stop();
    timeTotal += time;
    System.out.println("\nFinished reading users");
    System.out.println("Time: " + time + "\n");

    Crono.start();
    catalogoBusinesses.populateFromFile(stats, businesses, null, null);
    time = Crono.stop();
    timeTotal += time;
    System.out.println("Finished reading businesses");
    System.out.println("Time: " + time + "\n");

    // atualiza negocios nao avaliados e tal
    Crono.start();
    catalogoReviews.populateFromFile(stats, reviews, catalogoUsers, catalogoBusinesses);
    time = Crono.stop();
    timeTotal += time;
    System.out.println("Finished reading businesses");
    System.out.println("Time: " + time + "\n");
    System.out.println("\nTotal Time: " + timeTotal + "\n");

  }

  public CatalogoUsers getCatalogoUsers() {
    return catalogoUsers;
  }

  public CatalogoBusinesses getCatalogoBusinesses() {
    return catalogoBusinesses;
  }

  public CatalogoReviews getCatalogoReviews() {
    return catalogoReviews;
  }

  public Stats getStats() {
    return stats;
  }

  public String getReviewsInputFileName() { return catalogoReviews.getInputFileName(); }

  public String getBusinessesInputFileName() { return catalogoBusinesses.getInputFileName(); }

  public String getUsersInputFileName() { return catalogoUsers.getInputFileName(); }

  public int getBusinessWithReviews(){
    return this.stats.getBusinessWithReviews();
  }

  /**
   * Query 5
   * Devolve uma lista de nomes de negocios por orden decrescente de numero de avaliações que o user fez e quantos
   * no total para quantidades iguais, por ordem alfabética de nomes dos negócios.
   * @param userId User Id
   * @return Lista
   */
  public List<MyPair<String, Integer>> query5(String userId) throws UserNotFoundException, BusinessNotFoundException {
    Comparator<MyPair<String, Integer>> c = (par1, par2) -> {
      if (par1.getY().equals(par2.getY())) {
        return par1.getX().compareTo(par2.getX());
      } else {
        return par1.getY().compareTo(par2.getY());
      }
    };
    List<MyPair<String, Integer>> r = new ArrayList<>();
    for(final var par : stats.pairBusinessIdAndTheirReviews(userId)) {
        par.setX(this.catalogoBusinesses.getName(par.getX()));
        r.add(par);
    }
    r.sort(c);
    return r;
  }

  public int getNumberReviewsInYearBusiness(String businessId, int ano) {
    return Math.toIntExact(this.stats.getAllReviews(businessId).stream().map(catalogoReviews::getReviewById).filter(r -> r.getDate().getYear() == ano).count());
  }

  /**
   * Query 3
   * @param userId user id
   * @return Devolve a informação relacionada com a query 3
   */
  public List<MyTriple<Integer, Integer, Double>> query3(String userId) throws UserNotFoundException {
    return this.stats.query3(userId);
  }

  /**
   * Query 4
   * @param businessId Business Id
   * @return Devolve a informação relacionada com a query 4
   */

  public List<MyTriple<Integer, Integer, Double>> query4(String businessId) throws BusinessNotFoundException {
    return this.stats.query4(businessId);
  }

  /**
   * Query 7
   * @return Devolve a informação relacionada com a query 7
   */
  public List<MyTriple<String, String, Integer>> query7() {
    return stats.query7();
  }

  /**
   * Query 6
   * Devolve um Map de anos para lista de pares. Sendo que esses pares vão conter os X negócios mais avaliados, contendo
   * o Business em questao e o número total de utilizadores distintos que o avaliaram.
   * @param n
   * @return
   */
  public Map<Integer, List<MyPair<IBusiness, Integer>>> query6(int n) {
    Map<Integer, Map<String, List<Review>>> b = this.catalogoReviews.getAnoToReviewsPerMonth().entrySet().stream()
        .collect(
            Collectors.toMap(
                Map.Entry::getKey,
                e -> e.getValue().stream().filter(Objects::nonNull).flatMap(Collection::stream).collect(Collectors.groupingBy(Review::getBusinessId))
            ));
    Map<Integer, List<MyPair<IBusiness, Integer>>> c = new HashMap<>();
    for (final var yy : b.entrySet()) {
      for (final var business : yy.getValue().entrySet()) {
        final var list = c.computeIfAbsent(yy.getKey(), (k) -> new ArrayList<>());
        try {
          list.add(new MyPair<>(this.catalogoBusinesses.getById(business.getKey()), business.getValue().size()));
        } catch (BusinessNotFoundException ignored) {
        }
        list.sort(Comparator.comparingInt((ToIntFunction<MyPair<IBusiness, Integer>>) MyPair::getY).reversed());
        if (list.size() > n) {
          list.remove(list.size() - 1);
        }
      }
    }
    c.forEach((key, list) -> {
      for (int i = 0; i < list.size(); ++i) {
        final var oldPair = list.get(i);
        final var distinctUsers = (int) b.get(key).get(oldPair.getX().getId()).stream().map(Review::getUserId).distinct().count();
        list.set(i, new MyPair<>(oldPair.getX(), distinctUsers));
      }
    });
    return c;
  }

  public Stream<Review> getReviewsOfBusiness(String businessId) throws BusinessNotFoundException {
    this.catalogoBusinesses.getById(businessId); // assert that business exists
    return this.catalogoReviews.getByReviewId()
        .values()
        .stream()
        .filter(r -> r.getBusinessId().equals(businessId));
  }

  /**
   * Query 8
   * @param x Número
   * @return Devolve informaçao relacionada com a query8
   */
  public List<MyPair<String, Integer>> query8(Integer x) {
    return stats.query8(x);
  }

  // save to object file
  public void onSave(String filename) throws IOException {
    BufferedOutputStream fos = null;
    ObjectOutputStream oos = null;
    try {
       fos = new BufferedOutputStream(new FileOutputStream(filename));
       oos = new ObjectOutputStream(fos);
       oos.writeObject(this);
    } finally {
       if (fos != null) fos.flush();
       if (oos != null) oos.close();
    }
  }

  // read from object file
  public void onRestore(String filename) throws IOException, ClassNotFoundException {
    FileInputStream fos = null;
    ObjectInputStream oos = null;
    try{
      fos = new FileInputStream(filename);
      oos = new ObjectInputStream(fos);
      GestReviews r = (GestReviews) oos.readObject();
      this.catalogoBusinesses = r.catalogoBusinesses;
      this.catalogoUsers = r.catalogoUsers;
      this.catalogoReviews = r.catalogoReviews;
      this.stats = r.stats;
    } finally {
      if (oos != null) oos.close();
    }
  }
}

