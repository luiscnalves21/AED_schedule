#include <iostream>
#include "./include/student.h"
#include "./include/turmah.h"
#include "./include/pedido.h"
#include "./include/gestaoh.h"

// caso o input do utilizador não esteja entre os aceitados, apresenta uma mensagem de erro
void teclaErro() {
    cout << "\n+--------------+\n"
            "|Input Invalido|\n"
            "+--------------+\n\n";
}

// depois do utilizador escolher uma tarefa, aparece a opção de voltar ao menu
void voltar() {
    string op;
    cout << "\nPressione [V] para voltar ao Menu:";
    cin >> op;
    while (op != "V" && op != "v") {
        teclaErro();
        cout << "\nPressione [V] para voltar ao Menu:";
        cin >> op;
    }
}

// programa principal
int main() {
    GestaoH h; // cria um objeto h
    h.lerClasses(); // lê o ficheiro classes.csv
    h.lerStudentClasses(); // lê o ficheiro StudentClasses.csv
    // ciclo do programa
    while (true) {
        GestaoH::drawMenu(); // desenha o menu
        string op;
        cin >> op;
        if (op.length() != 1) {
            teclaErro();
            continue;
        }
        // dependendo do input do utilizador, vai executar tarefas diferentes
        if (op == "1") {
            h.drawEstudantes();
            voltar();
        }
        else if (op == "2") {
            Student estudante;
            int n;
            cout << "\nNumero UP: up";
            cin >> n;
            estudante = h.getSpecificStudent(n);
            if (estudante.getCode() == 0) cout << "O estudante especificado nao se encontra matriculado.\n";
            else h.drawEstudante(estudante, true);
            voltar();
        }
        else if (op == "3") {
            h.drawHorario();
            voltar();
        }
        else if (op == "4") {
            h.drawNumberOfStudentsPerUcTurma();
            voltar();
        }
        else if (op == "q" || op == "Q") break;
        else teclaErro();
    }
    return 0;
}
