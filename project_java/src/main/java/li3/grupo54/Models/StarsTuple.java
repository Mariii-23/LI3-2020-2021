package li3.grupo54.Models;

import java.io.Serializable;
import java.util.Comparator;

/**
 * Tuple which contains the average rating for a given business calculated up to that point and the total number of reviews which were used in that mean.
 */

public class StarsTuple implements Comparator<StarsTuple>, Serializable {
    /**
     * Média atual
     */
    private double currentAverage;
    /**
     * Número total
     */
    private int numberTotal;

    /**
     * Inicializa um Stars Tuple a 0.
     */
    public StarsTuple() {
        currentAverage = 0;
        numberTotal = 0;
    }

    /**
     * Construtor que inicializa um Stars Tuples partir de dois valores dados.
     *
     * @param currentAverage Média atual
     * @param numberTotal    Número total
     */
    public StarsTuple(double currentAverage, int numberTotal) {
        this.currentAverage = currentAverage;
        this.numberTotal = numberTotal;
    }

    /**
     * Método que efetua o update de Stars Tuple a partir de um dado valor.
     *
     * @param value Valor a ser analisado
     */
    public void update(double value) {
        currentAverage = (currentAverage * numberTotal + value) / (++numberTotal);
    }

    /**
     * Devolve a média Atual
     *
     * @return Média atual
     */
    public double getCurrentAverage() {
        return currentAverage;
    }

    /**
     * Devolve o número de todos os valores recebidos
     *
     * @return Número de valores recebidos
     */
    public int getNumberTotal() {
        return numberTotal;
    }

    @Override
    public int compare(StarsTuple starsTuple, StarsTuple t1) {
        return (int) (starsTuple.getCurrentAverage() - t1.getCurrentAverage());
    }
}
