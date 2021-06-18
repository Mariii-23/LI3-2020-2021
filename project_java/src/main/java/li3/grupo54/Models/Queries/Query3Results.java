package li3.grupo54.Models.Queries;

import org.apache.commons.lang3.tuple.Triple;

import java.util.HashMap;
import java.util.Map;

public class Query3Results {
    Map<Integer, Triple<Integer,Integer,Float>> result;
    // mes to triplo(numero review, negocios distintos, media atribuida)

    public Query3Results(Map<Integer,Triple<Integer,Integer,Float>> result){
        this.result = result;
    }

    public Map<Integer, Triple<Integer,Integer,Float>> getResults() {
        return new HashMap<>(result);
    }

}
