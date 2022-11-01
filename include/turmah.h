#ifndef TURMAH_H
#define TURMAH_H

#include <string>
#include <list>
#include "slot.h"
#include "ucturma.h"

using namespace std;

class TurmaH : public UcTurma { // usa-se public UcTurma já que essa classe usa dois dos atributos desta
    public:
        // constructor
        TurmaH(const string& ucCode, const string& classCode, list<Slot> horarioUcClass);
        
        // accessors
        list<Slot> getHorarioUcClass() const;
        int getNumberOfStudents() const; // ver para que é que serve
    private:
        string ucCode_; // unidade curricular
        string classCode_; // turma
        list<Slot> horarioUcClass_; // horario uc turma
};

#endif
