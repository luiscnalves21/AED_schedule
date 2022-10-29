#include "../include/gestaoh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

GestaoH::GestaoH() {
    estudantes_ = set<Student> {};
    horario_ = vector<TurmaH> {};
    pedido_ = queue<Pedido> {};
}

GestaoH::GestaoH(set<Student> estudantes, vector<TurmaH> horario, queue<Pedido> pedido) {
    estudantes_ = estudantes;
    horario_ = horario;
    pedido_ = pedido;
}

void GestaoH::lerClasses() {
    // o objetivo é povoar vector<TurmaH>
    // temos que criar um vector<TurmaH>
    // ver parte dos slots
    string line, temp, word;
    string classCode, ucCode, weekday, sstartHour, sduration, type;
    string ficheiro = "classes.csv";
    ifstream ifs;
    list<Slot> horario;
    ifs.open(ficheiro, ios::in);
    getline(ifs, temp);
    while(getline(ifs, line)){
        stringstream s(line);
        getline(s, classCode, ','), getline(s, ucCode, ','), getline(s, weekday, ','), getline(s, sstartHour, ','), getline(s, sduration, ','), getline(s, type, '\r');
        double startHour = stod(sstartHour), duration = stod(sduration);
        Slot aux = Slot(weekday, startHour, duration, type); // cria slot
        horario.push_back(aux); // adiciona slot ao horario
        TurmaH F = TurmaH(ucCode, classCode, horario); // rever esta parte e as slots
    }
}

void GestaoH::lerStudentClasses() {
    string line, temp, word, sstudentCode, studentName, ucCode, classCode, tempStudentName; // tempStudentName para guardar o estudante anterior
    int tempSstudentCode; // para guardar o código do estudante anterior
    set<Student> estudantes; // criar set de estudantes
    list<UcTurma> listaUcTurma; // criar lista de ucTurma do estudante
    UcTurma classUc;
    string ficheiro = "../schedule/students_classes.csv";
    ifstream ifs;
    ifs.open(ficheiro, ios::in); // abre ficheiro
    getline(ifs, temp); // passa a primeira linha à frente
    while(getline(ifs, line)){
        stringstream s(line);
        getline(s, sstudentCode, ','), getline(s, studentName, ','), getline(s, ucCode, ','), getline(s, classCode, '\r');
        int studentCode = stoi(sstudentCode); // converter para int o código do estudante
        if (tempStudentName != studentName && !tempStudentName.empty()) {
            Student estudante(tempSstudentCode, tempStudentName, listaUcTurma);
            estudantes.insert(estudante);
            listaUcTurma = {};
            if (tempStudentName.length() > getMaxLength()) {
                setMaxLength((int)tempStudentName.length());
            }
        }
        classUc.setUcCode(ucCode);
        classUc.setClassCode(classCode);
        listaUcTurma.push_back(classUc);
        tempStudentName = studentName;
        tempSstudentCode = studentCode;
    }
    setEstudantes(estudantes);
}

void GestaoH::drawEstudantes() const {
    set<Student> estudantes = getEstudantes();
    cout << "+-------------+---------------------------+----------+-----------+\n"
            "| StudentCode |        StudentName        |  UcCode  | ClassCode +\n";
    for (const Student& s : estudantes) {
        for (int i = 0; i < 36+getMaxLength(); i++) {
            if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
            cout << "-";
            if (i == 35+getMaxLength()) cout << "+\n";
        }
        int pad1 = getMaxLength()-(int)s.getName().length();
        int pad2;
        if ((int)s.getName().length()%2 == 1) pad2 = pad1+1;
        else pad2 = pad1;
        cout << "|  " << s.getCode() << "  | ";
        for (int f = 0; f < pad1; f++) {
            cout << " ";
            ++f;
        }
         cout << s.getName();
        for (int e = 0; e < pad2; e++) {
            cout << " ";
            ++e;
        }
        cout << "|\n";
    }
    for (int i = 0; i < 36+getMaxLength(); i++) {
        if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
        cout << "-";
        if (i == 35+getMaxLength()) cout << "+\n";
    }
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

int GestaoH::getMaxLength() const {
    return maxLength_;
}

void GestaoH::setEstudantes(set<Student> estudantes) {
    estudantes_ = estudantes;
}

void GestaoH::setHorario(vector<TurmaH> horario) {
    horario_ = horario;
}

void GestaoH::setPedido(queue<Pedido> pedido) {
    pedido_ = pedido;
}

void GestaoH::setMaxLength(int maxLength) {
    maxLength_ = maxLength;
}

void GestaoH::addPedido(Pedido pedido){
    pedido_.push(pedido);
}
