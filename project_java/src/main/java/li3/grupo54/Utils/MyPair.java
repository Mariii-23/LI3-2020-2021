package li3.grupo54.Utils;

import java.io.Serializable;
import java.util.Objects;

/**
 * Auxiliary data structure for combining two different results, mostly for queries which require more than one information.
 *
 * @param <T> First generic value
 * @param <R> Second generic value
 */
public class MyPair<T, R> implements Serializable {
    /**
     * Primeiro elemento.
     */
    private T x;
    /**
     * Segundo elemento.
     */
    private R y;

    public MyPair(T x, R y) {
        this.x = x;
        this.y = y;
    }

    public MyPair(MyPair<T, R> that) {
        this.x = that.getX();
        this.y = that.getY();
    }

    /**
     * Retorna o primeiro elemento armazenado.
     *
     * @return Primeira classe
     */
    public T getX() {
        return x;
    }

    /**
     * Altera o primeiro elemento armazenado por um outro.
     */
    public void setX(T x) {
        this.x = x;
    }

    /**
     * Retorna o segundo elemento armazenado.
     *
     * @return Segunda classe
     */
    public R getY() {
        return y;
    }

    /**
     * Altera o segundo elemento armazenado por um outro.
     */
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
