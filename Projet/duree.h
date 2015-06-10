#ifndef DUREE_H
#define DUREE_H



/*
* \file Duree.h
* \brief Contient Classe permettant la gestion d'une duree
* \author Thomas Pelletier, Paul Buzaud, Amélie Thery
* \version 1
* \date 07/06/2015
*
*/


/*! \class Duree
* \brief Classe permettant la gestion d'une duree
*
*  La classe gere la lecture d'une liste de morceaux
*/
class Duree{
private:
	unsigned int nbMinutes;  /*!< Duree en minute */
public:
	/*!
	*  \brief Constructeur deux arguments : heure et minutes
	*  \param h nombre d'heures
	*  \param m nombre de minutes (fonctionne si m>60)
	*/
	Duree(unsigned int h, unsigned int m) :nbMinutes(h * 60 + m) {}


	/*!
	*  \brief surcharge Constructeur unargument : minutes
	*  \param m nombre de minutes (fonctionne si m>60)
	*/
	Duree(unsigned int m = 0) :nbMinutes(m) {}
	

	/*!
	*  \brief Constructeur de recopie
	*  \param other Duree a recopier
	*/
	Duree(const Duree & other) : nbMinutes(other.nbMinutes) {}
	
	
	/*!
	*  \brief modifier la duree
	*  \param heures nombre d'heures
	*  \param minutes nombre de minute (fonctionne si minutes>60)
	*/
	void setDuree(unsigned int heures, unsigned int minutes) { nbMinutes = heures * 60 + minutes; }


	/*!
	*  \brief surcharge pour modifier heure
	*  \param minutes duree totale en minute
	*/
	void setDuree(unsigned int minutes) { nbMinutes = minutes; }


	unsigned int getDureeEnMinutes() const { return nbMinutes; } //<!Retourne la duree en minutes>
	double getDureeEnHeures() const { return double(nbMinutes) / 60; } //<!Retourne la duree en heures>
    int getResteDureeEnMinutes() const {return nbMinutes%60;}  //<!Retourne la duree duree en minute de la derniere heure>

	Duree operator+(unsigned int min) const;
	Duree operator-(Duree const & other) const;
	Duree operator+=(Duree const & other);
	Duree operator-=(Duree const & other);
	bool operator==(Duree const& other) const;
	bool operator>=(Duree const& other) const;
	bool operator<=(Duree const& other) const;
	bool operator<(Duree const& other) const;
	bool operator>(Duree const& other) const;
};


#endif
