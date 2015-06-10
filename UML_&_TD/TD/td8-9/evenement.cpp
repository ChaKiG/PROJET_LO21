#include "evenement.h"

using namespace TIME;
using namespace std;


std::ostream& operator<<(std::ostream& f, const Evt1j& evt){
	evt.afficher(f);
	return f;
}
std::ostream& operator<<(std::ostream& f, const Evt1jDur& evt){
	evt.afficher(f);
	return f;
}
std::ostream& operator<<(std::ostream& f, const Rdv& evt){
	evt.afficher(f);
	return f;
}

void TIME::Evt1j::afficher(std::ostream& f) const {
		f<<"***** Evt ********"<<"\n"<<"Date="<<date<<" sujet="<<sujet<<"\n";
}
Evt1j::~Evt1j() {cout<<"destruction Evt1j\n";};


void Evt1jDur::afficher(ostream & f) const
{ 
	//f<<"***** Evt ********"<<"\n"<<"Date="<<getDate()<<" sujet="<<getDescription()<<"\n";
	Evt1j::afficher(f);
	f<<"Horaire="<<horaire<<" duree="<<duree<<endl;
}

Evt1jDur::~Evt1jDur() {cout<<"destruction Evt1jDur\n";};

void Rdv::afficher(ostream & f) const{
	Evt1jDur::afficher(f);
	f<<" lieu : "<<lieu <<endl;
	f<<" personne : "<<personne<<endl;
}

Rdv::~Rdv() {
	cout<<"destruction Rdv\n";
}