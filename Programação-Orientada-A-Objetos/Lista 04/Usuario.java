public class Usuario {
    private String nome = "";
    private int creditos = 0;
    private Midia[] inventario = new Midia[3];

    public Usuario() {  }
    public Usuario(String nome, int creditos) {
        this.nome = nome;
        this.creditos = creditos;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public int getCreditos() {
        return creditos;
    }
}
