package li3.grupo54.main.java.li3.grupo54.Models;

import java.util.*;

public class Stats {
  //User id ->  mes a mes -> UserStarsTuple
  Map<String,List<UserStarsTuple>> averageByUserId;
  //Business id ->  mes a mes -> BusinessStarsTuple
  Map<String,List<BusinessStarsTuple>> averageByBusinessId;

  public Stats(){
    averageByUserId = new HashMap<>();
    averageByBusinessId = new HashMap<>();
  }

  public void updateStats(Review review){
    updateAverageBusiness(review);
    updateAverageUSer(review);
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
