package li3.grupo54.Utils;

public class MyTriple<T, T1, T2> {
    private T left;
    private T1 middle;
    private T2 right;

    public MyTriple(T left, T1 middle, T2 right) {
        this.left = left;
        this.middle = middle;
        this.right = right;
    }

    public T getLeft() {
        return left;
    }

    public void setLeft(T left) {
        this.left = left;
    }

    public T1 getMiddle() {
        return middle;
    }

    public void setMiddle(T1 middle) {
        this.middle = middle;
    }

    public T2 getRight() {
        return right;
    }

    @Override
    public String toString() {
        return "MyTriple{" +
                "left=" + left +
                ", middle=" + middle +
                ", right=" + right +
                '}';
    }

    public void setRight(T2 right) {
        this.right = right;
    }
}
