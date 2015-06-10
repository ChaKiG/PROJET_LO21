#include "tache_editeur.h"




TacheEditeur::TacheEditeur(Tache * tacheToEdit, QWidget* parent) : _tache(tacheToEdit){
	box = new QGridLayout(parent);
	setLayout(box);

	label_t = new QLabel("titre");
    titre = new QLineEdit(_tache->getTitre());
	box->addWidget(label_t, 1, 0);
	box->addWidget(titre, 1, 1, 1, 4);
	label_dispo = new QLabel("disponibilité");
    dispo = new QDateEdit(_tache->getDateDisponibilite());
	label_echeance = new QLabel("échéance");
    echeance = new QDateEdit(_tache->getDateEcheance());
    saveButton = new QPushButton("sauvegarder");
    ajoutPre = new QPushButton("ajout Prerequis");
    suppPre = new QPushButton("supprimmer prerequis");
	box->addWidget(label_dispo, 2, 0);
    box->addWidget(dispo, 2, 1);
    box->addWidget(saveButton,7,2,1,4);


	prerequis = new QListWidget();
	labelPrerequis = new QLabel("Prérequis :");
	box->addWidget(labelPrerequis, 2, 3);
	box->addWidget(prerequis, 3, 3, 3, 1);
    box->addWidget(ajoutPre,3,4);
    box->addWidget(suppPre,4,4);
    std::vector<Tache*>::const_iterator ite = _tache->getPrerequis().begin();
    while (ite != _tache->getPrerequis().end()){
		QListWidgetItem * item = new QListWidgetItem((*ite)->getTitre());
		prerequis->addItem(item);
		++ite;
	}


    if (dynamic_cast<TacheComposite*>(_tache)){
		label_sousTaches = new QLabel("Sous Taches :");
		sousTaches = new QListWidget();
		box->addWidget(label_sousTaches, 2, 2);
        box->addWidget(sousTaches, 3, 2, 3, 1);
		box->addWidget(label_echeance, 3, 0);
		box->addWidget(echeance, 3, 1);

        std::vector<Tache*>::const_iterator ite = ((TacheComposite*)_tache)->getSousTaches().begin();
        while (ite != ((TacheComposite*)_tache)->getSousTaches().end()){
			QListWidgetItem * item = new QListWidgetItem((*ite)->getTitre());
            item->setData(Qt::UserRole, QVariant((*ite)->getId()));
			sousTaches->addItem(item);
			ite++;
		}
	}

    else{					//si tache Unitaire
        label_pre = new QLabel();
		box->addWidget(label_pre, 0, 6);
		labelDureeInitiale = new QLabel("durée Initiale");
		heureDebut = new QSpinBox(this);
		minDebut = new QSpinBox(this);

        if (dynamic_cast<TacheUnitairePreemptee*>(_tache)){
            label_pre->setText("Tache preemptee");
			heureEffectue = new QSpinBox(this);
			minEffectue = new QSpinBox(this);
			labelDureeEffectue = new QLabel("durée Effectuée (si preemptive)");
            heureEffectue->setValue(((TacheUnitairePreemptee*)_tache)->getDureeEffectuee().getDureeEnHeures());
			heureEffectue->setSuffix(" heure(s)");
            minEffectue->setValue(((TacheUnitairePreemptee*)_tache)->getDureeEffectuee().getResteDureeEnMinutes());
			minEffectue->setSuffix(" minute(s)");
			minEffectue->setReadOnly(true);
			heureEffectue->setReadOnly(true);
			box->addWidget(heureEffectue, 5, 1);
			box->addWidget(minEffectue, 5, 2);
			box->addWidget(labelDureeEffectue, 5, 0);

		}
        else
            label_pre->setText("Tache Non preemptee");

        heureDebut->setValue(((TacheUnitaire*)_tache)->getDuree().getDureeEnHeures());
		heureDebut->setSuffix(" heure(s)");
        minDebut->setValue(((TacheUnitaire*)_tache)->getDuree().getResteDureeEnMinutes());
		minDebut->setSuffix(" minute(s)");
		minDebut->setSingleStep(15);

		box->addWidget(label_echeance, 3, 0);
		box->addWidget(echeance, 3, 1);
		box->addWidget(heureDebut, 4, 1);
		box->addWidget(minDebut, 4, 2);
		box->addWidget(labelDureeInitiale, 4, 0);
	}

    QObject::connect(ajoutPre, SIGNAL(clicked()), this, SLOT(addPre()));
    QObject::connect(suppPre, SIGNAL(clicked()), this, SLOT(delPre()));
	QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));


}


void TacheEditeur::addPre(){


}

void TacheEditeur::delPre(){
    QListWidgetItem *p = prerequis->takeItem(prerequis->currentRow());
    prerequis->removeItemWidget(p);
}


void TacheEditeur::save(){
	if (dynamic_cast<TacheUnitaire*>(_tache)){
		Duree d(heureDebut->value(), minDebut->value());
		_tache->setTitre(titre->text());
		_tache->setDatesDisponibiliteEcheance(dispo->date(), echeance->date());
		((TacheUnitaire*)_tache)->setDuree(d);
	}
	else{
		/////faire modif sous taches
	}
	//// faire modifs prerequis
}
	



