public class Livro extends Publicacao{
    String autor;

    public Livro(String titulo, String ano, String autor) {
        super(titulo, ano);
        this.autor = autor;
    }

    public String getAutor() {
        return autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    @Override
    public String toString() {
        return "Livro: " + titulo + " " + autor + " " + ano;
    }
}
