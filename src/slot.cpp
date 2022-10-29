#include "../include/slot.h"

Slot::Slot(const string& weekday, double startHour, double duration, const string& type) {
    weekday_ = weekday;
    startHour_ = startHour;
    finalHour_ = (startHour + duration);
    type_ = type;
}

string Slot::getWeekday() const {
    return weekday_;
}

double Slot::getStartHour() const {
    return startHour_;
}

double Slot::getFinalHour() const {
    return finalHour_;
}

string Slot::getType() const {
    return type_;
}