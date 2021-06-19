package li3.grupo54.Models.Interfaces;

import java.io.Serializable;
import java.util.Set;

/**
 * Interface whose methods need be implemented by any class which wants to have the behaviour of a business.
 */
public interface IBusiness extends Serializable {
    /**
     * Devolve o seu ID.
     *
     * @return String
     */
    public String getId();

    /**
     * Devolve o seu Nome.
     *
     * @return String
     */
    public String getName();

    /**
     * Devolve a cidade aonde este pertence.
     *
     * @return String
     */
    public String getCity();

    /**
     * Devolve o estado aonde este pertence.
     *
     * @return String
     */
    public String getState();

    /**
     * Categorias a que esse business pode ser enquadrado.
     *
     * @return Set&lt;String&gt;
     */
    public Set<String> getCategories();

    /**
     * Método que devolve um seu clone.
     *
     * @return Business clone.
     */
    public IBusiness clone();
}