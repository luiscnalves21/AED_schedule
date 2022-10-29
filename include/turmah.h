#ifndef TURMAH_H
#define TURMAH_H

#include <string>
#include <list>
#include "slot.h"
#include "ucturma.h"

using namespace std;

class TurmaH : public UcTurma {
    public:
        // constructor
        TurmaH(const string& ucCode, const string& classCode, list<Slot> horarioUcClass);
        
        // accessors
        list<Slot> getHorarioUcClass() const;
        
    private:
        string ucCode_; // unidade curricular
        string classCode_; // turma
        list<Slot> horarioUcClass_; // horario uc turma
};

#endif
