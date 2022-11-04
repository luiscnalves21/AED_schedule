#include <iostream>
#include <algorithm>
#include "./include/student.h"
#include "./include/turmah.h"
#include "./include/pedido.h"
#include "./include/gestaoh.h"
#include "./include/menu.h"

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
            Menu::teclaErro();
            continue;
        }
        // dependendo do input do utilizador, vai executar tarefas diferentes
        if (op == "1") {
            bool mS = GestaoH::mostrarSpecs();
            if (mS) h.drawEstudantes({}, false);
            else h.drawEstudantes({}, true);
            Menu::voltar();
        }
        else if (op == "2") {
            h.drawHorario();
            Menu::voltar();
        }
        else if (op == "3") {
            h.drawNumberOfStudentsPerUcTurma();
            Menu::voltar();
        }
        else if (op == "4") {
            set<Student> estudantes = h.studentsPerYear();
            bool mS = GestaoH::mostrarSpecs();
            if (mS) h.drawEstudantes(estudantes, false);
            else h.drawEstudantes(estudantes, true);
            Menu::voltar();
        }
        else if (op == "5") {
            while (true) {
                set<Student> estudantes = h.studentsPerUcPerClass();
                if (estudantes.empty()) {
                    cout << "\n+--------------------------------+\n"
                            "|  Unidade Curricular incorreta  |\n"
                            "|  ou Numero da turma incorreto  |\n"
                            "+--------------------------------+\n"
                            "|          TENTE DE NOVO         |\n"
                            "+--------------------------------+\n";
                }
                else {
                    bool mS = GestaoH::mostrarSpecs();
                    if (mS) h.drawEstudantes(estudantes, false);
                    else h.drawEstudantes(estudantes, true);
                    break;
                }
            }
            Menu::voltar();
        }
        else if (op == "6") {
            while (true) {
                set<Student> estudantes = h.studentsPerUc();
                if (estudantes.empty()) {
                    cout << "\n+--------------------------------+\n"
                            "|  Unidade Curricular incorreta  |\n"
                            "+--------------------------------+\n"
                            "|          TENTE DE NOVO         |\n"
                            "+--------------------------------+\n";
                }
                else {
                    bool mS = GestaoH::mostrarSpecs();
                    if (mS) h.drawEstudantes(estudantes, false);
                    else h.drawEstudantes(estudantes, true);
                    break;
                }
            }
            Menu::voltar();
        }
        else if (op == "7") {
            Student estudante;
            estudante = h.getSpecificStudent();
            if (estudante.getCode() == 0) cout << "O estudante especificado nao se encontra matriculado.\n";
            else h.drawEstudante(estudante, true, false);
            Menu::voltar();
        }
        else if (op == "8") {
            Student estudante;
            estudante = h.getSpecificStudent();
            if (estudante.getCode() == 0) cout << "O estudante especificado nao se encontra matriculado.\n";
            else h.drawHorarioEstudante(estudante);
            Menu::voltar();
        }
        else if (op == "9"){ // operação para adicionar pedido
            vector<Pedido> pedido;
            queue<vector<Pedido>> pedido_;
            int n;
            string uc, initialClass, tipo, finalClass;
            while (true) {
                GestaoH::drawPedido();
                string p, press;
                cin >> p;
                if (p == "A" || p == "a") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    cout << "\nIndique a turma que pretende ficar: "; cin >> finalClass;
                    tipo = "A";
                    //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                    Pedido aux = Pedido(n, tipo, initialClass, finalClass, uc);
                    pedido.push_back(aux);
                    pedido_.push(pedido);
                    pedido.clear();
                }
                else if (p == "R" || p == "r") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    cout << "\nIndique a turma que pretende remover: "; cin >> initialClass;
                    tipo = "R";
                    //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                    Pedido aux = Pedido(n, tipo, initialClass, finalClass, uc);
                    pedido.push_back(aux);
                    pedido_.push(pedido);
                    pedido.clear();
                }
                else if (p == "T" || p == "t") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    cout << "\nIndique a turma em que esta de momento: "; cin >> initialClass;
                    cout << "\nIndique a turma para onde pretende mudar: "; cin >> finalClass;
                    tipo = "T";
                    //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                    Pedido aux = Pedido(n, tipo, initialClass, finalClass, uc);
                    pedido.push_back(aux);
                    pedido_.push(pedido);
                    pedido.clear();
                }
                else if (p == "C" || p == "c") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    tipo = "CT";
                    while (true) {
                        cout << "\nIndique a unidade curricular: "; cin >> uc;
                        cout << "\nIndique a turma em que esta de momento: "; cin >> initialClass;
                        cout << "\nIndique a turma para onde pretende mudar: "; cin >> finalClass;
                        //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                        Pedido aux = Pedido(n, tipo, initialClass, finalClass, uc);
                        pedido.push_back(aux);
                        cout << "\nPressione S para sair, N para outro pedido: ";
                        cin >> press;
                        if (press == "S" || press == "s") {
                            break;
                        }
                    }
                    pedido_.push(pedido);
                    pedido.clear();
                }
                else if (p == "V" || p == "v") {
                    break;
                }
                else {
                    Menu::teclaErro();
                    continue;
                }
                h.setPedido(pedido_);
            }
        }
        else if(op == "P" || op == "p"){
            h.processarPedidos();
            Menu::voltar();
        }
        else if (op == "q" || op == "Q") break;
        else Menu::teclaErro();
    }
    return 0;
}
