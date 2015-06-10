#include "gestiontache.h"
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <stdio.h>




TacheEditeur::TacheEditeur(Tache * tacheToEdit, QWidget* parent){
    box = new QGridLayout(parent);
    setLayout(box);

    label_t = new QLabel("titre");
    titre = new QLineEdit(tacheToEdit->getTitre());
    box->addWidget(label_t, 1, 0);
    box->addWidget(titre, 1, 1, 1, 4);
    label_dispo = new QLabel("disponibilité");
    dispo = new QDateEdit(tacheToEdit->getDateDisponibilite());
    label_echeance = new QLabel("échéance");
    echeance = new QDateEdit(tacheToEdit->getDateEcheance());
    saveButton = new QPushButton("sauvegarder");
    annuler = new QPushButton("annuler");
    box->addWidget(label_dispo, 2, 0);
    box->addWidget(dispo, 2, 1);
    box->addWidget(annuler, 7, 0, 1, 3);
    box->addWidget(saveButton, 7, 4, 1, 4);


    prerequis = new QListWidget();
    labelPrerequis = new QLabel("Prérequis :");
    box->addWidget(labelPrerequis, 2, 3);
    box->addWidget(prerequis, 3, 3, 3, 1);
    std::vector<Tache*>::const_iterator ite = tacheToEdit->getPrerequis().begin();
    while (ite != tacheToEdit->getPrerequis().end()){
        QListWidgetItem * item = new QListWidgetItem((*ite)->getTitre());
        prerequis->addItem(item);
        ++ite;
    }


    if (dynamic_cast<TacheComposite*>(tacheToEdit)){
        label_sousTaches = new QLabel("Sous Taches :");
        sousTaches = new QListWidget();
        box->addWidget(label_sousTaches, 2, 2);
        box->addWidget(sousTaches, 3, 2, 1, 1);
        box->addWidget(label_echeance, 3, 0);
        box->addWidget(echeance, 3, 1);

        std::vector<Tache*>::const_iterator ite = ((TacheComposite*)tacheToEdit)->getSousTaches().begin();
        while (ite != ((TacheComposite*)tacheToEdit)->getSousTaches().end()){
            QListWidgetItem * item = new QListWidgetItem((*ite)->getTitre());
            sousTaches->addItem(item);
            ite++;
        }
    }

    else{					//si tache Unitaire
        pre = new QCheckBox();
        label_pre = new QLabel("preemptive");
        box->addWidget(pre, 0, 5);
        box->addWidget(label_pre, 0, 6);
        labelDureeInitiale = new QLabel("durée Initiale");
        heureDebut = new QSpinBox(this);
        minDebut = new QSpinBox(this);

        if (dynamic_cast<TacheUnitairePreemptee*>(tacheToEdit)){
            pre->setChecked(true);
            heureEffectue = new QSpinBox(this);
            minEffectue = new QSpinBox(this);
            labelDureeEffectue = new QLabel("durée Effectuée (si preemptive)");
            heureEffectue->setValue(((TacheUnitairePreemptee*)tacheToEdit)->getDureeEffectuee().getDureeEnHeures());
            heureEffectue->setSuffix(" heure(s)");
            minEffectue->setValue(((TacheUnitairePreemptee*)tacheToEdit)->getDureeEffectuee().getResteDureeEnMinutes());
            minEffectue->setSuffix(" minute(s)");
            minEffectue->setSingleStep(15);
            box->addWidget(heureEffectue, 5, 1);
            box->addWidget(minEffectue, 5, 2);
            box->addWidget(labelDureeEffectue, 5, 0);

        }
        else{
            pre->setChecked(false);
        }
        heureDebut->setValue(((TacheUnitaire*)tacheToEdit)->getDuree().getDureeEnHeures());
        heureDebut->setSuffix(" heure(s)");
        minDebut->setValue(((TacheUnitaire*)tacheToEdit)->getDuree().getResteDureeEnMinutes());
        minDebut->setSuffix(" minute(s)");
        minDebut->setSingleStep(15);

        box->addWidget(label_echeance, 3, 0);
        box->addWidget(echeance, 3, 1);
        box->addWidget(heureDebut, 4, 1);
        box->addWidget(minDebut, 4, 2);
        box->addWidget(labelDureeInitiale, 4, 0);
    }


    //QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    //QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));


}

/*
void TacheEditeur::save(){
Duree d(heure->value(),min->value());
if(id->text()==tache->getId()){
tache->setTitre(titre->toPlainText());
tache->setDatesDisponibiliteEcheance(dispo->date(),echeance->date());
tache->setDuree(d);
if(pre->isChecked())
tache->setPreemptive();
else
tache->setNonPreemptive();
}
}
*/




GestionTache::GestionTache(Projet &proj) : _proj(&proj){
	lay = new QVBoxLayout();
	Unitaire = new QRadioButton("Unitaire?");
	Preemptive = new QRadioButton("Preemptee?");
	Composite = new QRadioButton("Composite?");
	Sauvegarder = new QPushButton("Sauvegarder");
    Annuler = new QPushButton("Annuler");
	pre = std::vector<Tache*>();
    verif = 0;

	Prerequis1 = new QLabel("Taches prérequises:");
	Prerequis2 = new QLineEdit();

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
	lay->addWidget(Prerequis1);
	lay->addWidget(Prerequis2);
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
    pre = std::vector<Tache*>();
    verif = 0;

	Prerequis1 = new QLabel("Taches prérequises:");
	Prerequis2 = new QLineEdit();

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
	lay->addWidget(Prerequis1);
	lay->addWidget(Prerequis2);
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
	{
        _proj->creerTache("TacheComposite", Titre2->text(), Dispo2->date(), Ech2->date());
	}

	if (Preemptive->isChecked()) //creation d'une tache preemptive si preemptive est cochée
	{
        _proj->creerTache("TacheUnitairePreemptee", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), NULL, Duree(Duree2->value(), Duree4->value()));
	}

	else // creation d'une tache unitaire si unitaire est cochée ou si rien n'est coché
	{
        _proj->creerTache("TacheUnitaire", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), NULL, Duree(Duree2->value(), Duree4->value()));
	}

	/* /////////////////Ne fonctionne pas////////////////////////////////////*/
/*	if (Prerequis2->text().toStdString() != ""){ //ajout des prerequis si il y en a
		/* const char* prerequis=Prerequis2->text().toStdString().c_str();
		char tache[20];
		char lettre =prerequis[0];
		int i=0,j=0;
		while (i<100){
		if (lettre != ' '||lettre != '\n'){
		tache[j]=lettre;
		lettre=prerequis[++i];
		j++;}
		else{ QString tache2(*tache);
		t->ajoutPrerequi(&(projM.getProjet(Projet2->text()).getTache(tache2)));
		j=0;}
		}*/
     //   t->ajoutPrerequi(&(projM.getProjet(Projet2->text()).getTache(Prerequis2->text())));//fonctionne pour 1 seul prerequis
    //}
	/* ////////////////////////////////////////////////////////////////////////*/

    close();

}









void GestionSousTache::creertache(){ //lorsque le bouton sauvegarder est cliqué
    if (dynamic_cast<TacheComposite*>(&_tache))
	{
		if (Composite->isChecked()) //creation d'une tache composite si composite est cochée
		{
            _proj.creerTache("TacheComposite", Titre2->text(), Dispo2->date(), Ech2->date(),  std::vector<Tache*>(), &_tache);
		}

		if (Preemptive->isChecked()) //creation d'une tache preemptive si preemptive est cochée
		{
            _proj.creerTache("TacheUnitairePreemptee", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), &_tache, Duree(Duree2->value(), Duree4->value()));
		}
		else // creation d'une tache unitaire si unitaire est cochée ou si rien n'est coché
        {
            _proj.creerTache("TacheUnitaire", Titre2->text(), Dispo2->date(), Ech2->date(), std::vector<Tache*>(), &_tache, Duree(Duree2->value(), Duree4->value()));
		}


		/* /////////////////Ne fonctionne pas////////////////////////////////////*/
        if (Prerequis2->text().toStdString() != ""){ //ajout des prerequis si il y en a
			/*  const char* prerequis=Prerequis2->text().toStdString().c_str();
			char tache[20];
			char lettre =prerequis[0];
			int i=0,j=0;
			while (i<100){
			if (lettre != ' '||lettre != '\n'){
			tache[j]=lettre;
			lettre=prerequis[++i];
			j++;}
			else{ QString tache2(*tache);
			t->ajoutPrerequi(&(projM.getProjet(Projet2->text()).getTache(tache2)));
			j=0;}
			}*/
            //t->ajoutPrerequi(&(projM.getProjet(Projet2->text()).getTache(Prerequis2->text())));//fonctionne pour 1 seul prerequis
		}
		/* ////////////////////////////////////////////////////////////////////////*/

    }
	//else   throw CalendarException("Impossible d'ajouter une sous tache à une tache non composite");
    close();
}




GestionTache::~GestionTache(){
	delete lay;
}




GestionSousTache::~GestionSousTache(){
	delete lay;
}

