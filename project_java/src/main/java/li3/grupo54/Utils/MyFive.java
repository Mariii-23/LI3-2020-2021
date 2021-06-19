package li3.grupo54.Utils;

import java.util.Objects;
/**
 * Auxiliary data structure for combining four different results, mostly for queries which require more than one information.
 * @param <T1> First Value
 * @param <T2> Second Value
 * @param <T3> Third Value
 * @param <T4> Fourth Value
 * @param <T5> Fith Value
 */
public class MyFive<T1,T2,T3,T4,T5> extends  MyFour<T1,T2,T3,T4>{
  /**
   * Quinto Objeto
   */
  private final T5 five;

  /**
   * Construtor que consoante 5 objetos dados devolve um objeto da classe MyFife
   * @param first
   * @param left
   * @param middle
   * @param right
   * @param five
   */
  public MyFive(T1 first, T2 left, T3 middle, T4 right, T5 five) {
    super(first, left, middle, right);
    this.five = five;
  }

  /**
   * Devolve o quinto objeto.
   * @return Quinto Objeto.
   */
  public T5 getFive() {
    return five;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    if (!super.equals(o)) return false;
    MyFive<?, ?, ?, ?, ?> myFive = (MyFive<?, ?, ?, ?, ?>) o;
    return Objects.equals(five, myFive.five);
  }

  @Override
  public int hashCode() {
    return Objects.hash(super.hashCode(), five);
  }
}
