package li3.grupo54.Models.Queries;

import li3.grupo54.Utils.MyPair;

import java.util.ArrayList;
import java.util.List;

public class Query5Results implements IQueryResults {
  List<MyPair<String, Integer>> result;

  public Query5Results(List<MyPair<String, Integer>> result) {
    this.result = result;
  }

  public List<MyPair<String, Integer>> getResults() {
    return result;
  }

public List<String> allNameReviews(){
  List<String> list = new ArrayList<>();
  for(MyPair<String,Integer> pair: result){
    list.add(pair.getX());
  }
  return list;
}

  public List<String> getAllNumber(){
    List<String> list = new ArrayList<>();
       for(MyPair<String,Integer> pair: result){
      list.add(Integer.toString(pair.getY()));
    }
    return list;
  }
}
