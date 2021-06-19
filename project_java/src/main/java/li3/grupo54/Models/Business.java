package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.InvalidBusinessLineException;
import li3.grupo54.Models.Interfaces.IBusiness;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * BUSINESS
 */
public class Business implements IBusiness {
  /**
   * Business id
   */
  private final String businessId;
  /**
   * Nome do business
   */
  private final String name;
  /**
   * Cidade a que esse business pertence.
   */
  private final String city;
  /**
   * Estado a que esse business pertence.
   */
  private final String state;
  /**
   * Categorias a que esse business pode ser enquadrado.
   */
  private Set<String> categories;

  /**
   * Construtor de um business
   * @param businessId Business Id
   * @param name Nome do business
   * @param city Cidade a que pertence
   * @param state Estado a que pertence
   * @param categories Categorias aonde se enquadra
   */
  public Business(String businessId, String name, String city, String state, Set<String> categories) {
    this.businessId = businessId;
    this.name = name;
    this.city = city;
    this.state = state;
    this.categories = new HashSet<>();
    this.categories.addAll(categories);
  }

  /**
   * Controí um business a partir de uma dada string.
   * @param linhaSplit String a ser analisada
   * @throws InvalidBusinessLineException A String recebida pode ser inválida
   */
  public Business(String[] linhaSplit) throws InvalidBusinessLineException {
    if (linhaSplit.length != 5) {
      throw new InvalidBusinessLineException();
    } else {
      this.businessId = linhaSplit[0];
      this.name = linhaSplit[1];
      this.city = linhaSplit[2];
      this.state = linhaSplit[3];
      this.categories = Arrays.stream(linhaSplit[4].split(",")).collect(Collectors.toSet());
    }
  }

  /**
   * Contruí um business a partir de um outro dado.
   * @param that Business a ser copiado.
   */
  public Business(Business that) {
    this.businessId = that.businessId;
    this.name = that.name;
    this.city = that.city;
    this.state = that.state;
    this.categories = new HashSet<>(that.categories);
  }

  @Override
  /**
   * Devolve o seu Id.
   * @return ID
   */
  public String getId() {
    return businessId;
  }

  /**
   * Devolve o seu nome.
   * @return Nome
   */
  public String getName() {
    return name;
  }

  /**
   * Devolve a cidada à qual pertence.
   * @return Cidade
   */
  public String getCity() {
    return city;
  }

  /**
   * Devolve o estado à qual pertence.
   * @return Estado
   */
  public String getState() {
    return state;
  }

  /**
   * Devolve um set de strings à qual este se enquadra.
   * @return Categorias a que pertence.
   */
  public Set<String> getCategories() {
    return new HashSet<>(this.categories);
  }

  /**
   * Recebe um business e retorna um clone do mesmo.
   * @return Business
   */
  public Business clone() {
    return new Business(this);
  }

  /**
   * Verifica se o objeto em questão é igual a um dado.
   * @param o Objeto a ser analisado.
   * @return Returna true se forem iguais, falso caso contrário.
   */
  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Business business = (Business) o;
    return getId().equals(business.getId()) && getName().equals(business.getName()) && getCity().equals(business.getCity()) && getState().equals(business.getState()) && getCategories().equals(business.getCategories());
  }

  @Override
  public int hashCode() {
    return Objects.hash(getId(), getName(), getCity(), getState(), getCategories());
  }

  public String toString() {
    return "Business{" +
        "businessId='" + businessId + '\'' +
        ", name='" + name + '\'' +
        ", city='" + city + '\'' +
        ", state='" + state + '\'' +
        ", categories=" + categories +
        '}';
  }
}
