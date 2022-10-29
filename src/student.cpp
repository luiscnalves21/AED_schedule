#include "../include/student.h"

Student::Student(int code, const string& name, list<UcTurma>& turmas) {
    code_ = code;
    name_ = name;
    turmas_ = turmas;
    }

string Student::getName() const {
    return name_;
}

int Student::getCode() const {
    return code_;
}

list<UcTurma> Student::getTurmas() const {
    return turmas_;
}
