#include "Distance.h"

Distance::Distance() {
    _feet = 0;
    _inches = 0;
}

Distance::Distance(unsigned ft, double in) {
    _feet = ft;
    _inches = in;

    if (_inches < 0) {
        _inches *= -1;
    }

    while (_inches >= 12) {
        _inches -= 12;
        _feet++;
    }
}

Distance::Distance(double in) {
    _feet = 0;
    _inches = in;

    if (_inches < 0) {
        _inches *= -1;
    }

    while (_inches >= 12) {
        _inches -= 12;
        _feet++;
    }
}

unsigned Distance::getFeet() const {
    return _feet;
}

double Distance::getInches() const {
    return _inches;
}

double Distance::distanceInInches() const {
    return _feet * 12 + _inches;
}
 
double Distance::distanceInFeet() const {
    return _feet + _inches / 12;
}

double Distance::distanceInMeters() const {
    return (_feet * 12.0 + _inches) * 0.0254; //converted to inches then meters
}

Distance Distance::operator+(const Distance &rhs) const {
    return Distance(_feet + rhs._feet, _inches + rhs._inches);
}

Distance Distance::operator-(const Distance &rhs) const {
    int ft = rhs._feet - _feet; //yes, this is not an unsigned, but it was a headache working with unsigned
    double in = rhs._inches - _inches; // had to move rhs to the left because it works for some reason

    while (in < 0) {
        ft--;
        in += 12;
    }

    while (ft < 0) {
        ft++;
        in -= 12;
    }

    return Distance(ft, in);
}

ostream& operator<<(ostream &out, const Distance &rhs) {
    return out << rhs.getFeet() << "\' " << rhs.getInches() << "\"";
}

  