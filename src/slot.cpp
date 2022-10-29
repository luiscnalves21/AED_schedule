#include "../include/slot.h"

Slot::Slot(const string& dia, double horaInicio, double duration, const string& tipo) {
    dia_ = dia;
    horaInicio_ = horaInicio;
    horaFim_ = (horaInicio + duration);
    tipo_ = tipo;
}

string Slot::getDia() const {
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