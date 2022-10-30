#include "../include/gestaoh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

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
    string line1, line2, temp, word;
    string classCode1, classCode2, ucCode1, ucCode2, weekday, sstartHour, sduration, type, tempClassCode, tempUcCode;
    double startHour, duration;
    Slot aux;
    vector<TurmaH> horario; //criar vector de Turma/Uc de slots
    string ficheiro = "../schedule/classes.csv";
    ifstream ifs1, ifs2;
    list<Slot> slot; // criar lista de slots
    ifs1.open(ficheiro, ios::in);
    getline(ifs1, temp);
    while(getline(ifs1, line1)) {
        stringstream s1(line1);
        getline(s1, classCode1, ','), getline(s1, ucCode1, ','), getline(s1, weekday, ','), getline(s1, sstartHour, ','), getline(s1, sduration, ','), getline(s1, type, '\r');
        startHour = stod(sstartHour), duration = stod(sduration); // converter para double a hora inicial e a duração
        aux = Slot(weekday, startHour, duration, type); // cria slot
        slot.push_back(aux); // adiciona slot ao slot
        ifs2.open(ficheiro, ios::in);
        getline(ifs2, temp);
        while (getline(ifs2, line2)) {
            stringstream s2(line2);
            getline(s2, classCode2, ','), getline(s2, ucCode2, ','), getline(s2, weekday, ','), getline(s2, sstartHour, ','), getline(s2, sduration, ','), getline(s2, type, '\r');
            if (line1 != line2 && classCode1 == classCode2 && ucCode1 == ucCode2) {
                startHour = stod(sstartHour), duration = stod(sduration); // converter para double a hora inicial e a duração
                aux = Slot(weekday, startHour, duration, type); // cria slot
                slot.push_back(aux); // adiciona slot ao slot
            }
        }
        ifs2.close();
        TurmaH turmaH(ucCode1, classCode1, slot);
        horario.push_back(turmaH);
        slot = {}; // esvaziar a lista de slots
    }
    setHorario(horario);
}

void GestaoH::lerStudentClasses() {
    string line, temp, word, sstudentCode, studentName, ucCode, classCode, tempStudentName; // tempStudentName para guardar o nome estudante anterior
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

// função auxiliar para desenhar
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

void GestaoH::drawEstudantes() const {
    set<Student> estudantes = getEstudantes();
    cout << "+-------------+---------------------------+----------+-----------+\n"
            "| StudentCode |        StudentName        |  UcCode  | ClassCode |\n";
    for (const Student& s : estudantes) {
        for (int i = 0; i < 36+getMaxLength(); i++) {
            if (i == 0 || i == 13 || i == 40 || i == 50) cout << "+";
            cout << "-";
            if (i == 35+getMaxLength()) cout << "+\n";
        }
        cout << "|  " << s.getCode() << "  | ";
        pair<int, int> pad = auxCenterDraw(getMaxLength()-(int)s.getName().length(), (int)s.getName().length()%2 == 1);
        for (int f = 0; f < pad.first; f++) {
            cout << " ";
            ++f;
        }
         cout << s.getName();
        for (int e = 0; e < pad.second; e++) {
            cout << " ";
            ++e;
        }
        int c = 0;
        list<UcTurma> classUc = s.getTurmas();
        for (const UcTurma& u : classUc) {
            if (c > 0) {
                cout << "|             |                           ";
            }
            cout << "| " << u.getUcCode() << " |  " << u.getClassCode() << "  |\n";
            c++;
        }
    }
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
