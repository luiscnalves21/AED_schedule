#include <iostream>
#include "./include/student.h"
#include "./include/ucturma.h"
#include "./include/turmah.h"
#include "./include/pedido.h"
#include "./include/slot.h"
#include "./include/gestaoh.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void lerClasses(){
    string line, temp, word;
    string classCode, ucCode, weekday, sstartHour, sduration, type;
    string ficheiro = "classes.csv";
    ifstream ifs;
    vector<Slot> horario;
    ifs.open(ficheiro, ios::in);
    getline(ifs, temp);
    while(getline(ifs, line)){
        stringstream s(line);
        getline(s, classCode, ','), getline(s, ucCode, ','), getline(s, weekday, ','), getline(s, sstartHour, ','), getline(s, sduration, ','), getline(s, type, '\r');
        double startHour = stod(sstartHour), duration = stod(sduration);
        Slot aux = Slot(weekday, startHour, duration, type);
        horario.push_back(aux);
        TurmaH F = TurmaH(classCode, ucCode, horario);
    }
}

void lerStudentClasses() {
    string line, temp, word;
        string ficheiro = "classes.csv";
    ifstream ifs;
    vector<Slot> horario;
    ifs.open(ficheiro, ios::in); // abre ficheiro
    getline(ifs, temp); // passa a primeira linha à frente
    while(getline(ifs, line)){
        stringstream s(line);
        while (getline(s, classCode, ',') && getline(s, ucCode, ',')) {

        }
    }
}

int main(){
    GestaoH h;
    lerClasses();
    return 0;
}
