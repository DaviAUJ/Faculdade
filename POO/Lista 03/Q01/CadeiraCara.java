public class CadeiraCara extends Cadeira {
    private String materialRecheio;
    private String materialEstofado;
    private boolean estaRasgado = false;

    public CadeiraCara() {}

    public CadeiraCara(String materialRecheio, String materialEstofado) {
        this.materialRecheio = materialRecheio;
        this.materialEstofado = materialEstofado;
    }

    public String getMaterialRecheio() {
        return materialRecheio;
    }

    public String getMaterialEstofado() {
        return materialEstofado;
    }

    public boolean getEstaRasgado() {
        return estaRasgado;
    }

    public void rasgarEstofado() {
        estaRasgado = true;
    }

    public void remendarEstofado() {
        estaRasgado = false;
    }

    @Override
    public void empurrar() {
        System.out.println("Não empurre a cadeira cara para não arranhar");
    }
}
