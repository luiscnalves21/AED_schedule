//
// Created by gonca on 26/10/2022.
//

#ifndef PROJETO_AED_STUDENT_H
#define PROJETO_AED_STUDENT_H
#include<list>
#include<string>
#include "ucturma.h"
using namespace std;
class Student{
    public:
        void student(int number, string name, list<UCTURMA> turmas); // Construtor
        string getName();
        int getNumber();
        list<UCTURMA> getTurmas();

    private:
        int number;
        string name;
        list<UCTURMA> turmas;
};
#endif