package li3.grupo54.main.java.li3.grupo54.Models;

public class StarsTuple {
  private double currentAverrage;
  private int numberTotal;

  public StarsTuple() {
    currentAverrage = 0;
    numberTotal = 0;
  }

  public StarsTuple(double currentAverrage, int numberTotal) {
    this.currentAverrage = currentAverrage;
    this.numberTotal = numberTotal;
  }

  public void update(double value){
    currentAverrage = (currentAverrage* numberTotal +value)/(++numberTotal);
  }

  public double getCurrentAverrage() {
    return currentAverrage;
  }

  public int getNumberTotal() {
    return numberTotal;
  }
}
