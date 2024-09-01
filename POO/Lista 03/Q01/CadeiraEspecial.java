public class CadeiraEspecial extends Cadeira {
    private final int rodasGrandes = 2;
    private final int rodasPequenas = 2;

    public int getRodasGrandes() {
        return rodasGrandes;
    }

    public int getRodasPequenas() {
        return rodasPequenas;
    }

    public int getTotalRodas() {
        return rodasPequenas + rodasGrandes;
    }

    @Override
    public void empurrar() {
        System.out.println("Cuidado para não empurrar forte de mais");
    }
}