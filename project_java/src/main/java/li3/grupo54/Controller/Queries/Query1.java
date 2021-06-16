package li3.grupo54.Controller.Queries;

import li3.grupo54.Models.GestReviews;
import li3.grupo54.Models.Interfaces.IBusiness;

import java.util.List;
import java.util.stream.Collectors;

public class Query1 {
    private List<IBusiness> businesses;

    public Query1(GestReviews model) {
        businesses = model.getCatalogoBusinesses().getNegociosNuncaAvaliadosOrdered();
    }

    public List<IBusiness> getBusinesses() {
        return businesses.stream().map(IBusiness::clone).collect(Collectors.toList());
    }

    public int getNumBusinesses() {
        return businesses.size();
    }
}
