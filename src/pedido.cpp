#include "../include/pedido.h"

using namespace std;

Pedido::Pedido(int studentCode, const string& type, const string& initialClassCode, const string& finalClassCode, const string& ucCode) {
    studentCode_ = studentCode;
    type_ = type;
    initialClassCode_ = initialClassCode;
    finalClassCode_ = finalClassCode;
    ucCode_= ucCode;
}

int Pedido::getStudentCode() const {
    return studentCode_;
}

string Pedido::getType() const {
    return type_;
}

string Pedido::getInitialClassCode() const {
    return initialClassCode_;
}

string Pedido::getFinalClassCode() const {
    return finalClassCode_;
}

string Pedido::getUcCode() const {
    return ucCode_;
}
