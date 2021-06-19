package li3.grupo54.Models;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * Tuple which contains all the informations in StarsTuple as well as a set of reviews the user has reviews and the
 * businesses they correspond to.
 */
public class UserStarsTuple extends StarsTuple implements Serializable {
    /**
     * Set de reviews Id.
     */
    private final Set<String> reviews;
    /**
     * Set de Business Id
     */
    private final Set<String> business;

    /**
     * Construtor que apenas inicia um UserStarsTuple
     */
    public UserStarsTuple() {
        super();
        reviews = new HashSet<>();
        business = new HashSet<>();
    }

    /**
     * Construtor que inicia um UserStarsTuple a partir de uma dada review
     */
    public UserStarsTuple(Review review) {
        super(review.getStars(), 1);
        reviews = new HashSet<>();
        reviews.add(review.getReviewId());
        business = new HashSet<>();
        business.add(review.getBusinessId());
    }

    /**
     * Atualiza a sua informação consoante uma determinada review
     *
     * @param review Review a ser analisada
     */
    public void updateAverage(Review review) {
        super.update(review.getStars());
        reviews.add(review.getReviewId());
        business.add(review.getBusinessId());
    }

    /**
     * Retorna a média de estrelas atualmente associada  com um user
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
     * Devolve quantos business únicos foram analisados.
     *
     * @return Número único de business
     */
    public int getBusinessNumberDistint() {
        return this.business.size();
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
     * Devolve todos os id's únicos dos business analisados até ao momento.
     *
     * @return Set de business id
     */
    public Set<String> getBusiness() {
        return new HashSet<>(business);
    }
}
