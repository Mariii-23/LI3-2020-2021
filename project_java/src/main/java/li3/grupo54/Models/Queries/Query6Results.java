package li3.grupo54.Models.Queries;

import li3.grupo54.Models.Business;
import li3.grupo54.Models.Interfaces.IBusiness;
import li3.grupo54.Utils.MyPair;
import li3.grupo54.Utils.MyTriple;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Query6Results implements IQueryResults {

    private Map<Integer, List<MyPair<IBusiness, Integer>>> businesses;

    // ver clone
    public Query6Results(Map<Integer, List<MyPair<IBusiness, Integer>>> businesses) {
        this.businesses = businesses;
    }

    public List<MyTriple<Integer, String, Integer>> getBusinesses() {
        return businesses.entrySet()
                .stream()
                .flatMap(x ->
                    x.getValue().stream().map(b -> new MyTriple<>(x.getKey(), b.getX().getId(), b.getY()))
                )
                .collect(Collectors.toList());
    }

    public void setBusinesses(Map<Integer, List<MyPair<IBusiness, Integer>>> businesses) {
        this.businesses = businesses;
    }
}
