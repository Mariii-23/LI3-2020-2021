package li3.grupo54.Utils;

import java.io.Serializable;
import java.util.Objects;

/**
 * Classe desenvolida para conseguir armazenar 4 quaisqueres objetos.
 * Esta classe foi desenvolvida aproveitando a classe já existente MyTriple
 *
 * @param <T> Primeiro Objeto
 * @param <R> Segundo Objeto
 * @param <S> Terceiro Objeto
 * @param <H> Quarto Objeto
 */
public class MyFour<T, R, S, H> extends MyTriple<R, S, H> implements Serializable {
    private T first;

    /**
     * Construtor que retorna um MyFour à custa de 4 objetos fornecidos.
     *
     * @param first  Primeiro Objeto
     * @param left   Segundo Objeto
     * @param middle Terceiro Objeto
     * @param right  Quarto Objeto
     */
    public MyFour(T first, R left, S middle, H right) {
        super(left, middle, right);
        this.first = first;
    }

    /**
     * Construtor que retorna um myFour a partir de um MyTriple 3 e um outro objeto dado.
     *
     * @param first  Objeto a adicionar
     * @param triple Triplo
     */
    public MyFour(T first, MyTriple<R, S, H> triple) {
        super(triple);
        this.first = first;
    }

    public T getFirst() {
        return this.first;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        MyFour<?, ?, ?, ?> myFour = (MyFour<?, ?, ?, ?>) o;
        return Objects.equals(first, myFour.first);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), first);
    }
}
