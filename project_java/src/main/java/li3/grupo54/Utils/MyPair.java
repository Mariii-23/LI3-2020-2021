package li3.grupo54.Utils;

import java.util.Objects;

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

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    MyPair<?, ?> myPair = (MyPair<?, ?>) o;
    return Objects.equals(getX(), myPair.getX()) && Objects.equals(getY(), myPair.getY());
  }

  @Override
  public int hashCode() {
    return Objects.hash(getX(), getY());
  }
}
