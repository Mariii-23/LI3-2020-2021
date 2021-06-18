package li3.grupo54.Models.Queries;
import li3.grupo54.Models.Pair;
public class Query2Results implements IQueryResults {
    Pair<Integer,Integer> result;

    public Query2Results(Pair<Integer,Integer> result){
        this.result = result;
    }

    public Pair<Integer,Integer> getResults() {
        return new Pair<>(result);
    }
}
