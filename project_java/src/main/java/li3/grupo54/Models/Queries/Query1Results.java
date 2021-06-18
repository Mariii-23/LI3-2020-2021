package li3.grupo54.Models.Queries;

import li3.grupo54.Models.Interfaces.IBusiness;

import java.util.List;

public class Query1Results implements IQueryResults {
    private List<IBusiness> businesses;

    // ver clone
    public Query1Results(List<IBusiness> businesses) {
        this.businesses = businesses;
    }

    public List<IBusiness> getBusinesses() {
        return businesses;
    }

    public void setBusinesses(List<IBusiness> businesses) {
        this.businesses = businesses;
    }
}
