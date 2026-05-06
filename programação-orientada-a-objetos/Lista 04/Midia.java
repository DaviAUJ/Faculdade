public abstract class Midia {
    private String titulo = "";
    private int anoLancamento = 1;
    private int preco = 1;
    private boolean emprestada = false;

    public Midia() {  }
    public Midia(String titulo, int anoLancamento, int preco) {
        this.titulo = titulo;
        
        if(anoLancamento >= 1) {
            this.anoLancamento = anoLancamento;
        }
        
        if(preco >= 0) {
            this.preco = preco;
        }
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setAnoLancamento(int anoLancamento) {
        if(anoLancamento >= 1) {
            this.anoLancamento = anoLancamento;
        } 
        else {
            this.anoLancamento = 1;
        }
    }

    public int getAnoLancamento() {
        return anoLancamento;
    }

    public void setPreco(int preco) {
        if(preco >= 0) {
            this.preco = preco;
        }
        else {
            this.preco = 1;
        }
    }

    public int getPreco() {
        return preco;
    }

    public void setEmprestada(boolean emprestada) {
        this.emprestada = emprestada;
    }

    public boolean getEmprestada() {
        return emprestada;
    }
}
