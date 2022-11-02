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
    if(type == "A"){
        initialClassCode_ = "";
        finalClassCode_ = finalClassCode;
    }
    if(type == "R"){
        initialClassCode_ = initialClassCode;
        finalClassCode_ = "";
    }
    if(type == "T"){
        initialClassCode_ = initialClassCode;
        finalClassCode_ = finalClassCode;
    }
    //if(type == "CT"){}
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
