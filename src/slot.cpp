#include "../include/slot.h"

Slot::Slot() {
    weekday_ = "";
    startHour_ = 0.0;
    finalHour_ = 0.0;
    type_ = "";
}
/**
 * Construtor que recebe a startHour e a duration de cada aula e soma os dois criando uma FinalHour.
 * @param weekday
 * @param startHour
 * @param duration
 * @param type
 */
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