#ifndef TURMAH_H
#define TURMAH_H

#include <string>
#include <list>
#include "slot.h"

using namespace std;

class TurmaH {
    public:
        // constructor
        TurmaH(const string& codUc, const string& codTurma, list<Slot> horarioUcTurma);
        
        // accessors
        string getCodUc() const;
        string getCodTurma() const;
        list<Slot> getHorarioUcTurma() const;
        
    private:
        string codUc_;
        string codTurma_;
        list<Slot> horarioUcTurma_;
};

#endif
