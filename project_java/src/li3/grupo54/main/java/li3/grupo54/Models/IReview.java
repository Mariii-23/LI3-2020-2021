package li3.grupo54.main.java.li3.grupo54.Models;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

public interface IReview {
    public String getReviewId();
    public String getUserId();
    public String getBusinessId();

    public float getStars();

    public int getUseful();
    public int getFunny();
    public int getCool();

    public LocalDateTime getDate();
    public String getText();

}
