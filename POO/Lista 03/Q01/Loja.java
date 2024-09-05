public class Loja {
    private String nome;
    private Cadeira[] estoque = new Cadeira[20];

    public Loja(String nome) {
        this.nome = nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public Cadeira RemoverCadeira(int index) {
        Cadeira output = null;
        Cadeira[] temp = new Cadeira[20];

        if(index < 0 || estoque == null || index >= estoque.length) {
            return null;
        }

        for(int i = 0, k = 0; i < estoque.length; i++) {
            if(i == index) { 
                output = estoque[i];
                continue; 
            }

            temp[k] = estoque[i];
            k++;
        }

        estoque = temp;

        return output;
    }
}
