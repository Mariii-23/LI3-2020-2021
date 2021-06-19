package li3.grupo54.Models;

/**
 * Contém os nomes dos 3 ficheiros necessários para usar o programa
 */
public class FileTriple {
  private String usersFile;
  private String businessesFile;
  private String reviewsFile;

  public FileTriple(String usersFile, String businessesFile, String reviewsFile) {
    this.usersFile = usersFile;
    this.businessesFile = businessesFile;
    this.reviewsFile = reviewsFile;
  }

  public String getUsersFile() {
    return usersFile;
  }

  public void setUsersFile(String usersFile) {
    this.usersFile = usersFile;
  }

  public String getBusinessesFile() {
    return businessesFile;
  }

  public void setBusinessesFile(String businessesFile) {
    this.businessesFile = businessesFile;
  }

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
