
// Created by gonca on 26/10/2022.

#include "student.h"

void Student::student(int number, std::string name, list<UCTURMA> turmas) {this->number = number, this->name = name, this->turmas = turmas;}

std::string Student::getName() {return this->name;}

int Student::getNumber() {return this->number;}

list<UCTURMA> Student::getTurmas() {return this->turmas;}