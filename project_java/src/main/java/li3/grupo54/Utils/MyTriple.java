package li3.grupo54.Utils;

import java.io.Serializable;

/**
 *
 * @param <T> First generic parameter
 * @param <T1> Middle generic parameter
 * @param <T2> Third generic parameter
 * Auxiliary data structure for combining three different results, mostly for queries which require more than one information.
 */
public class MyTriple<T, T1, T2> implements Serializable {

  private T left;
  private T1 middle;
  private T2 right;

  public MyTriple(T left, T1 middle, T2 right) {
    this.left = left;
    this.middle = middle;
    this.right = right;
  }

  public MyTriple(MyTriple<T, T1, T2> that) {
    this.left = that.getLeft();
    this.middle = that.getMiddle();
    this.right = that.right;
  }

  public T getLeft() {
    return left;
  }

  public void setLeft(T left) {
    this.left = left;
  }

  public T1 getMiddle() {
    return middle;
  }

  public void setMiddle(T1 middle) {
    this.middle = middle;
  }

  public T2 getRight() {
    return right;
  }

  public void setRight(T2 right) {
    this.right = right;
  }

  @Override
  public String toString() {
    return "MyTriple{" +
        "left=" + left +
        ", middle=" + middle +
        ", right=" + right +
        '}';
  }
}
