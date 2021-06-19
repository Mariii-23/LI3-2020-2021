package li3.grupo54.Utils;

public class MyFive<T1,T2,T3,T4,T5> extends  MyFour<T1,T2,T3,T4>{
  private final T5 five;

  public MyFive(T1 first, T2 left, T3 middle, T4 right, T5 five) {
    super(first, left, middle, right);
    this.five = five;
  }

  public T5 getFive() {
    return five;
  }
}
