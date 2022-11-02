#include <utility>

#include "../include/turmah.h"

TurmaH::TurmaH() : UcTurma() {
    horarioUcClass_ = {};
}

TurmaH::TurmaH(const string& ucCode, const string& classCode, list<Slot> horarioUcClass) : UcTurma(ucCode, classCode) {
    // usando a classe UcTurma só é necessário fazer a atribuição de valores ao atributo horarioUcClass_
    horarioUcClass_ = std::move(horarioUcClass);
}

list<Slot> TurmaH::getHorarioUcClass() const {
    return horarioUcClass_;
}