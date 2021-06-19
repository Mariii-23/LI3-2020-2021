package li3.grupo54.Models.Queries;


import li3.grupo54.Utils.MyTriple;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Query3Results implements IQueryResults{
    List<MyTriple<Integer,Integer,Float>> result;
    // mes to triplo(numero review, negocios distintos, media atribuida)

    public Query3Results(List<MyTriple<Integer,Integer,Float>> result){
        this.result = result;
    }

    public List<MyTriple<Integer,Integer,Float>> getResults() {
      return result;
    }

    public List<String> getNumberReviews(){
        List<String> list = new ArrayList<>();
        for(MyTriple<Integer,Integer,Float> triplo: result){
            if(triplo != null) {
                list.add(Integer.toString(triplo.getLeft()));
            }
        }
        return list;
    }

    public List<String> getNumberBusiness(){
        List<String> list = new ArrayList<>();
        for(MyTriple<Integer,Integer,Float> triplo: result){
            if(triplo != null) {
                list.add(Integer.toString(triplo.getMiddle()));
            }
        }
        return list;
    }

    public List<String> getMean(){
        List<String> list = new ArrayList<>();
        for(MyTriple<Integer,Integer,Float> triplo: result){
            if(triplo != null) {
                list.add(Float.toString(triplo.getRight()));
            }
        }
        return list;
    }
}
