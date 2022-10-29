#ifndef SLOT_H
#define SLOT_H

#include <string>

using namespace std;

class Slot {
    public:
        // constructor
        Slot(int dia, double horainicio, double duration, const string& tipo);

        // accessors
        int getDia() const;
        double getHoraInicio() const;
        double getHoraFim() const;
        string getTipo() const;

    private:
        int dia_;
        double horaInicio_;
        double horaFim_;
        string tipo_;
};

#endif
