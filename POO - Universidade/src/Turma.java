import java.util.ArrayList;
import java.util.List;

public class Turma implements Exibivel{
    private List<Estudante> alunos;
    private Professor professor;
    private int ano;
    private int semestre;
    private Disciplina disciplina;

    public Turma(List<Estudante> alunos, Professor professor, int ano, int semestre, Disciplina disciplina) {
        this.alunos = new ArrayList<Estudante>(alunos);
        this.professor = professor;
        this.ano = ano;
        this.semestre = semestre;
        this.disciplina = disciplina;
    }

    public Disciplina getDisciplina() {
        return disciplina;
    }

    public void setDisciplina(Disciplina disciplina) {
        this.disciplina = disciplina;
    }

    public void setAlunos(List<Estudante> alunos) {
        this.alunos = alunos;
    }

    public void setProfessor(Professor professor) {
        this.professor = professor;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public void setSemestre(int semestre) {
        this.semestre = semestre;
    }


    public List<Estudante> getAlunos() {
        return alunos;
    }

    public Professor getProfessor() {
        return professor;
    }

    public int getAno() {
        return ano;
    }

    public int getSemestre() {
        return semestre;
    }

    // metodos lista
    public boolean adicionarEstudante(Estudante aluno) {
        return alunos.add(aluno);
    }

    public boolean removerEstudante(String CPF) {

        for (Estudante aluno : alunos) {
            if (aluno.getCPF().equals(CPF)) {
                alunos.remove(aluno);
                return true;
            }
        }
        return false;
    }

    public Estudante buscarEstudante(String CPF) {
        for (Estudante aluno : alunos) {
            if (aluno.getCPF().equals(CPF)) {
                return aluno;
            }
        }
        return null;
    }

    public void showStudentList() {
        for (Estudante aluno : alunos) {
            System.out.println(aluno.mostrarDados());
            System.out.println("\n\n\n");
        }
    }

    public Estudante searchStudent(String CPF) {
        for (Estudante aluno : alunos) {
            if (aluno.getCPF().equals(CPF)) {
                return aluno;
            }
        }
        return null;
    }

    // metodo abstrato
    @Override
    public String mostrarDados() {
        return "Disciplina: " + disciplina.getNome() + "\nCodigo: " + disciplina.getCodigo() + "\nCarga Horaria: " + disciplina.getCargaHoraria() + "\nAno: " + ano + "\nSemestre: " + semestre + "\nProfessor:" + professor.getNome()+ " - " + professor.getCPF() + "\n\n\n";
    }

}
