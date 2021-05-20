package li3.grupo54.Models;

import java.util.HashSet;
import java.util.Set;

public class Business {

  private String businessId;
  private String name;
  private String city;
  private String state;
  private Set<String> categories;

  public Business(String businessId, String name, String city, String state, Set<String> categories) {
    this.businessId = businessId;
    this.name = name;
    this.city = city;
    this.state = state;
    this.categories = new HashSet<>();
    categories.forEach( s-> this.categories.add(s));
  }

  public Business(String businessId, String name, String city, String state) {
    this.businessId = businessId;
    this.name = name;
    this.city = city;
    this.state = state;
  }

  public Business(Business that){
    this.businessId = businessId;
    this.name = name;
    this.city = city;
    this.state = state;
    this.categories = new HashSet<>();
  }

  public String getBusinessId() {
    return businessId;
  }

  public String getName() {
    return name;
  }

  public String getCity() {
    return city;
  }

  public String getState() {
    return state;
  }

  public Set<String> getCategories() {
    Set<String> result = new HashSet<>();
    this.categories.forEach( s-> result.add(s));
    return categories;
  }

//   public void setCategories(Set<String> categories) {
//     this.categories = new HashSet<>();
//     categories.forEach( s-> this.categories.add(s));
//   }

  public Business clone(Business that){
    return  new Business(that);
  }

  // fazer to string e equals
}