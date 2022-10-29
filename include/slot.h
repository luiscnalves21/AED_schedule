#ifndef SLOT_H
#define SLOT_H

#include <string>

using namespace std;

class Slot {
    public:
        // constructor
        Slot(const string& dia, double horaInicio, double duration, const string& tipo);

        // accessors
        string getDia() const;
        double getHoraInicio() const;
        double getHoraFim() const;
        string getTipo() const;

    private:
        string dia_;
        double horaInicio_;
        double horaFim_;
        string tipo_;
};

#endif
