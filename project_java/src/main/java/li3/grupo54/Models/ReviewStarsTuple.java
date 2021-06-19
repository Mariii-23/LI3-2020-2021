package li3.grupo54.Models;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * Tuple which contains a set of reviews, which meet a certain criteria, the set of users
 * which made them as well as the businesses they correspond to.
 */

public class ReviewStarsTuple extends StarsTuple implements Serializable {
    /**
     * Set de reviews Id.
     */
    private final Set<String> reviews;
    /**
     * Set de Users Id
     */
    private final Set<String> users;
    /**
     * Set de Business Id
     */
    private final Set<String> business;


    /**
     * Construtor que apenas inicia uma ReviewStarsTuple
     */
    public ReviewStarsTuple() {
        super();
        reviews = new HashSet<>();
        users = new HashSet<>();
        business = new HashSet<>();
    }

    /**
     * Construtor que inicia uma ReviewStarsTuple a partir de uma dada review
     */
    public ReviewStarsTuple(Review review) {
        super(review.getStars(), 1);
        reviews = new HashSet<>();
        users = new HashSet<>();
        business = new HashSet<>();
    }

    /**
     * Atualiza os campos dos sets consoante a informação contida na review dada e da sua média.
     *
     * @param review Review a ser analisada
     */
    public void updateAverage(Review review) {
        super.update(review.getStars());
        reviews.add(review.getReviewId());
        users.add(review.getUserId());
        business.add(review.getBusinessId());
    }

    /**
     * Retorna a média de estrelas
     *
     * @return Média atual
     */
    public double getCurrentAverage() {
        return super.getCurrentAverage();
    }

    /**
     * Devolve quantas reviews únicas foram lidas.
     *
     * @return Número único de reviews
     */
    public int getReviewsNumber() {
        return super.getNumberTotal();
    }

    /**
     * Devolve todos os id's únicos das reviews analisadas até ao momento.
     *
     * @return Set de reviews id
     */
    public Set<String> getReviews() {
        return new HashSet<>(reviews);
    }

    /**
     * Devolve quantos users únicos foram lidos.
     *
     * @return Número único de users
     */
    public Integer getUserDistincts() {
        return this.users.size();
    }

    /**
     * Devolve quantos business únicos foram lidos.
     *
     * @return Número único de business
     */
    public Integer getBusinessDistincts() {
        return this.business.size();
    }
}
