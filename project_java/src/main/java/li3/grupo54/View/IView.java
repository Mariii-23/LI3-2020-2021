package li3.grupo54.View;

import li3.grupo54.Controller.CallbackFileTriple;
import li3.grupo54.Controller.ExecuteCallback;
import li3.grupo54.Controller.SaveCallback;
import li3.grupo54.Models.FileTriple;
import li3.grupo54.View.Queries.IQueryView;

import java.io.File;

/**
 * A view.
 */
public interface IView {
    /**
     * Aprensenta a view
     */
    public void show();

    /**
     * Pede ao utilizador que escolha os ficheiros para popular o model
     */
    public FileTriple getFileTriple();

    /**
     * Apresenta uma mensagem de erro ao utilizador
     */
    public void showError(String title, String description);

    /**
     * Configura o callback para quando os 3 ficheiros de populacao do modelo sao escolhidos
     */
    public void setOpenCallback(CallbackFileTriple callback);

    /**
     * Adiciona uma view de uma query
     */
    public void addQuery(IQueryView query, ExecuteCallback callback);

    /**
     * Configura o callback para quando o utilizador decide persistir o estado da aplicação
     */
    public void setOnSave(SaveCallback callback);

    /**
     * Pede ao utilizador que escolha onde quer guardar um ficheiro
     */
    public File getSaveLocation();

    /**
     * Desativa as queries
     */
    public void disableQueries(boolean disable);

    /**
     * Configura a callback para quando estado persistido tem de ser restaurado
     */
    void setOnRestore(SaveCallback callback);
}
