#include <utility>

#include "../include/student.h"

Student::Student() {
    code_ = 0;
    name_ = "";
    turmas_ = list<UcTurma> {};
}

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

void Student::setTurmas(list<UcTurma> turmas) {
    turmas_ = std::move(turmas);
}
