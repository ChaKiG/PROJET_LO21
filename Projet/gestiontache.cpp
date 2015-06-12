#include "gestiontache.h"
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <stdio.h>





GestionTache::GestionTache(Projet &proj) : _proj(&proj){
	lay = new QVBoxLayout();
	Unitaire = new QRadioButton("Unitaire?");
	Preemptive = new QRadioButton("Preemptee?");
	Composite = new QRadioButton("Composite?");
	Sauvegarder = new QPushButton("Sauvegarder");
    Annuler = new QPushButton("Annuler");
    verif = 0;


	Duree1 = new QLabel("Duree heure:");
	Duree2 = new QSpinBox(0);
	Duree3 = new QLabel("Duree minute:");
	Duree4 = new QSpinBox(0);

	Titre1 = new QLabel("Titre de la tache:");
	Titre2 = new QLineEdit("");

	Projet1 = new QLabel("Inclue dans le projet:");
    Projet2 = new QLineEdit(_proj->getTitre());
    Projet2->setReadOnly(true);

	Dispo1 = new QLabel("A partir de:");
	Dispo2 = new QDateEdit(QDate::currentDate());

	Ech1 = new QLabel("A faire avant le:");
	Ech2 = new QDateEdit(QDate::currentDate());

	setLayout(lay);

	lay->addWidget(Titre1);
	lay->addWidget(Titre2);
	lay->addWidget(Projet1);
	lay->addWidget(Projet2);
	lay->addWidget(Dispo1);
	lay->addWidget(Dispo2);
	lay->addWidget(Ech1);
	lay->addWidget(Ech2);
	lay->addWidget(Unitaire);
	lay->addWidget(Preemptive);
	lay->addWidget(Composite);
	lay->addWidget(Sauvegarder);
	lay->addWidget(Annuler);

	QObject::connect(Unitaire, SIGNAL(clicked()), this, SLOT(afficherpreemptive()));
	QObject::connect(Preemptive, SIGNAL(clicked()), this, SLOT(afficherpreemptive()));
	QObject::connect(Composite, SIGNAL(clicked()), this, SLOT(affichercomposite()));
	QObject::connect(Sauvegarder, SIGNAL(clicked()), this, SLOT(creertache()));
	QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(close()));

	show();

}

GestionSousTache::GestionSousTache(Projet &proj, Tache &tache) : _proj(proj), _tache(tache){
	lay = new QVBoxLayout();
	Unitaire = new QRadioButton("Unitaire?");
	Preemptive = new QRadioButton("Preemptee?");
	Composite = new QRadioButton("Composite?");
	Sauvegarder = new QPushButton("Sauvegarder");
    Annuler = new QPushButton("Annuler");
    verif = 0;


	Duree1 = new QLabel("Duree heure:");
	Duree2 = new QSpinBox(0);
	Duree3 = new QLabel("Duree minute:");
	Duree4 = new QSpinBox(0);

	Titre1 = new QLabel("Titre de la tache:");
    Titre2 = new QLineEdit("");

	Parent1 = new QLabel("Sous-tache de: (attention cette tache doit être composite)");
    Parent2 = new QLineEdit(_tache.getTitre());

	Dispo1 = new QLabel("A partir de:");
    Dispo2 = new QDateEdit(_tache.getDateDisponibilite());

	Ech1 = new QLabel("A faire avant le:");
    Ech2 = new QDateEdit(_tache.getDateEcheance());

	setLayout(lay);

	lay->addWidget(Titre1);
    lay->addWidget(Titre2);
    lay->addWidget(Dispo1);
    lay->addWidget(Dispo2);
	lay->addWidget(Ech1);
	lay->addWidget(Ech2);
	lay->addWidget(Unitaire);
	lay->addWidget(Preemptive);
	lay->addWidget(Composite);
	lay->addWidget(Sauvegarder);
	lay->addWidget(Annuler);

	QObject::connect(Unitaire, SIGNAL(clicked()), this, SLOT(afficherpreemptive()));
	QObject::connect(Preemptive, SIGNAL(clicked()), this, SLOT(afficherpreemptive()));
	QObject::connect(Composite, SIGNAL(clicked()), this, SLOT(affichercomposite()));
	QObject::connect(Sauvegarder, SIGNAL(clicked()), this, SLOT(creertache()));
	QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(close()));

	show();

}

void GestionTache::affichercomposite(){ //si composite est cochée, et que preemptive était cochée avant on enlève les durees
	if (verif == 1){
		lay->removeWidget(Sauvegarder);
		lay->removeWidget(Annuler);
		Duree1->close();
		lay->removeWidget(Duree1);
		Duree2->close();
		lay->removeWidget(Duree2);
		Duree3->close();
		lay->removeWidget(Duree3);
		Duree4->close();
		lay->removeWidget(Duree4);
		verif = 0;
		lay->addWidget(Sauvegarder);
		lay->addWidget(Annuler);
		lay->update();
	}


}

void GestionSousTache::affichercomposite(){ //si composite est cochée, et que preemptive était cochée avant on enlève les durees
	if (verif == 1){
		lay->removeWidget(Sauvegarder);
		lay->removeWidget(Annuler);
		Duree1->close();
		lay->removeWidget(Duree1);
		Duree2->close();
		lay->removeWidget(Duree2);
		Duree3->close();
		lay->removeWidget(Duree3);
		Duree4->close();
		lay->removeWidget(Duree4);
		verif = 0;
		lay->addWidget(Sauvegarder);
		lay->addWidget(Annuler);
		lay->update();
	}

}

void GestionTache::afficherpreemptive(){ // ajout des durées pour unitaire et préemptive
	lay->removeWidget(Sauvegarder);
	lay->removeWidget(Annuler);
	lay->addWidget(Duree1);
	Duree1->show();
	lay->addWidget(Duree2);
	Duree2->show();
	lay->addWidget(Duree3);
	Duree3->show();
	lay->addWidget(Duree4);
	Duree4->show();
	lay->addWidget(Sauvegarder);
	lay->addWidget(Annuler);
	verif = 1;

}

void GestionSousTache::afficherpreemptive(){ // ajout des durées pour unitaire et préemptive
	lay->removeWidget(Sauvegarder);
	lay->removeWidget(Annuler);
	lay->addWidget(Duree1);
	Duree1->show();
	lay->addWidget(Duree2);
	Duree2->show();
	lay->addWidget(Duree3);
	Duree3->show();
	lay->addWidget(Duree4);
	Duree4->show();
	lay->addWidget(Sauvegarder);
	lay->addWidget(Annuler);
	verif = 1;

}


void GestionTache::creertache(){ //lorsque le bouton sauvegarder est cliqué
	if (Composite->isChecked()) //creation d'une tache composite si composite est cochée
		_proj->creerTache("TacheComposite", Titre2->text(), Dispo2->date(), Ech2->date());
    else if (Preemptive->isChecked()) //creation d'une tache preemptive si preemptive est cochée
        _proj->creerTache("TacheUnitairePreemptee", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), NULL, Duree(Duree2->value(), Duree4->value()));
	else // creation d'une tache unitaire si unitaire est cochée ou si rien n'est coché
        _proj->creerTache("TacheUnitaire", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), NULL, Duree(Duree2->value(), Duree4->value()));
	new GestionProj();
    close();
}




void GestionSousTache::creertache(){ //lorsque le bouton sauvegarder est cliqué
    if (dynamic_cast<TacheComposite*>(&_tache))
	{
		if (Composite->isChecked()) //creation d'une tache composite si composite est cochée
            _proj.creerTache("TacheComposite", Titre2->text(), Dispo2->date(), Ech2->date(),  std::vector<Tache*>(), &_tache);
		if (Preemptive->isChecked()) //creation d'une tache preemptive si preemptive est cochée
            _proj.creerTache("TacheUnitairePreemptee", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), &_tache, Duree(Duree2->value(), Duree4->value()));
		else // creation d'une tache unitaire si unitaire est cochée ou si rien n'est coché
            _proj.creerTache("TacheUnitaire", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), &_tache, Duree(Duree2->value(), Duree4->value()));
        close();
    }else{
        throw CalendarException("impossible d'ajouter une sous tache a une tache non composite");
        close();
    }
}



GestionTache::~GestionTache(){
    delete lay;
    delete Preemptive;
    delete Composite;
    delete Unitaire;
    delete Duree1;
    delete Duree3;
    delete Ech1;
    delete Dispo1;
    delete Projet1;
    delete Titre1;
    delete Duree2;
    delete Duree4;
    delete Ech2;
    delete Dispo2;
    delete Projet2;
    delete Titre2;
    delete Sauvegarder;
    delete Annuler;
}




GestionSousTache::~GestionSousTache(){
    delete lay;
    delete Preemptive;
    delete Composite;
    delete Unitaire;
    delete Duree1;
    delete Duree3;
    delete Ech1;
    delete Dispo1;
    delete Projet1;
    delete Titre1;
    delete Duree2;
    delete Duree4;
    delete Ech2;
    delete Dispo2;
    delete Projet2;
    delete Titre2;
    delete Sauvegarder;
    delete Annuler;
}

