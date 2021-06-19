package li3.grupo54.Models;

public class Leitura {
    public static char determineDelimiter(String line) {

        char[] delims = {',', ';', '?', '%', '$'};
        for (char c : delims) {
            if (line.indexOf(c) != -1) {
                return c;
            }
        }
        return ';';
    }
}