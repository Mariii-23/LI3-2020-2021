package li3.grupo54.Models;

public interface ICatalog<T> {
    public int size();
    public void add(T t);
    public T getById(String id);
    public void delete(String id);
}
