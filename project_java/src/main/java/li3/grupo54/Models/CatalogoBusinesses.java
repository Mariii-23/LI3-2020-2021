package li3.grupo54.Models;

import li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.Models.Exceptions.InvalidBusinessLineException;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Models.Interfaces.ICatalog;

import java.util.*;
import java.util.stream.Collectors;

public class CatalogoBusinesses implements ICatalog<IBusiness> {
  // todos os negocios  vao ser colocados aqui numa fase inicial e depois passados para o outro map  caso se encontre uma review
  private final TreeMap<String, IBusiness> negociosNuncaAvaliados; // ordenados por ordem alfabetica
  private final Map<String, IBusiness> negociosAvaliados;

  private int invalidBusiness;

  public CatalogoBusinesses() {
    //Comparable<String,Business> byId = (e1,e2)-> e1.getBusinessId() - e2.getBusinessId();
    //Comparable<Business> byId = (e1,e2)-> e1.getBusinessId().compareTo(e2.getBusinessId()) ;
    this.negociosNuncaAvaliados = new TreeMap<>(); // ordenar alfabeticamente
    this.negociosAvaliados = new HashMap<>();
    this.invalidBusiness = 0;
  }

  //private int byId(String e1,String e2){
  //    return e1.compareTo(e2);
  //};

  public void addInvalid(){
    this.invalidBusiness++;
  }

  public int getInvalidBusiness() {
    return invalidBusiness;
  }

  @Override
  public Business callConstructor(String[] line) throws InvalidBusinessLineException {
    return new Business(line);
  }

  @Override
  public int size() {
    return negociosAvaliados.size() + negociosNuncaAvaliados.size();
  }

  @Override
  public void add(IBusiness business) {
    this.negociosNuncaAvaliados.put(business.getId(), business.clone());
  }

  public void changesBusinessAvalied(String id) throws BusinessNotFoundException {
    IBusiness business = negociosNuncaAvaliados.remove(id);
    if (business == null)
      throw new BusinessNotFoundException("Business Not Found, id: " + id);
    this.negociosAvaliados.put(id, business.clone());
  }

  @Override
  public IBusiness getById(String id) throws BusinessNotFoundException {
    IBusiness b;
    if ((b = negociosAvaliados.get(id)) != null || (b = negociosNuncaAvaliados.get(id)) != null) {
      return b.clone();
    } else {
      throw new BusinessNotFoundException();
    }
  }

  @Override
  public void delete(String id) throws BusinessNotFoundException {
    if (negociosAvaliados.get(id) != null) {
      negociosAvaliados.remove(id);
    } else if (negociosNuncaAvaliados.get(id) != null) {
      negociosNuncaAvaliados.remove(id);
    } else {
      throw new BusinessNotFoundException();
    }
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    CatalogoBusinesses that = (CatalogoBusinesses) o;
    return Objects.equals(negociosNuncaAvaliados, that.negociosNuncaAvaliados) && Objects.equals(negociosAvaliados, that.negociosAvaliados);
  }

  @Override
  public int hashCode() {
    return Objects.hash(negociosNuncaAvaliados, negociosAvaliados);
  }

  @Override
  public String toString() {
    return "CatalogoBusinesses{" +
        "negociosNuncaAvaliados=" + negociosNuncaAvaliados +
        ", negociosAvaliados=" + negociosAvaliados +
        '}';
  }

  // para a query 1
  public List<IBusiness> getNegociosNuncaAvaliadosOrdered() {
    // acho que devolve ordenado mas preciso de confirmar
    return this.negociosNuncaAvaliados.values().stream().map(IBusiness::clone).collect(Collectors.toList());
  }

}
