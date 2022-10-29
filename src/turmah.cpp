#include "../include/turmah.h"

TurmaH::TurmaH(const string& ucCode, const string& classCode, list<Slot> horarioUcClass) : UcTurma(ucCode, classCode) {
    horarioUcClass_ = horarioUcClass;
}

list<Slot> TurmaH::getHorarioUcClass() const {
    return horarioUcClass_;
}