//
// Created by gonca on 26/10/2022.
//

#include "turmah.h"

void turmaH::TurmaH(std::string codUC, std::string codTurma, list<slot> horarioUCturma) {this->codUC = codUC, this->codTurma = codTurma, this->horarioUCturma = horarioUCturma;}

string turmaH::getCodTurma() {return this->codTurma;}

string turmaH::getCodUC() {return this->codUC;}

list<slot> turmaH::getHorarioUCTurma() {return this->horarioUCturma;}