package li3.grupo54.main.java.li3.grupo54.Models;

import java.util.*;

public class Stats {
  // User id ->  mes a mes -> UserStarsTuple
  Map<String,List<UserStarsTuple>> averageByUserId;
  // Business id ->  mes a mes -> BusinessStarsTuple
  Map<String,List<BusinessStarsTuple>> averageByBusinessId;
  // State -> City -> BusinessId -> Average
  Map<String,Map<String,Map<String,StarsTuple>>> averageByStateBusiness;

  public Stats(){
    averageByUserId = new HashMap<>();
    averageByBusinessId = new HashMap<>();
    averageByStateBusiness = new HashMap<>();
  }

  public void updateStats(Review review,Business business){
    updateAverageBusiness(review);
    updateAverageUSer(review);
    updateAveragebySate(review,business);
  }

  // TODO rever
  public void updateAveragebySate(Review review,Business business){
    if(review==null) return;
    if(!review.getBusinessId().equals(business.getBusinessId()))
      return;
    var state = business.getState();
    var city = business.getCity();
    Map<String,Map<String,StarsTuple>> map;
    if((map=this.averageByStateBusiness.get(state))==null){
      map = new HashMap<>();
      Map<String,StarsTuple> mapCity = new HashMap<>();
      mapCity.put(business.getBusinessId(), new BusinessStarsTuple(review));
      map.put(city,mapCity);
      this.averageByStateBusiness.put(state,map);
    }
    else {
      Map<String,StarsTuple> mapCity = map.get(city);
      if(mapCity==null){
        mapCity = new HashMap<>();
        mapCity.put(business.getBusinessId(), new BusinessStarsTuple(review));
        map.put(city,mapCity);
      }else {
        var starTuple = mapCity.get(business.getBusinessId());
        if(starTuple==null)
          mapCity.put(business.getBusinessId(), new BusinessStarsTuple(review));
        else
          starTuple.update(review.getStars());
      }
    }
  }

  public void updateAverageUSer(Review review){
    String userId = review.getUserId();
    Integer month = review.getDate().getMonthValue()-1;
    List<UserStarsTuple> list = null;

    if ((list = this.averageByUserId.get(userId)) ==null){
      list = new ArrayList<>(12);
      list.add(month,new UserStarsTuple(review));
      this.averageByUserId.put(userId,list);

    } else {
      UserStarsTuple userStarsTuple = list.get(month);
      if(userStarsTuple == null)
        userStarsTuple = new UserStarsTuple();
      userStarsTuple.updateAverage(review);
    }
  }

  public void updateAverageBusiness(Review review){
    String businessId = review.getBusinessId();
    Integer month = review.getDate().getMonthValue()-1;
    List<BusinessStarsTuple> list = null;

    if ((list = this.averageByBusinessId.get(businessId)) ==null){
      list = new ArrayList<>(12);
      list.add(month,new BusinessStarsTuple(review));
      this.averageByBusinessId.put(businessId,list);

    } else {
      BusinessStarsTuple userStarsTuple = list.get(month);
      if(userStarsTuple == null)
        userStarsTuple = new BusinessStarsTuple();
      userStarsTuple.updateAverage(review);
    }
  }
}
