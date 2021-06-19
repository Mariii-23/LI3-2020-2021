package li3.grupo54.Utils;

import static java.lang.System.nanoTime;

// Classe utilizada para a medição de performance

/**
 * Classe Crono, é uma classe utilizada essencialmente para a medição da performance do nosso programa.
 */
public class Crono {
  static long begin = 0L;
  static long end = 0L;

  /**
   * Método que reinicía a contagem do tempo.
   */
  public static void start() {
    end = 0L;
    begin = nanoTime();
  }

  /**
   * Método que calcúla o tempo que passou desde a chamada do método start.
   * @return Double
   */
  public static double stop() {
    end = nanoTime();
    return (end - begin) / 1e9;
  }
}
