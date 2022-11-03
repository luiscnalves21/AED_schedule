#include <iostream>
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
            h.drawEstudantes({});
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
            h.drawEstudantes(h.studentsPerYear());
            Menu::voltar();
        }
        else if (op == "5") {
            h.drawEstudantes(h.studentsPerUcPerClass());
            Menu::voltar();
        }
        else if (op == "6") {

        }
        else if (op == "7") {
            Student estudante;
            int n;
            cout << "\nNumero UP: up";
            cin >> n;
            estudante = h.getSpecificStudent(n);
            if (estudante.getCode() == 0) cout << "O estudante especificado nao se encontra matriculado.\n";
            else h.drawEstudante(estudante, true);
            Menu::voltar();
        }
        else if (op == "8"){ // operação para adicionar pedido
            vector<Pedido> pedido;
            queue<vector<Pedido>> pedido_;
            int n;
            string uc, initialClass, type, finalClass;
            while (true) {
                GestaoH::drawPedido();
                string p, press;
                cin >> p;
                if (p == "A" || p == "a") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    cout << "\nIndique a turma que pretende ficar: "; cin >> finalClass;
                    type = "A";
                    //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                    Pedido aux = Pedido(n, type, initialClass, finalClass, uc);
                    pedido.push_back(aux);
                    pedido_.push(pedido);
                }
                else if (p == "R" || p == "r") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    cout << "\nIndique a turma que pretende remover: "; cin >> initialClass;
                    type = "R";
                    //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                    Pedido aux = Pedido(n, type, initialClass, finalClass, uc);
                    pedido.push_back(aux);
                    pedido_.push(pedido);
                }
                else if (p == "T" || p == "t") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    cout << "\nIndique a turma em que esta de momento: "; cin >> initialClass;
                    cout << "\nIndique a turma para onde pretende mudar: "; cin >> finalClass;
                    type = "T";
                    //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                    Pedido aux = Pedido(n, type, initialClass, finalClass, uc);
                    pedido.push_back(aux);
                    pedido_.push(pedido);
                }
                else if (p == "C" || p == "c") {
                    cout << "\nIndique o numero do estudante: "; cin >> n;
                    cout << "\nIndique a unidade curricular: "; cin >> uc;
                    type = "CT";
                    while (true) {
                        cout << "\nIndique a turma em que esta de momento: "; cin >> initialClass;
                        cout << "\nIndique a turma para onde pretende mudar: "; cin >> finalClass;
                        //é preciso verificar se uc e initialClass/finalClass estão bem escritos! (uc deve ter LEIC ou UP na string e as turmas devem ter L.EIC)
                        Pedido aux = Pedido(n, type, initialClass, finalClass, uc);
                        pedido.push_back(aux);
                        cout << "\nPressione S para sair, C para outro pedido";
                        cin >> press;
                        if (press == "S" || press == "s") {
                            break;
                        }
                    }
                    pedido_.push(pedido);
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
        else if (op == "q" || op == "Q") break;
        else Menu::teclaErro();
    }
    return 0;
}
