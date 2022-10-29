#include "../include/pedido.h"

using namespace std;

Pedido::Pedido(const string &tipo, int turma, const string &uc) {
    tipo_ = tipo;
    turma_ = turma;
    uc_ = uc;
}

string Pedido::getTipo() const {
    return tipo_;
}

int Pedido::getTurma() const {
    return turma_;
}

string Pedido::getUc() const {
    return uc_;
}
