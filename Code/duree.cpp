#include "duree.h"

Duree Duree::operator-(Duree const & other) const{
	return Duree(nbMinutes - other.nbMinutes);
}

Duree Duree::operator+=(Duree const & other){
	nbMinutes += other.nbMinutes;
	return *this;
}

Duree Duree::operator-=(Duree const & other){
	nbMinutes -= other.nbMinutes;
	return *this;
}

Duree Duree::operator+(unsigned int min) const { 
	return Duree(nbMinutes + min);
}

bool Duree::operator==(Duree const& other) const { 
	return (nbMinutes == other.nbMinutes); 
}

bool Duree::operator<=(Duree const& other) const {
	return (nbMinutes <= other.nbMinutes);
}

bool Duree::operator>=(Duree const& other) const {
	return (nbMinutes >= other.nbMinutes);
}

bool Duree::operator<(Duree const& other) const {
	return (nbMinutes < other.nbMinutes);
}

bool Duree::operator>(Duree const& other) const {
	return (nbMinutes > other.nbMinutes);
}
