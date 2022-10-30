#include <iostream>
#include "./include/student.h"
#include "./include/turmah.h"
#include "./include/pedido.h"
#include "./include/gestaoh.h"

int main(){
    GestaoH h;
    h.lerClasses(); // lê o ficheiro classes.csv
    h.drawHorario(); // desenha o vector<TurmaH>
    //h.lerStudentClasses(); // lê o ficheiro StudentClasses.csv
    //h.drawEstudantes(); // desenha o set<Student>
    return 0;
}
