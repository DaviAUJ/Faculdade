public class Main {
    public static void main(String[] args) {
        Aluno aluno1 = new Aluno("Sandro", new Data(), 7f, 5.5f, 8.9f);
        Aluno aluno2 = new Aluno("Eduardo", new Data(), 2.6f, 10f, 7.1f);
        Aluno aluno3 = new Aluno("Alex", new Data(), 1f, 5.5f, 5.3f);

        aluno1.nascimento.setAll((byte) 6, (byte) 4, (short) 2005);
        aluno2.nascimento.setAll((byte) 30, (byte) 2, (short) 1990);
        aluno3.nascimento.setAll((byte) -5, (byte) 13, (short) -1);

        System.out.println(aluno1.getNome() + ":");
        System.out.println("Data de nascimento: " + aluno1.nascimento.formatado());
        System.out.println("Media: " + String.format("%.2f", aluno1.getMedia()));

        System.out.println("\n" + aluno2.getNome() + ":");
        System.out.println("Data de nascimento: " + aluno2.nascimento.formatado());
        System.out.println("Media: " + String.format("%.2f", aluno2.getMedia()));

        System.out.println("\n" + aluno3.getNome() + ":");
        System.out.println("Data de nascimento: " + aluno3.nascimento.formatado());
        System.out.println("Media: " + String.format("%.2f", aluno3.getMedia()));
    }
}
