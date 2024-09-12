public class Aluno extends Pessoa {
    private float[] notas = new float[3];
    
    public Aluno() {  }
    public Aluno(String nome, Data nascimento, float nota1, float nota2, float nota3) {
        super(nome, nascimento);

        notas[0] = nota1;
        notas[1] = nota2;
        notas[2] = nota3;

        // Limitando as notas uma por vez
        for(byte i = 0; i < notas.length; i++) {
            if(notas[i] > 10) {
                notas[i] = 10;
            }
            else if(notas[i] < 0) {
                notas[i] = 0;
            }
        }
    }

    public void setNota1(float nota) {
        notas[0] = nota;
    }

    public void setNota2(float nota) {
        notas[1] = nota;
    }

    public void setNota3(float nota) {
        notas[2] = nota;
    }

    public float[] getNotas() {
        return notas;
    }

    public float getMedia() {
        return (notas[0] + notas[1] + notas[2]) / 3;
    }
}
