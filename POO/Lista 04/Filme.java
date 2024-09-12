public class Filme extends Midia {
    private String diretor = "";

    public Filme() {  }
    public Filme(String titulo, int anoLancamento, String diretor, int preco) {
        super(titulo, anoLancamento, preco);
        this.diretor = diretor;
    }

    public void setDiretor(String diretor) {
        this.diretor = diretor;
    }

    public String getDiretor() {
        return diretor;
    }
}
