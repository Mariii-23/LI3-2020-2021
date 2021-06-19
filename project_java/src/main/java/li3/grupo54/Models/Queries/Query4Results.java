package li3.grupo54.Models.Queries;


import li3.grupo54.Utils.MyTriple;

import java.util.List;

public class Query4Results implements IQueryResults{
  List<MyTriple<Integer,Integer,Float>> result;
  // mes to triplo(numero review, negocios distintos, media atribuida)

  public Query4Results(List<MyTriple<Integer,Integer,Float>> result){
    this.result = result;
  }

  public List<MyTriple<Integer,Integer,Float>> getResults() {
    return result;
  }
}
