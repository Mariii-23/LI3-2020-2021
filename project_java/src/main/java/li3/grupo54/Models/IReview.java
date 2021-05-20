package li3.grupo54.Models;

public interface IReview {
    public String getId();
    public String getText();
    public String getUserId();
    public String getBusinessId();

    public double getStars();

    public int getUseful();
    public int getFunny();
    public int getCool();

    public String getDate();
}
