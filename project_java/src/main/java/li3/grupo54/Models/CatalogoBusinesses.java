package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.Models.Exceptions.InvalidBusinessLineException;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Interfaces.ICatalog;

import java.io.Serializable;
import java.util.Objects;
import java.util.TreeMap;

/**
 * Esta classe contém todas as informações de um conjuto de business.
 */
public class CatalogoBusinesses implements ICatalog<IBusiness>, Serializable {
  /**
   * Todos os negócios são colocados aqui numa fase inicial e depois, passados para um outro map no caso que se encontre
   * uma review com o seu id.
   */
  private final TreeMap<String, IBusiness> businessesById; // ordenados por ordem alfabetica
  /**
   * Number of invalid businesses seen so far
   */
  private int invalidBusinesses;

  private String inputFileName = "businesses.csv";

  /**
   * @return The last input file named used
   */
  @Override
  public String getInputFileName() {
    return inputFileName;
  }

  @Override
  public void setInputFileName(String inputFileName) {
    this.inputFileName = inputFileName;
  }

  public CatalogoBusinesses() {
    this.businessesById = new TreeMap<>();
    this.invalidBusinesses = 0;
  }

  public IBusiness getBusiness(String businessId) {
    return businessesById.get(businessId);
  }

  /**
   * Deolve o numero de negocios considerados invalidos durante a leitura
   * @return
   */
  @Override
  public int getInvalidCount() {
    return invalidBusinesses;
  }

  /**
   * Incrementa o número de negócios inválidos
   * @return
   */
  public void addInvalid() {
    this.invalidBusinesses++;
  }

  /**
   * Devolve os negocios invalidos
   * @return int
   */
  public int getInvalidBusinesses() {
    return invalidBusinesses;
  }

  /**
   * Devolve o nome de um business a partir do seu business id.
   * @param businessId Business ID
   * @return Nome do business
   * @throws BusinessNotFoundException Devolve excepcao no caso de não existir esse business.
   */
  public String getName(String businessId) throws BusinessNotFoundException {
    IBusiness business = null;
    if ((business = businessesById.get(businessId)) == null)
      throw new BusinessNotFoundException("Business Not Found Id: " + businessId);
    return business.getName();
  }

  /**
   * Verifica se um determinado business encontra-se no catálogo a partir do seu id.
   * @param businessId Business Id
   * @return Retorna true no caso de existir, e no contrário retornará falso
   */
  public boolean containsBusinessById(String businessId) {
    return this.businessesById.containsKey(businessId);
  }

  /**
   * Devolve um determinado business obtido através do parsing de uma determinada string
   * @param line Linha a ser analisada
   * @return Business
   * @throws InvalidBusinessLineException
   */
  @Override
  public Business callConstructor(String[] line) throws InvalidBusinessLineException {
    return new Business(line);
  }

  /**
   *  Delvolve o número total de business contidas.
   * @return Inteiro
   */
  @Override
  public int size() {
    return businessesById.size();
  }

  /**
   * Adiciona um determinado business ao catálogo.
   * @param iBusiness Business a ser adicionado.
   */
  @Override
  public void add(IBusiness iBusiness) {
    this.businessesById.put(iBusiness.getId(), iBusiness.clone());
  }

  /**
   * Devolve um determinado business a partir do seu business id
   * @param id Business id
   * @return Business
   * @throws BusinessNotFoundException Lança uma exceção no caso desse business não existir
   */
  @Override
  public IBusiness getById(String id) throws BusinessNotFoundException {
    var biz = this.businessesById.get(id);
    if (biz != null) {
      return biz;
    } else {
      throw new BusinessNotFoundException(id);
    }
  }

  /**
   *  Apaga um business do catalogo dado o seu id
   * @param id businessId
   * @throws BusinessNotFoundException
   */
  @Override
  public void delete(String id) throws BusinessNotFoundException {
    if (this.businessesById.get(id) == null) throw new BusinessNotFoundException();
    else {
      this.businessesById.remove(id);
    }
  }

  @Override
  public String toString() {
    return "CatalogoBusinesses{" +
        "businesses=" + businessesById +
        ", invalidBusinesses=" + invalidBusinesses +
        '}';
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    CatalogoBusinesses that = (CatalogoBusinesses) o;
    return getInvalidBusinesses() == that.getInvalidBusinesses() && Objects.equals(businessesById, that.businessesById);
  }

  @Override
  public int hashCode() {
    return Objects.hash(businessesById, getInvalidBusinesses());
  }

}
