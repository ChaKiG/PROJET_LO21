#include "fenetres_gestion_programmations.h"





CreationProgrammation::CreationProgrammation(QWidget * parent){
	setParent(parent);
	choisir = new QPushButton("choisir");
	newActi = new QPushButton("nouvelle activite");
	l = new QLabel("Choisir la tache a programmer");
    arbre = ProjetManager::getInstance().creerArbreProjets();
	lay = new QGridLayout();

	l_debut = new QLabel("choisir debut :");
	d_j = new QDateEdit(QDate::currentDate());
	d_h = new QSpinBox();
	d_m = new QSpinBox();

	d_m->setRange(0, 45);
	d_m->setSingleStep(15);
	d_m->setSuffix(" minutes");
	d_h->setSuffix(" heures");
	d_h->setValue(QTime::currentTime().hour());
	d_m->setValue(QTime::currentTime().minute() - QTime::currentTime().minute() % 15);


	lay->addWidget(l_debut, 4, 0);
	lay->addWidget(d_j, 5, 0);
	lay->addWidget(d_h, 5, 1);
	lay->addWidget(d_m, 5, 2);
	lay->addWidget(l, 0, 0);
	lay->addWidget(arbre, 1, 0, 3, 3);
	lay->addWidget(choisir, 6, 2);
	lay->addWidget(newActi, 6, 0);

	setLayout(lay);

	QObject::connect(choisir, SIGNAL(clicked()), this, SLOT(creerProg()));
	QObject::connect(newActi, SIGNAL(clicked()), this, SLOT(creerActi()));
	show();
}



CreationProgrammation::~CreationProgrammation(){
	delete arbre;
	delete choisir;
	delete l;
	delete l_debut;
	delete d_j;
	delete d_h;
	delete d_m;
	delete lay;
}





void CreationProgrammation::creerProg(){
	try{
		QTreeWidgetItem * p;
        if ((p = arbre->currentItem())){
			if (p->parent()){
				while (p->parent() != NULL)
					p = p->parent();
				Tache * t = &(ProjetManager::getInstance().getProjet(p->text(0)).getTache(arbre->currentItem()->text(0)));
				if (!dynamic_cast<TacheComposite*>(t)){
					QDate date = d_j->date();
					QTime time(d_h->value(), d_m->value());
					ProgrammationManager::getInstance().creerProgrammation(t, date, time);
					if (!dynamic_cast<TacheUnitairePreemptee*>(t))
						new EmploiDuTemps(date);
					close();
				}
				else
					throw CalendarException("tentative de programmer une tache composite");
			}
			else
				throw CalendarException("tentative de programmer un projet");
		}
		else
			throw CalendarException("aucun objet selectionne");
	}
	catch (CalendarException & c){
		QMessageBox::information(this, "erreur", c.getInfo());
	}
}

void CreationProgrammation::creerActi(){
	new CreationActivite();
	close();
}




CreationActivite::CreationActivite(QWidget * parent){
	setParent(parent);
	lay = new QGridLayout;
	valider = new QPushButton("valider");
	typeActi = new QSpinBox();
	typeActi->setMinimum(0);
	typeActi->setMaximum(15);
	textacti = new QLabel("Rentrez le(s) nom(s) du/des participants");
	text = new QLabel("Choisissez le nombre de participants à l'activité");
	text1 = new QLabel("Choisissez la date et l'heure de debut ");
	text2 = new QLabel("Choisissez la durée de votre activité");
	text3 = new QLabel("Choisissez un titre à votre activité");
	titre = new QLineEdit();
	debut = new QDateTimeEdit(QDateTime::currentDateTime());
	heure = new QSpinBox();
	minute = new QSpinBox();
	text4 = new QLabel("Choisissez un lieu");
	lieu = new QLineEdit();
	setLayout(lay);
	lay->addWidget(text3, 0, 0);
	lay->addWidget(titre, 1, 0);
	lay->addWidget(text, 2, 0);
	lay->addWidget(typeActi, 3, 0);
	lay->addWidget(text1, 4, 0);
	lay->addWidget(debut, 5, 0);
	lay->addWidget(text2, 6, 0);
	lay->addWidget(heure, 7, 0);
	lay->addWidget(minute, 8, 1);
	lay->addWidget(text4, 9, 0);
	lay->addWidget(lieu, 10, 0);
	lay->addWidget(valider, 11, 1, 1, 1);
	lay->addWidget(textacti, 12, 0);



	minute->setMaximum(60);
	minute->setSingleStep(15);
	heure->setMaximum(12);
	minute->setSuffix(" minutes");
	heure->setSuffix(" heures");
	show();

	QObject::connect(typeActi, SIGNAL(valueChanged(int)), this, SLOT(change(int)));
	QObject::connect(valider, SIGNAL(clicked()), this, SLOT(save()));

}


void CreationActivite::save(){
	Duree d(heure->value(), minute->value());
	ActiviteTraditionnelle * acti = NULL;
	try{
		if (typeActi->value() == 1){
			acti = new Rdv(titre->text(), d, lieu->text(), List.first()->text());
			ProgrammationManager::getInstance().creerProgrammation(acti, debut->date(), debut->time());
		}
		else{
			std::vector<QString> vec;
			for (QList<QLineEdit*>::iterator it = List.begin(); it != List.end(); ++it)
				vec.push_back((*it)->text());
			Reunion * reunion = new Reunion(titre->text(), d, lieu->text(), vec);
			ProgrammationManager::getInstance().creerProgrammation(reunion, debut->date(), debut->time());
		}
		new EmploiDuTemps(debut->date());
	}
	catch (CalendarException & e){
		QMessageBox::information(this, "erreur", e.getInfo());
		delete acti;
	}
	close();
}


void CreationActivite::change(int){
	if (!List.empty()){
		for (QList<QLineEdit*>::iterator it = List.begin(); it != List.end(); ++it){
			lay->removeWidget(*it);
			delete (*it);
		}
		List.clear();
	}
	for (int i = 0; i<typeActi->value(); i++){
		QLineEdit * participant = new QLineEdit;
		lay->addWidget(participant, i + 13, 0);
		List.append(participant);
	}
	show();
}



CreationActivite::~CreationActivite(){
	delete valider;
	delete text;
	delete text1;
	delete text2;
	delete text3;
	delete text4;
	List.clear();
	delete titre;
	delete debut;
	delete typeActi;
	delete heure;
	delete minute;
	delete lay;
}




ProgrammationEditeur::ProgrammationEditeur(Programmation & prog, QWidget * parent) : _prog(prog){
	setParent(parent);
	lay = new QGridLayout();
	supp = new QPushButton("Supprimmer Programmation");
	val = new QPushButton("Sauvegarder");
	ann = new QPushButton("annuler");
	debut_j = new QDateEdit(prog.getDateChoisie());
	debut_h_h = new QSpinBox();
	debut_h_m = new QSpinBox();
	dur_h = new QSpinBox();
	dur_m = new QSpinBox();
	titre = new QLineEdit(prog.getEvent()->getTitre());
	titre->setReadOnly(true);
	l_date = new QLabel("Date");
	l_debut = new QLabel("Horaire de debut");
	l_duree = new QLabel("Duree");
	l_titre = new QLabel("titre de l'evenement");

	setLayout(lay);
	lay->addWidget(supp, 0, 0, 1, 2);
	lay->addWidget(l_titre, 1, 0);
	lay->addWidget(titre, 2, 0, 1, 2);
	lay->addWidget(l_date, 3, 0);
	lay->addWidget(debut_j, 4, 0);
	lay->addWidget(l_debut, 5, 0);
	lay->addWidget(debut_h_h, 6, 0);
	lay->addWidget(debut_h_m, 6, 1);
	lay->addWidget(l_duree, 7, 0);
	lay->addWidget(dur_h, 8, 0);
	lay->addWidget(dur_m, 8, 1);
	lay->addWidget(ann, 9, 0);
	lay->addWidget(val, 9, 1);


	debut_h_h->setRange(7, 21);
	debut_h_m->setRange(0, 45);
	debut_h_m->setSingleStep(15);
	debut_h_m->setSuffix(" minutes");
	debut_h_h->setSuffix(" heures");
	debut_h_h->setValue(prog.getHoraireChoisi().hour());
	debut_h_m->setValue(prog.getHoraireChoisi().minute());


	dur_h->setValue(prog.getDuree().getDureeEnHeures());
	dur_m->setValue(prog.getDuree().getResteDureeEnMinutes());
	dur_h->setRange(0, (prog.getEvent())->getDuree().getDureeEnHeures());
	dur_m->setRange(0, 45);
	dur_m->setSingleStep(15);
	dur_m->setSuffix(" minutes");
	dur_h->setSuffix(" heures");

	Evenement * evt = prog.getEvent();
	if (!dynamic_cast<TacheUnitairePreemptee*>(evt)){
		dur_m->setReadOnly(true);
		dur_h->setReadOnly(true);
	}


	QObject::connect(ann, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(val, SIGNAL(clicked()), this, SLOT(save()));
	QObject::connect(supp, SIGNAL(clicked()), this, SLOT(delprog()));

	show();
}


ProgrammationEditeur::~ProgrammationEditeur(){
	delete lay;
	delete debut_j;
	delete debut_h_h;
	delete debut_h_m;
	delete dur_m;
	delete dur_h;
	delete val;
	delete ann;
}



void ProgrammationEditeur::save(){
    try{
        _prog.setDateChoisie(debut_j->date());
        _prog.setHoraireChoisi(QTime(debut_h_h->value(), debut_h_m->value()));
        if(dynamic_cast<TacheUnitairePreemptee*>(_prog.getEvent()))
            _prog.setDuree(Duree(dur_m->value() + 60 * dur_h->value()));
    }catch (CalendarException & e){
            QMessageBox::information(NULL,"erreur",e.getInfo());
    }
    close();
}

void ProgrammationEditeur::delprog(){
    if (dynamic_cast<ActiviteTraditionnelle*>(_prog.getEvent())){
		if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "sur ?", "Ceci supprimmera definitivement l'activite", QMessageBox::Yes | QMessageBox::No).exec())
			ProgrammationManager::getInstance().supprimerProgrammation(_prog.getId());
	}
	else
		ProgrammationManager::getInstance().supprimerProgrammation(_prog.getId());
	new EmploiDuTemps(debut_j->date());
	close();
}
