package li3.grupo54.Models.Queries;


import li3.grupo54.Utils.MyTriple;

import java.util.List;

public class Query3Results implements IQueryResults {
    List<MyTriple<Integer, Integer, Double>> result;
    // mes to triplo(numero review, negocios distintos, media atribuida)

    public Query3Results(List<MyTriple<Integer, Integer, Double>> result) {
        this.result = result;
    }

    public List<MyTriple<Integer, Integer, Double>> getResults() {
        return result;
    }
}
