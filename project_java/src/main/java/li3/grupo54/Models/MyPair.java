package li3.grupo54.Models;

public class MyPair<T,R> {
  private T x;
  private R y;

  public MyPair(T x, R y) {
    this.x = x;
    this.y = y;
  }

  public MyPair(MyPair<T,R> that){
    this.x = that.getX();
    this.y = that.getY();
  }

  public T getX() {
    return x;
  }

  public void setX(T x) {
    this.x = x;
  }

  public R getY() {
    return y;
  }

  public void setY(R y) {
    this.y = y;
  }
}
