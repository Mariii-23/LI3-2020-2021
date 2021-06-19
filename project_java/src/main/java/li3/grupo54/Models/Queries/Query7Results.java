package li3.grupo54.Models.Queries;


import li3.grupo54.Utils.MyTriple;

import java.util.List;

public class Query7Results implements IQueryResults {
    List<MyTriple<String, String, Integer>> result;
    // mes to triplo(numero review, negocios distintos, media atribuida)

    public Query7Results(List<MyTriple<String, String, Integer>> result) {
        this.result = result;
    }

    public List<MyTriple<String, String, Integer>> getResults() {
        return result;
    }
}
