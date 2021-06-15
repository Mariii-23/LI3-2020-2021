package li3.grupo54.main.java.li3.grupo54.Models;

import li3.grupo54.main.java.li3.grupo54.Models.Exceptions.InvalidBusinessLineException;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

public class Business {

  private final String businessId;
  private final String name;
  private final String city;
  private final String state;
  private Set<String> categories;

  public Business(String businessId, String name, String city, String state, Set<String> categories) {
    this.businessId = businessId;
    this.name = name;
    this.city = city;
    this.state = state;
    this.categories = new HashSet<>();
    this.categories.addAll(categories);
  }

  public Business(String businessId, String name, String city, String state) {
    this.businessId = businessId;
    this.name = name;
    this.city = city;
    this.state = state;
  }

  public Business(String[] linhaSplit) throws InvalidBusinessLineException {
    if (linhaSplit.length != 5) {
      throw new InvalidBusinessLineException();
    } else {
      this.businessId = linhaSplit[0];
      this.name = linhaSplit[1];
      this.city = linhaSplit[2];
      this.state = linhaSplit[3];
      this.categories = Arrays.stream(linhaSplit[4].split(",")).collect(Collectors.toSet());
    }
  }

  public Business(Business that) {
    this.businessId = that.businessId;
    this.name = that.name;
    this.city = that.city;
    this.state = that.state;
    this.categories = new HashSet<>(that.categories);
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
    return new HashSet<>(this.categories);
  }

  public void setCategories(Set<String> categories) {
    this.categories = new HashSet<>(categories);
  }

  public Business clone() {
    return new Business(this);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Business business = (Business) o;
    return Objects.equals(getBusinessId(), business.getBusinessId()) && Objects.equals(getName(), business.getName()) && Objects.equals(getCity(), business.getCity()) && Objects.equals(getState(), business.getState()) && Objects.equals(getCategories(), business.getCategories());
  }

  @Override
  public int hashCode() {
    return Objects.hash(getBusinessId(), getName(), getCity(), getState(), getCategories());
  }

  public String toString() {
    return "Business{" +
        "businessId='" + businessId + '\'' +
        ", name='" + name + '\'' +
        ", city='" + city + '\'' +
        ", state='" + state + '\'' +
        ", categories=" + categories +
        '}';
  }
}
