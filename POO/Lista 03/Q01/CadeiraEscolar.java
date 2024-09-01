public class CadeiraEscolar extends Cadeira {
    private String tipoBraco;
    private boolean estaQuebrada;

    public String getTipoBraco() {
        return tipoBraco;
    }

    public boolean getEstaQuebrada() {
        return estaQuebrada;
    }

    public void quebrarBraco() {
        estaQuebrada = true;
    }

    public void consertarBraco() {
        estaQuebrada = false;
    }

    @Override
    public void empurrar() {
        System.out.println("Você derrubou o colega da frente!");
    }
}
