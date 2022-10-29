#include "../include/ucturma.h"

UcTurma::UcTurma() {
    ucCode_ = "";
    classCode_ = "";
}

UcTurma::UcTurma(const string& ucCode, const string& classCode) {
    ucCode_ = ucCode;
    classCode_ = classCode;
}

string UcTurma::getUcCode() const {
    return ucCode_;
}

string UcTurma::getClassCode() const {
    return classCode_;
}

void UcTurma::setUcCode(const string& ucCode) {
    ucCode_ = ucCode;
}

void UcTurma::setClassCode(const string& classCode) {
    classCode_ = classCode;
}
