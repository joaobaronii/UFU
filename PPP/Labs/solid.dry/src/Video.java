public class Video extends Publicacao{
    String autor;
    String duracao;

    public Video(String titulo, String ano, String autor, String duracao) {
        super(titulo, ano);
        this.autor = autor;
        this.duracao = duracao;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public String getAutor() {
        return autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public String getDuracao() {
        return duracao;
    }

    public void setDuracao(String duracao) {
        this.duracao = duracao;
    }

    @Override
    public String toString() {
        return "Video: " + titulo + ", " + autor + ", " + duracao;
    }
}
