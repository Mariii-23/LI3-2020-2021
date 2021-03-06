package li3.grupo54.Models;

import java.io.Serializable;

/**
 * Contém os nomes dos 3 ficheiros necessários para usar o programa
 */
public class FileTriple implements Serializable {
    /**
     * Nome do ficehiro dos users.
     */
    private String usersFile;
    /**
     * Nome do ficheiro dos business.
     */
    private String businessesFile;
    /**
     * Noe dos ficheiros das reviews.
     */
    private String reviewsFile;

    public FileTriple(String usersFile, String businessesFile, String reviewsFile) {
        this.usersFile = usersFile;
        this.businessesFile = businessesFile;
        this.reviewsFile = reviewsFile;
    }

    /**
     * Devolve o  ficheiro que o utilizador escolheu para popular os Users.
     *
     * @return Ficheiro de Users
     */
    public String getUsersFile() {
        return usersFile;
    }

    public void setUsersFile(String usersFile) {
        this.usersFile = usersFile;
    }

    /**
     * Devolve o  ficheiro que o utilizador escolheu para popular os Businesses.
     *
     * @return Ficheiro de Businesses
     */
    public String getBusinessesFile() {
        return businessesFile;
    }

    public void setBusinessesFile(String businessesFile) {
        this.businessesFile = businessesFile;
    }

    /**
     * Devolve o  ficheiro que o utilizador escolheu para popular os Reviews.
     *
     * @return Ficheiro de Users
     */
    public String getReviewsFile() {
        return reviewsFile;
    }

    public void setReviewsFile(String reviewsFile) {
        this.reviewsFile = reviewsFile;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        FileTriple that = (FileTriple) o;
        return usersFile.equals(that.usersFile) && businessesFile.equals(that.businessesFile) && reviewsFile.equals(that.reviewsFile);
    }
}
