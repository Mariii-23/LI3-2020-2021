package li3.grupo54.Utils;

import java.io.Serializable;

/**
 *  Auxiliary data structure for combining four different results, mostly for queries which require more than one information.
 * @param <T> First Value
 * @param <R> Second Value
 * @param <S> Third Value
 * @param <H> Fourth Value
 */

public class MyFour<T, R, S, H> extends MyTriple<R, S, H> implements Serializable {
  private T first;

  public MyFour(T first, R left, S middle, H right) {
    super(left, middle, right);
    this.first = first;
  }

  public MyFour(T first, MyTriple<R, S, H> triple) {
    super(triple);
    this.first = first;
  }

  public T getFirst() {
    return this.first;
  }
}
