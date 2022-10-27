#include "slot.h"

void slot::Slot(int dia, double horainicio, double duration, std::string tipo) {this->dia = dia, this->horainicio = horainicio, this->horafim = (horainicio + duration), this->tipo = tipo;}

int slot::getDia() {return this->dia;}

double slot::getHorafim() {return this->horafim;}

double slot::getHorainicio() {return this->horainicio;}

string slot::getTipo() {return this->tipo;}