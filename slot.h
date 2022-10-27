//
// Created by gonca on 26/10/2022.
//

#ifndef PROJETO_AED_SLOT_H
#define PROJETO_AED_SLOT_H
#include<string>
using namespace std;

class slot {
    public:
        void Slot(int dia, double horainicio, double duration, string tipo); //Construtor
        int getDia();
        double getHorainicio();
        double getHorafim();
        string getTipo();
    private:
        int dia;
        double horainicio;
        double horafim;
        string tipo;
};

#endif //PROJETO_AED_SLOT_H
