#if !defined(_EVENEMENT_H)
#define _EVENEMENT_H
#include <iostream>
#include <string>
#include "timing.h"
namespace TIME{
	class Evt1j {
	private:
		Date date;
		std::string sujet;
	public:
		Evt1j(const Date& d, const std::string& s):date(d),sujet(s){std::cout<<"construction Evt1j\n";}
		const std::string& getDescription() const { return sujet; }
		const Date& getDate() const { return date; }
		virtual void afficher(std::ostream& f= std::cout) const;
		virtual ~Evt1j();


	};

	class Evt1jDur : public Evt1j { // on indique pour Evt1jDur herite de evt(1j => un iobjet Evt1jDur a une partie Evt1jDur (une date et une description
	private :
		Horaire horaire;
		Duree duree;

	public :
		Evt1jDur(const Date & d, const std::string & s, const Horaire & h, const Duree & dur): Evt1j(d,s),horaire(h),duree(dur){std::cout<<"construction Evt1jDur\n";};
		const Horaire getHoraire() const {return horaire;};
		const Duree getDuree() const {return duree;};
		virtual void afficher(std::ostream & f= std::cout) const;
		virtual ~Evt1jDur();

	};

	class Rdv : public Evt1jDur{
	private:
		std::string lieu;
		std::string personne;
	public:
		Rdv(const Date & d, const std::string & s, const Horaire & h, const Duree & dur, const std::string l, const std::string& per): Evt1jDur(d,s,h,dur),lieu(l),personne(per){std::cout<<"construction Rdv\n";};
		//Rdv(const Rdv & other):Evt1jDur(other.getDate(),other.getDescription(),other.getHoraire(),other.getDuree()), lieu(other.lieu),personne(other.personne) {};
		Rdv(const Rdv& other): Evt1jDur(other),lieu(other.lieu),personne(other.personne) {};
		const std::string & getLieu() const {return lieu;};
		const std::string & getPersonne()const {return personne;};
		virtual void afficher(std::ostream & f= std::cout) const;
		virtual ~Rdv();
		const Rdv & operator=(const Rdv& other){
			Evt1jDur::operator=(other); //Evt1jDur & ref=*this, ref=other;
			personne=other.personne;
			lieu=other.lieu;
			return *this;
		}

	};
}


std::ostream& operator<<(std::ostream&, const TIME::Evt1j&);
std::ostream& operator<<(std::ostream&, const TIME::Evt1jDur&);
std::ostream& operator<<(std::ostream&, const TIME::Rdv& );


/* il n'est pas jnecessaire de declarer date et sujet en protected On peut utiliser les accesseurs publics !
le mot clé protected peut etre vu comme une entorse au princuipe d'encapsulation
- on peut redefinir afficher() meme si cette methode n'est pas virtual. Le choix de la methode à appeler se fera
a la compilation en fonction du type de la variable sur laquelle on fait l'appel
Evt1jDur evt("...")
evt.afficher(cout)->Evt1jDurafficher
evt1j bref=evt
refafficher(cout)->evt1j::afficher

on ne respecte le principe de substitution (un evtjdur ne peut pas prndre la placed'un evtijdfur en toute cironstance)à*/


//	operateur d'affactation et constructeur de recopie créés automatiquement

#endif