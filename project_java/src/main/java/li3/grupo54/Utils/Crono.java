package li3.grupo54.Utils;

import static java.lang.System.nanoTime;
/**
 * Classe utilizada para a medição de performance
 */

public class Crono {
  static long begin = 0L;
  static long end = 0L;

  public static void start() {
    end = 0L;
    begin = nanoTime();
  }

  public static double stop() {
    end = nanoTime();
    return (end - begin) / 1e9;
  }
}
