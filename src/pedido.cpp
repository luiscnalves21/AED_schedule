#include "../include/pedido.h"

using namespace std;

Pedido::Pedido(int studentCode, const string& tipo, const string& codTurmaInicial,
               const string& codTurmaFinal, const string& codUc) {
    studentCode_ = studentCode;
    tipo_ = tipo;
    codTurmaInicial_ = codTurmaInicial;
    codTurmaFinal_ = codTurmaFinal;
    codUc_ = codUc;
}

int Pedido::getStudentCode() const {
    return studentCode_;
}

string Pedido::getTipo() const {
    return tipo_;
}

string Pedido::getCodTurmaInicial() const {
    return codTurmaInicial_;
}

string Pedido::getCodTurmaFinal() const {
    return codTurmaFinal_;
}

string Pedido::getCodUc() const {
    return codUc_;
}
