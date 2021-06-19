package li3.grupo54.Utils;

import java.util.Objects;

/**
 * Classe desenvolvida para ser possível o armazenamento de 5 quaisquer objetos.
 * Esta classe foi escrita aproveitando a existêcia da classe MyFour.
 * @param <T1> Primeiro Objeto
 * @param <T2> Segundo Objeto
 * @param <T3> Terceiro Objeto
 * @param <T4> Quarto Objeto
 * @param <T5> Quinto Objeto
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
