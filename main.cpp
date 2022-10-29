#include <iostream>
#include "./include/student.h"
#include "./include/turmah.h"
#include "./include/pedido.h"
#include "./include/gestaoh.h"

int main(){
    GestaoH h;
    h.lerClasses();
    h.lerStudentClasses();
    h.drawEstudantes();
    return 0;
}
