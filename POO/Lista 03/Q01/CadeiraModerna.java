public class CadeiraModerna extends Cadeira {
    private String tipoTronco;
    private String tipoRodinhas;
    private int quantRodinhas;

    public CadeiraModerna() { }

    public CadeiraModerna(String tipoTronco, String tipoRodinhas, int quantRodinhas) {
        this.tipoTronco = tipoTronco;
        this.tipoRodinhas = tipoRodinhas;
        this.quantRodinhas = quantRodinhas;
    }

    public String getTipoTronco() {
        return tipoTronco;
    }

    public void setTipoTronco(String nome) {
        tipoTronco = nome;
    }

    public String getTipoRodinhas() {
        return tipoRodinhas;
    }

    public void setRodinhas(String nome) {
        tipoTronco = nome;
    }

    public int getQuantRodinhas() {
        return quantRodinhas;
    }

    @Override
    public void empurrar() {
        System.out.println("Você jogou ela para o outro lado da sala");
    }
}
