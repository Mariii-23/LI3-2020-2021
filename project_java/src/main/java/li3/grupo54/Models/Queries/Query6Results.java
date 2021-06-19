package li3.grupo54.Models.Queries;

import li3.grupo54.Models.Business;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Utils.MyPair;

import java.util.List;
import java.util.Map;

public class Query6Results implements IQueryResults {

    private Map<Integer, List<MyPair<IBusiness,Integer>>> businesses;
    // ver clone
public Query6Results(Map<Integer, List< MyPair<IBusiness,Integer>>> businesses) {
    this.businesses = businesses;
    }

    public Map<Integer, List< MyPair<IBusiness,Integer>>> getBusinesses() {
        return businesses;
    }

    public void setBusinesses(Map<Integer, List< MyPair<IBusiness,Integer>>>businesses) {
        this.businesses = businesses;

    }
}
