#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QDateTime>
#include "duree.h"
#include "evenement.h"
#include "exception.h"
#include "projet.h"

#include <exception>
#include <QMessageBox>

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLabel>
#include <QSpinBox>
#include <QSpinBox>
#include <QDate>
#include <QTime>



class Programmation{
	friend class ProgrammationManager;
private:
	static int currentId;
    int id;
	QDate dateChoisie;
	QTime horaireChoisi;
	Duree duree;
    Evenement * evt;

    Programmation(Evenement * event, const QDate & dateChoisie, const QTime& horaireChoisi, Duree dur = Duree(0));
	Programmation operator=(Programmation & other);
	Programmation(Programmation & other);

public:
	const QDate& getDateChoisie() const {return dateChoisie; }
	const QTime& getHoraireChoisi() const {return horaireChoisi; }
	const Duree& getDuree()const { return duree; }
	Duree& getDuree() { return duree; }

    void setDateChoisie(QDate d) { dateChoisie = d; }
    void setHoraireChoisi(QTime t) { horaireChoisi = t; }
    void setDuree(Duree d);

    int getId()const {return id;}
	Evenement * getEvent() { return evt; }
    const QTime getHoraireFin () const;

    ~Programmation() {}



	bool operator>(const Programmation & other) const;
	bool operator<(const Programmation & other) const;
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////               gere toutes les programmations                    /////////////////////////////
//////////         permet de regrouper toutes les programmations            /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class ProgrammationManager{
	friend class CreationProgrammationPreemptee;
private:
	std::vector<Programmation*> programmations;
	static ProgrammationManager * instance;


	ProgrammationManager(){}
    ~ProgrammationManager();
	Programmation* trouverProgrammation(int id) const;
	Programmation* trouverDerniereProgrammation(Evenement * evt) const;
	Programmation* createProgPreemptee(Evenement * event, QDate date, QTime horaire);
	void addItem(Programmation* t);


public:
    static ProgrammationManager& getInstance();
	static void libererInstance();
	bool creneaulibre(const QDate& da, const QTime& h, const Duree& du);

    void creerProgrammation(Evenement * event, QDate dateChoisie, QTime horaireChoisi, Duree d = 0);

	Programmation& getProgrammation(int id);
	Programmation& getDerniereProgrammation(Evenement * evt);

	
	const std::vector<Programmation*> & getProgrammations() const {return programmations; }
	std::vector<Programmation*> getSemaine(QDate & date) const;
	
	void supprimerProgrammation(const QString p);
	void supprimerProgrammation(int id);	
};

////////////////////////////////////////////////////////////////////////////////////////////////
///////////           lorsque l'on cree une programmation                    ///////////////////
///////////			 d'une tache preemptee on doit avoir la duree voulue     ///////////////////
///////////			  cette fenetre permet de l'avoir                        ///////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


class CreationProgrammationPreemptee : public QWidget {
	friend class ProgrammationManager;
	Q_OBJECT
private:
	QGridLayout *lay;
	QPushButton *valider;
	QLabel *text, *text1, *textR;
	QSpinBox *heure, *minute, *tempsR;
	Evenement * event;
	QDate _date;
    QTime _horaire;

    CreationProgrammationPreemptee(Evenement * e, QDate date, QTime horaire, Duree dur = 0, QWidget * parent = 0);
	~CreationProgrammationPreemptee();

	private slots :
	void save();
};



#endif
