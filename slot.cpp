#include "slot.h"

using namespace std;

Slot::Slot(int dia, double horainicio, double duration, const string& tipo) {
    dia_ = dia;
    horaInicio_ = horainicio;
    horaFim_ = (horainicio + duration);
    tipo_ = tipo;
}

int Slot::getDia() const {
    return dia_;
}

double Slot::getHoraInicio() const {
    return horaInicio_;
}

double Slot::getHoraFim() const {
    return horaFim_;
}

string Slot::getTipo() const {
    return tipo_;
}