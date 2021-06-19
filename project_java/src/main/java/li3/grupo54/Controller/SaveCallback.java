package li3.grupo54.Controller;

import java.io.File;
import java.io.IOException;

/**
 * Callback associated with the action of saving the  model to an object file
 */
public interface SaveCallback {
    public void run(File f) throws IOException;
}
