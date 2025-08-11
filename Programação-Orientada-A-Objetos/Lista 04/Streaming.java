public class Streaming {
    public int banco = 0;
    private Midia[] catalogo = new Midia[10];

    public Streaming() {  }

    public boolean cadastrarMidia(Midia midia) {
        for(int i = 0; i < catalogo.length; i++) {
            if(catalogo[i] == null) {
                catalogo[i] = midia;
                return true;
            }
        }
        
        return false;
    }
    
    public boolean removerMidia(String nome) {
        for(int i = 0; i < catalogo.length; i++) {
            if(catalogo[i].getTitulo().equals(nome) && !catalogo[i].getEmprestada()) {
                catalogo[i] = null;

                return true;
            }
        }

        return false;
    }
}
