#include "../include/gestaoh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <cmath>

GestaoH::GestaoH() {
    estudantes_ = set<Student> {};
    horario_ = vector<TurmaH> {};
    pedido_ = queue<Pedido> {};
}

GestaoH::GestaoH(set<Student> estudantes, vector<TurmaH> horario, queue<Pedido> pedido) {
    estudantes_ = std::move(estudantes); // em vez de fazer estudantes_ = estudantes fazemos
    horario_ = std::move(horario);       // isso para não copiarmos o objeto duas vezes
    pedido_ = std::move(pedido);         // (sugestão do CLion)
}

void GestaoH::lerClasses() {
    string line1, line2, temp, word;
    string classCode1, classCode2, ucCode1, ucCode2, weekday, sstartHour, sduration, type, tempClassCode, tempUcCode;
    double startHour, duration;
    Slot aux;
    vector<TurmaH> horario; // criar vector de ucCode/classCode e uma list<Slot>
    string ficheiro = "../schedule/classes.csv";
    ifstream ifs1, ifs2;
    list<Slot> slot; // criar lista de slots para cada ucCode/classCode
    ifs1.open(ficheiro, ios::in);
    getline(ifs1, temp);
    // objetivo aqui é fazer dois ciclos para correr o ficheiro todo
    // visto que as mesmas ucCode/classCode não estão seguidas no ficheiro
    while(getline(ifs1, line1)) {
        stringstream s1(line1);
        getline(s1, classCode1, ','), getline(s1, ucCode1, ','), getline(s1, weekday, ','), getline(s1, sstartHour, ','), getline(s1, sduration, ','), getline(s1, type, '\r');
        startHour = stod(sstartHour), duration = stod(sduration); // converter para double a hora inicial e a duração
        aux = Slot(weekday, startHour, duration, type); // cria slot
        slot.push_back(aux); // adiciona slot à list<Slot>
        ifs2.open(ficheiro, ios::in);
        getline(ifs2, temp);
        while (getline(ifs2, line2)) {
            stringstream s2(line2);
            getline(s2, classCode2, ','), getline(s2, ucCode2, ','), getline(s2, weekday, ','), getline(s2, sstartHour, ','), getline(s2, sduration, ','), getline(s2, type, '\r');
            if (line1 != line2 && classCode1 == classCode2 && ucCode1 == ucCode2) { // verificar se é o mesmo par ucCode/classCode
                startHour = stod(sstartHour), duration = stod(sduration); // converter para double a hora inicial e a duração
                aux = Slot(weekday, startHour, duration, type); // cria slot
                slot.push_back(aux); // adiciona slot à list<Slot>
            }
        }
        ifs2.close(); // fechar o ficheiro para podermos abri-lo novamente desde o início
        TurmaH turmaH(ucCode1, classCode1, slot); // criar uma TurmaH com as informações todas
        horario.push_back(turmaH); // fazer push da TurmaH para o vector<TurmaH>
        slot = {}; // esvaziar a lista de slots para começar de novo
    }
    setHorario(horario); // povoar o vector<TurmaH>
}

void GestaoH::lerStudentClasses() {
    string line, temp, word, sstudentCode, studentName, ucCode, classCode, tempStudentName; // tempStudentName para guardar o nome estudante anterior
    int tempSstudentCode; // para guardar o código do estudante anterior
    set<Student> estudantes; // criar set de estudantes
    list<UcTurma> listaUcTurma; // criar lista de ucTurma para cada estudante
    UcTurma classUc; // criar UcTurma para cada conjunto de ucCode/classCode
    string ficheiro = "../schedule/students_classes.csv";
    ifstream ifs;
    ifs.open(ficheiro, ios::in); // abre ficheiro
    getline(ifs, temp); // passa a primeira linha à frente
    // como as cadeiras/turmas de cada estudante estão seguidas
    // só precisamos de fazer um ciclo
    while(getline(ifs, line)){
        stringstream s(line);
        getline(s, sstudentCode, ','), getline(s, studentName, ','), getline(s, ucCode, ','), getline(s, classCode, '\r');
        int studentCode = stoi(sstudentCode); // converter para int o código do estudante
        if (tempStudentName != studentName && !tempStudentName.empty()) { // esta condição serve para ignorarmos a primeira iteração e para verificarmos se já mudou para outro estudante
            Student estudante(tempSstudentCode, tempStudentName, listaUcTurma); // criar um objeto estudante
            estudantes.insert(estudante); // adicionar esse objeto estudante ao set<Student>
            listaUcTurma = {}; // esvaziar a list<UcTurma>
            // o próximo if é só para saber qual o tamanho do maior nome de um estudante
            if (tempStudentName.length() > getMaxLength()) {
                setMaxLength((int)tempStudentName.length());
            }
        }
        classUc.setUcCode(ucCode); // insere o ucCode
        classUc.setClassCode(classCode); // insere o classCode
        listaUcTurma.push_back(classUc); // adiciona o conjunto ucCode/classCode à list<UcTurma>
        tempStudentName = studentName; // muda o nome do estudante temporário para o estudante atual
        tempSstudentCode = studentCode; // muda o número do estudante temporário para o estudante atual
    }
    setEstudantes(estudantes); // povoar o set<Student>
}

// funções auxiliares para desenhar
// função para ajudar a centralizar textos
pair<int, int> auxCenterDraw(int n, bool v) {
    int pad1 = n;
    int pad2;
    if (v) {
        pad2 = pad1+1;
    }
    else {
        pad2 = pad1;
    }
    return pair<int, int> {pad1, pad2};
}

// ajuda a desenhar as horas das slots
void auxHourDraw(double n) {
    bool flag_decimal = true;
    bool flag_two_digits = false;

    if(ceil(n) == floor(n)) flag_decimal = false;
    if (n >= 10.0) flag_two_digits = true;

    if (flag_two_digits && flag_decimal) cout << "   " << n << "   |";
    else if (flag_two_digits) cout << "    " << n << "    |";
    else if (flag_decimal) cout << "   " << n << "    |";
    else cout << "    " << n << "     |";
}

// ajuda a desenhar o tipo das slots
void auxTypeDraw(const string& type) {
    switch (type.length()) {
        case 1:
            cout << "   " << type << "   |\n";
            break;
        case 2:
            cout << "   " << type << "  |\n";
            break;
    }
}

void GestaoH::drawEstudante(const Student& estudante, bool header, bool oneStudent) const {
    // desenha o cabeçalho quando é o primeiro estudante
    if (header) {
        cout << "+-------------+---------------------------+----------+-----------+\n"
                "| StudentCode |        StudentName        |  UcCode  | ClassCode |\n";
    }
    // apresenta as informações relativas a um estudante
    for (int i = 0; i < 36+getMaxLength(); i++) {
        if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
        cout << "-";
        if (i == 35+getMaxLength()) cout << "+\n";
    }
    cout << "|  " << estudante.getCode() << "  | ";
    pair<int, int> pad = auxCenterDraw(getMaxLength()-(int)estudante.getName().length(), (int)estudante.getName().length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << estudante.getName();
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    int c = 0;
    list<UcTurma> classUc = estudante.getTurmas();
    for (const UcTurma& u : classUc) {
        if (c > 0) {
            cout << "|             |                           ";
        }
        cout << "| " << u.getUcCode() << " |  " << u.getClassCode() << "  |\n";
        c++;
    }
    // desenha o rodapé se for para representar apenas um estudante
    if (oneStudent) {
        for (int i = 0; i < 36+getMaxLength(); i++) {
            if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
            cout << "-";
            if (i == 35+getMaxLength()) cout << "+\n";
        }
    }
}

void GestaoH::drawEstudantes() const {
    set<Student> estudantes = getEstudantes();
    int v = 1;
    for (const Student& s : estudantes) {
        drawEstudante(s, v, false);
        v = 0;
    }
    // desenha o rodapé
    for (int i = 0; i < 36+getMaxLength(); i++) {
        if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
        cout << "-";
        if (i == 35+getMaxLength()) cout << "+\n";
    }
}

void GestaoH::drawHorario() const {
    vector<TurmaH> horario = getHorario();
    cout << "+----------+-----------+-------------+----------+----------+-------+\n"
            "|  UcCode  | ClassCode |   Weekday   | Start H. | Final H. |  Type |\n";
    for (const TurmaH& s : horario) {
        for (int i = 0; i < 61; i++) {
            if (i == 0 || i == 10 || i == 21 || i == 34 || i == 44 || i == 54) cout << "+";
            cout << "-";
            if (i == 60) cout << "+\n";
        }
        if (s.getUcCode().length() == 5) cout << "|  " << s.getUcCode() << "   |  ";
        else cout << "| " << s.getUcCode() << " |  ";
        cout << s.getClassCode() << "  |  ";
        int c = 0;
        list<Slot> slot = s.getHorarioUcClass();
        for (const Slot& u : slot) {
            if (c > 0) {
                cout << "|          |           |  ";
            }
            pair<int, int> pad = auxCenterDraw(9-(int)u.getWeekday().length(), (int)u.getWeekday().length()%2 == 1);
            for (int f = 0; f < pad.first; f++) {
                cout << " ";
                ++f;
            }
            cout << u.getWeekday();
            for (int e = 0; e < pad.second; e++) {
                cout << " ";
                ++e;
            }
            cout << " |";
            auxHourDraw(u.getStartHour());
            auxHourDraw(u.getFinalHour());
            auxTypeDraw(u.getType());
            c++;
        }
    }
    for (int i = 0; i < 61; i++) {
        if (i == 0 || i == 10 || i == 21 || i == 34 || i == 44 || i == 54) cout << "+";
        cout << "-";
        if (i == 60) cout << "+\n";
    }
}

void GestaoH::drawMenu() {
    cout << "+-----------------------------------------+\n"
            "|        GESTAO DE HORARIOS               |\n"
            "+-----------------------------------------+\n"
            "| [1] - Listar estudantes e UCs           |\n"
            "| [2] - Listar um estudante em especifico |\n"
            "| [3] - Listar Blocos de Aulas            |\n"
            "| [Q] - Sair da aplicacao                 |\n"
            "+-----------------------------------------+\n";
    cout << ":";
}

set<Student> GestaoH::getEstudantes() const {
    return estudantes_;
}

vector<TurmaH> GestaoH::getHorario() const {
    return horario_;
}

queue<Pedido> GestaoH::getPedido() const {
    return pedido_;
}

Student GestaoH::getSpecificStudent(int n) const {
    set<Student> estudantes = getEstudantes();
    for (Student s : estudantes) {
        if (s.getCode() == n) {
            return s;
        }
    }
    return {};
}

int GestaoH::getMaxLength() const {
    return maxLength_;
}

void GestaoH::setEstudantes(set<Student> estudantes) {
    estudantes_ = std::move(estudantes);
}

void GestaoH::setHorario(vector<TurmaH> horario) {
    horario_ = std::move(horario);
}

void GestaoH::setPedido(queue<Pedido> pedido) {
    pedido_ = std::move(pedido);
}

void GestaoH::setMaxLength(int maxLength) {
    maxLength_ = maxLength;
}

void GestaoH::addPedido(const Pedido& pedido){
    pedido_.push(pedido);
}
