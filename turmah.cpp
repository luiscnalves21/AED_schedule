#include "turmah.h"

using namespace std;

TurmaH::TurmaH(const string& codUc, const string& codTurma, list<Slot> horarioUcTurma) {
    codUc_ = codUc;
    codTurma_ = codTurma;
    horarioUcTurma_ = horarioUcTurma;
}

string TurmaH::getCodUc() const {
    return codUc_;
}

string TurmaH::getCodTurma() const {
    return codTurma_;
}

list<Slot> TurmaH::getHorarioUcTurma() const {
    return horarioUcTurma_;
}