package li3.grupo54.Utils;

import java.io.Serializable;
import java.util.Objects;

/**
 * @param <T>  First generic parameter
 * @param <T1> Middle generic parameter
 * @param <T2> Third generic parameter
 *             Auxiliary data structure for combining three different results, mostly for queries which require more than one information.
 */
public class MyTriple<T, T1, T2> implements Serializable {

    /**
     * Primeiro elemento.
     */
    private T left;
    /**
     * Segundo elemento.
     */
    private T1 middle;
    /**
     * Terceiro elemento.
     */
    private T2 right;

    /**
     * Contruí um MyTriple a partir de três objetos dados.
     *
     * @param left   Primeiro elemento
     * @param middle Segundo elemento
     * @param right  Terceiro elemento
     */
    public MyTriple(T left, T1 middle, T2 right) {
        this.left = left;
        this.middle = middle;
        this.right = right;
    }

    /**
     * Contruí um MyTriple a parir de uma mesma classe dada
     *
     * @param that
     */
    public MyTriple(MyTriple<T, T1, T2> that) {
        this.left = that.getLeft();
        this.middle = that.getMiddle();
        this.right = that.right;
    }

    /**
     * Devolve o primeiro objeto.
     *
     * @return Primeiro Objeto
     */
    public T getLeft() {
        return left;
    }

    /**
     * Substitui o primeiro objeto por um novo da mesma classe.
     *
     * @param left Objeto a substituir.
     */
    public void setLeft(T left) {
        this.left = left;
    }

    /**
     * Devolve o segundo objeto.
     *
     * @return Segundo Objeto
     */
    public T1 getMiddle() {
        return middle;
    }

    /**
     * Substitui o segundo objeto por um novo da mesma classe.
     *
     * @param middle Objeto a substituir.
     */
    public void setMiddle(T1 middle) {
        this.middle = middle;
    }

    /**
     * Devolve o terceiro objeto.
     *
     * @return Terceiro Objeto
     */
    public T2 getRight() {
        return right;
    }

    /**
     * Substitui o terceiro objeto por um novo da mesma classe.
     *
     * @param right Objeto a substituir.
     */
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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        MyTriple<?, ?, ?> myTriple = (MyTriple<?, ?, ?>) o;
        return Objects.equals(left, myTriple.left) && Objects.equals(middle, myTriple.middle) && Objects.equals(right, myTriple.right);
    }

    @Override
    public int hashCode() {
        return Objects.hash(left, middle, right);
    }
}
