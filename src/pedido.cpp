#include <utility>

#include "../include/pedido.h"

using namespace std;

Pedido::Pedido() {
    studentCode_ = 0;
    type_ = "";
    initialClassCode_ = "";
    finalClassCode_ = "";
    ucCode_ = "";
}

Pedido::Pedido(int studentCode, const string& type, const string& initialClassCode, const string& finalClassCode, const string& ucCode) {
    // é preciso verificar qual o tipo de pedido
    studentCode_ = studentCode;
    type_ = type;
    ucCode_= ucCode;
    if (type == "A") {
        initialClassCode_ = "";
        finalClassCode_ = finalClassCode;
    }
    if (type == "R") {
        initialClassCode_ = initialClassCode;
        finalClassCode_ = "";
    }
    if (type == "T" || type == "CT") {
        initialClassCode_ = initialClassCode;
        finalClassCode_ = finalClassCode;
    }
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

void Pedido::setStudentCode(int studentCode) {
    studentCode_ = studentCode;
}

void Pedido::setType(string type) {
    type_ = std::move(type);
}

void Pedido::setInitialClassCode(string initialClassCode) {
    initialClassCode_ = std::move(initialClassCode);
}

void Pedido::setfinalClassCode(string finalClassCode) {
    finalClassCode_ = std::move(finalClassCode);
}

void Pedido::setUcCode(string ucCode) {
    ucCode_ = std::move(ucCode);
}
