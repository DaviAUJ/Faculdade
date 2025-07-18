public class Pessoa {
    private String nome;
    public Data nascimento;

    public Pessoa() {  }

    public Pessoa(String nome, Data nascimento) {
        this.nome = nome;
        this.nascimento = nascimento;
    }

    public Pessoa(String nome, byte dia, byte mes, short ano) {
        this.nome = nome;
        this.nascimento = new Data(dia, mes, ano);
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }
}
