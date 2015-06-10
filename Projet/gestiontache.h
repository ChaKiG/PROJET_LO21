#ifndef GESTIONTACHE_H
#define GESTIONTACHE_H


#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QListWidget>

#include "tache_editeur.h"
#include "projet.h"
#include "programmation.h"
#include "fenetres_gestion_projets.h"



class GestionTache : public QWidget{
	Q_OBJECT

    Projet *_proj;
    QVBoxLayout *lay;
    QRadioButton *Preemptive, *Composite, *Unitaire;
    QTreeWidgetItem *p;
    QLabel *Duree1, *Duree3, *Ech1, *Dispo1, *Projet1, *Prerequis1, *Titre1;
    QSpinBox *Duree2, *Duree4;
    QDateEdit *Ech2, *Dispo2;
    std::vector<Tache*> pre;
    QLineEdit *Projet2, *Titre2, *Prerequis2;
    TacheEditeur *editeur;
    QPushButton *Sauvegarder, *Annuler;
	int verif;
    Tache *t;
public:
    GestionTache(Projet & proj);
	~GestionTache();
	public slots:
	void creertache();
	void afficherpreemptive();
	void affichercomposite();
};

class GestionSousTache : public QWidget{
	Q_OBJECT

	Projet &_proj;
	Tache &_tache;
	QVBoxLayout * lay;
	QRadioButton* Preemptive, *Composite, *Unitaire;
	Tache *t;
	QTreeWidgetItem * p, *tachecomp;
	QLabel * Duree1, *Duree3, *Ech1, *Dispo1, *Projet1, *Parent1, *Titre1, *Prerequis1;
	QSpinBox* Duree2, *Duree4;
	QDateEdit* Ech2, *Dispo2;
	std::vector<Tache*> pre;
	QLineEdit * Projet2, *Parent2, *Titre2, *Prerequis2;
	TacheEditeur* editeur;
	QPushButton* Sauvegarder, *Annuler;
	Tache* par;
	int verif;
public:
	GestionSousTache(Projet & proj, Tache & tache);
	~GestionSousTache();
	public slots:
	void creertache();
	void afficherpreemptive();
	void affichercomposite();
};

#endif


