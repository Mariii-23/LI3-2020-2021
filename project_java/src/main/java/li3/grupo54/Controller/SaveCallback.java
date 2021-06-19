package li3.grupo54.Controller;

import java.io.File;
import java.io.IOException;

public interface SaveCallback {
  public void run(File f) throws IOException;
}
