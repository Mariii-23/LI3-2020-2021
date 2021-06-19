package li3.grupo54.Models.Queries;

import li3.grupo54.Models.StarsTuple;

import java.util.Map;
import java.util.stream.Stream;

public class Query10Results implements IQueryResults {

  private Map<String, Map<String, Map<String, StarsTuple>>> averageByStateBusiness;

  public Query10Results(Map<String, Map<String, Map<String, StarsTuple>>> averageByStateBusiness) {
    this.averageByStateBusiness = averageByStateBusiness;
  }

  public Stream<Result> getResults() {
    // this is kinda messy mas I think it works
    return averageByStateBusiness.entrySet().stream()
        .flatMap(stateRest ->
            stateRest.getValue().entrySet().stream().flatMap(cityRest ->
                cityRest.getValue().entrySet().stream().map(bidRest -> new Result(
                    stateRest.getKey(),
                    cityRest.getKey(),
                    bidRest.getKey(),
                    bidRest.getValue().getCurrentAverage())
                )
            )
        );
  }

  public static final class Result {
    private final String state;
    private final String city;
    private final String businessId;
    private final double averageRating;

    private Result(String state, String city, String businessId, double averageRating) {
      this.state = state;
      this.city = city;
      this.businessId = businessId;
      this.averageRating = averageRating;
    }

    public String getState() {
      return this.state;
    }

    public String getCity() {
      return this.city;
    }

    public String getBusinessId() {
      return businessId;
    }

    public double getAverageRating() {
      return averageRating;
    }
  }

}
