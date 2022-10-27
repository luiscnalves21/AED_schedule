//
// Created by gonca on 26/10/2022.
//
#include "ucturma.h"

void UCTURMA::ucTurma(string codUC, string codTurma) {this->codUC = codUC, this->codTurma = codTurma;}

string UCTURMA::getCodTurma(){return this->codTurma;}

string UCTURMA::getCodUC(){return this->codUC;}