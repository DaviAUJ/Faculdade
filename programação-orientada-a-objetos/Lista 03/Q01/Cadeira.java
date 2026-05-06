public abstract class Cadeira {
    private int quantPernas;
    private String material;
    private String cor;

    public int getQuantPernas() {
        return quantPernas;
    }

    public String getMaterial() {
        return material;
    }

    public String getCor() {
        return cor;
    }

    abstract public void empurrar();
}