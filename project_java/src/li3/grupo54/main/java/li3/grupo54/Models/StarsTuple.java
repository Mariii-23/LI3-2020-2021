package li3.grupo54.main.java.li3.grupo54.Models;

import java.util.Comparator;

public class StarsTuple implements Comparator<StarsTuple> {
  private double currentAverage;
  private int numberTotal;

  public StarsTuple() {
    currentAverage = 0;
    numberTotal = 0;
  }

  public StarsTuple(double currentAverage, int numberTotal) {
    this.currentAverage = currentAverage;
    this.numberTotal = numberTotal;
  }

  public void update(double value) {
    currentAverage = (currentAverage * numberTotal + value) / (++numberTotal);
  }

  public double getCurrentAverage() {
    return currentAverage;
  }

  public int getNumberTotal() {
    return numberTotal;
  }

  @Override
  public int compare(StarsTuple starsTuple, StarsTuple t1) {
    return (int) (starsTuple.getCurrentAverage() - t1.getCurrentAverage());
  }
}
