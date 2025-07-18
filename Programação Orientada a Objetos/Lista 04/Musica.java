public class Musica extends Midia {
    private String artista = "";

    public Musica() {  }
    public Musica(String titulo, int anoLancamento, String artista, int preco) {
        super(titulo, anoLancamento, preco);
        this.artista = artista;
    }

    public void setArtista(String artista) {
        this.artista = artista;
    }

    public String getArtista() {
        return artista;
    }
}
