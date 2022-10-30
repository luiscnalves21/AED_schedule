#ifndef SLOT_H
#define SLOT_H

#include <string>

using namespace std;

class Slot {
    public:
        // constructor
        Slot(); // default constructor
        Slot(const string& weekday, double startHour, double duration, const string& type);

        // accessors
        string getWeekday() const;
        double getStartHour() const;
        double getFinalHour() const;
        string getType() const;

    private:
        string weekday_;
        double startHour_;
        double finalHour_;
        string type_;
};

#endif
