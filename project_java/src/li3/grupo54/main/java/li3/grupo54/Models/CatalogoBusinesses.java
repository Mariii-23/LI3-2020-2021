package li3.grupo54.main.java.li3.grupo54.Models;

import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.BusinessNotFoundException;
import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.InvalidBusinessLineException;

import java.util.*;
import java.util.stream.Collectors;

public class CatalogoBusinesses implements ICatalog<Business> {
    // todos os negocios  vao ser colocados aqui numa fase inicial e depois passados para o outro map  caso se encontre uma review
    TreeMap<String, Business> negociosNuncaAvaliados; // ordenados por ordem alfabetica
    Map<String, Business> negociosAvaliados;

    @Override
    public Business callConstructor(String[] line) throws InvalidBusinessLineException {
        return new Business(line);
    }
    public CatalogoBusinesses() {
        this.negociosNuncaAvaliados = new TreeMap<>(); // ordenar alfabeticamente
        this.negociosAvaliados = new HashMap<>();
    }

    @Override
    public int size() {
        return negociosAvaliados.size() + negociosNuncaAvaliados.size();
    }
    @Override
    public void add(Business business) {
        this.negociosNuncaAvaliados.put(business.getBusinessId(),business.clone());
    }

    @Override
    public Business getById(String id) throws BusinessNotFoundException {
        Business b;
        if( (b = negociosAvaliados.get(id)) != null || (b = negociosNuncaAvaliados.get(id)) != null ) {
            return b.clone();
        }
        else {
            throw new BusinessNotFoundException();
        }
    }

    @Override
    public void delete(String id) throws BusinessNotFoundException {
        Business b;
        if (negociosAvaliados.get(id) != null) {
            negociosAvaliados.remove(id);
        }
        else if(negociosNuncaAvaliados.get(id) != null) {
            negociosNuncaAvaliados.remove(id);
        }
        else {
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
    public List<Business> getNegociosNuncaAvaliadosOrdered() {
        // acho que devolve ordenado mas preciso de confirmar
        return this.negociosNuncaAvaliados.values().stream().map(Business::clone).collect(Collectors.toList());
    }

}
