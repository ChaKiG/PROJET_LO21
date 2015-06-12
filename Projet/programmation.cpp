#include "programmation.h"
#include "emploidutemps.h"



int Programmation::currentId = 0;

Programmation::Programmation(Evenement * event, const QDate & dateChoisie, const QTime & horaireChoisi, Duree dur) : id(++currentId), dateChoisie(dateChoisie), horaireChoisi(horaireChoisi), duree(dur), evt(event){
	try{
		if (dynamic_cast<TacheUnitairePreemptee*>(event))
			((TacheUnitairePreemptee*)event)->addDureeEffectuee(dur);
		else
            event->setProgramme(true);
	}
	catch (CalendarException & e){
		QMessageBox::information(NULL, "erreur", e.getInfo());
	}
}


const QTime  Programmation::getHoraireFin () const {
    QTime horaireecheance=horaireChoisi;
    int sec = 60 *duree.getDureeEnMinutes();

    return horaireecheance.addSecs(sec);}


Programmation Programmation::operator=(Programmation & other){
	id = other.id;
	dateChoisie = other.dateChoisie;
	horaireChoisi = other.horaireChoisi;
	evt = other.evt;
	duree = other.duree;
	return *this;

}
Programmation::Programmation(Programmation & other) : id(other.id), dateChoisie(other.dateChoisie), horaireChoisi(other.horaireChoisi), duree(other.duree), evt(other.evt){}

void Programmation::setDuree(Duree d){
	if (dynamic_cast<TacheUnitairePreemptee*>(evt)){
		((TacheUnitairePreemptee*)evt)->subDureeEffectuee(duree);
		((TacheUnitairePreemptee*)evt)->addDureeEffectuee(d);
		duree = d;
	}
	else throw CalendarException("impossible de changer la duree d'ne tache non preemptee");
}



bool Programmation::operator>(const Programmation & other) const{	
	if (dateChoisie == other.dateChoisie){
		if (getHoraireFin() > other.getHoraireFin())
			return true;
		else
			return false;
	}
	else if (dateChoisie > other.dateChoisie)
		return true;
	else
		return false;
}
bool Programmation::operator<(const Programmation & other) const{
	return (!(*this>other));
}

Programmation::~Programmation() {
    if(dynamic_cast<ActiviteTraditionnelle*>(evt))
        delete evt;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////          PROGRAMMATION_MANAGER              //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProgrammationManager * ProgrammationManager::instance = 0;


ProgrammationManager& ProgrammationManager::getInstance(){
    if (instance == 0)
        instance = new ProgrammationManager();
    return *instance;
}
void ProgrammationManager::libererInstance(){
    if (instance)
        delete instance;
    instance = 0;
}
ProgrammationManager::~ProgrammationManager(){
    programmations.clear();
}
void ProgrammationManager::addItem(Programmation* t){
	programmations.push_back(t);
}

Programmation* ProgrammationManager::createProgPreemptee(Evenement * event, QDate date, QTime horaire){
	return new Programmation(event, date, horaire);
}


Programmation* ProgrammationManager::trouverProgrammation(int id) const{
    std::vector<Programmation*>::const_iterator ite = programmations.begin();
	while (ite != getProgrammations().end()){
        if ((*ite)->getId() == id)
            return *ite;
        ++ite;
    }
    return NULL;
}

Programmation* ProgrammationManager::trouverDerniereProgrammation(Evenement * evt)const{
	if (dynamic_cast<TacheComposite*>(evt)){
		std::vector<Tache*> sousTaches = ((TacheComposite*)evt)->getSousTaches();
		std::vector<Tache*>::iterator iteST = sousTaches.begin();
		Programmation *derniereProg = NULL;
		Programmation *derniereProgST = NULL;
		while (iteST != sousTaches.end()){
			derniereProgST = trouverDerniereProgrammation(*iteST);
			if (derniereProg == NULL)
				derniereProg = derniereProgST;
			else if (*derniereProgST > *derniereProg)
					derniereProg = derniereProgST;
			++iteST;
		}
		return derniereProg;
	}
	else{
		std::vector<Programmation*>::const_iterator ite = programmations.begin();
		Programmation* derniereProg = NULL;
		while (ite != programmations.end()){
			if ((*ite)->getEvent() == evt)
				derniereProg = (*ite);
			++ite;
		}
		return derniereProg;
	}
}

Programmation& ProgrammationManager::getProgrammation(int id) {
    Programmation* p = trouverProgrammation(id);
    if (!p) 
		throw CalendarException("erreur, ProgrammationManager, programmation inexistante");
	else
		return *p;
}
Programmation& ProgrammationManager::getDerniereProgrammation(Evenement * evt) {
	Programmation* p = trouverDerniereProgrammation(evt);
	if (!p)
		throw CalendarException("erreur, ProgrammationManager, programmation inexistante");
	else
		return *p;
}


bool ProgrammationManager::creneaulibre(const QDate& da, const QTime& progHoraireDebut, const Duree& du)
{
    std::vector<Programmation*>::const_iterator ite = programmations.begin();
	int h_fin_en_min = progHoraireDebut.hour() * 60 + progHoraireDebut.minute() + du.getDureeEnMinutes();
	QTime progHoraireFin(h_fin_en_min / 60, h_fin_en_min % 60, 0);

    while (ite != programmations.end()){		
		if ((*ite)->getDateChoisie() == da){
			QTime iteHoraireDeb = (*ite)->getHoraireChoisi();
			h_fin_en_min = iteHoraireDeb.hour() * 60 + iteHoraireDeb.minute() + (*ite)->getDuree().getDureeEnMinutes();
			QTime iteHoraireFin(h_fin_en_min / 60, h_fin_en_min % 60, 0);
			
			if ((iteHoraireDeb >= progHoraireDebut && iteHoraireDeb < progHoraireFin)
				|| (iteHoraireFin > progHoraireDebut && iteHoraireFin < progHoraireFin)
				|| (iteHoraireDeb <= progHoraireDebut && iteHoraireFin > progHoraireFin))
					return false;
		}
       ++ite;
    }
	QTime findejournee(21, 0);
	QTime debutdejournee(7, 0);
	if (progHoraireFin > findejournee || progHoraireDebut < debutdejournee)
		throw CalendarException("horaire de nuit");
    return true;
}


void ProgrammationManager::creerProgrammation(Evenement * event, QDate dateChoisie, QTime horaireChoisi){
	Duree duree;
	if (dynamic_cast<Tache*>(event)){
		std::vector<Tache*> pre = ((Tache*)event)->getPrerequis();
		std::vector<Tache*>::iterator ite = pre.begin();
		while (ite != pre.end()){
			if ((*ite)->isProgramme()){
				Programmation & prog = getDerniereProgrammation(*ite);
				if (prog.getDateChoisie() == dateChoisie)
					if (prog.getHoraireFin() > horaireChoisi)
						throw CalendarException("prerequis programme apres cette tache");
				if (prog.getDateChoisie() > dateChoisie)
					throw CalendarException("prerequis programme apres cette tache");
			}
			else{
				throw CalendarException("prerequis non programme");
				return;
			}
			ite++;
		}
	}
	if (!event->isProgramme()){
		if (dynamic_cast<TacheComposite*>(event))
			throw CalendarException("on ne peut pas programmer des taches composites");
		else{
			if (dynamic_cast<TacheUnitairePreemptee*>(event)){
				new CreationProgrammationPreemptee(event, dateChoisie, horaireChoisi);
			}
			else
				if (dynamic_cast<TacheUnitaire*>(event)){
				duree = ((TacheUnitaire*)event)->getDuree();
				if (creneaulibre(dateChoisie, horaireChoisi, duree)){
					Programmation * prog = new Programmation(event, dateChoisie, horaireChoisi, duree);
					programmations.push_back(prog);
				}
				else
					throw CalendarException("horaire indisponible");
				}
				else{
					if (creneaulibre(dateChoisie, horaireChoisi, duree)){
						duree = ((ActiviteTraditionnelle*)event)->getDuree();
						Programmation * prog = new Programmation(event, dateChoisie, horaireChoisi, duree);
						programmations.push_back(prog);
					}
					else
						throw CalendarException("horaire indisponible");
				}
		}
	}
	else 
		throw CalendarException("evenement deja programmé");
}






std::vector<Programmation*> ProgrammationManager::getSemaine(QDate & date) const{
	std::vector<Programmation*> sem; 

	std::vector<Programmation*>::const_iterator ite = programmations.begin();
	while (ite != programmations.end()){
		if ((*ite)->getDateChoisie() >= date && (*ite)->getDateChoisie() < date.addDays(7))
			sem.push_back(*ite);
		ite++;
	}
	return sem;
}


void ProgrammationManager::supprimerProgrammationsEvt(const QString t){
    std::vector<Programmation*>::iterator ite = programmations.begin();
	while (ite != programmations.end()){
		if ((*ite)->getEvent()->getTitre() == t){
			if (dynamic_cast<TacheUnitairePreemptee*>((*ite)->getEvent()))
				((TacheUnitairePreemptee*)(*ite)->getEvent())->subDureeEffectuee((*ite)->getDuree());
			else
				(*ite)->getEvent()->setProgramme(false);
			delete *ite;
			programmations.erase(ite);
			return;
		}
		++ite;
	}
	throw CalendarException("Prog introuvable");
}


void ProgrammationManager::supprimerProgrammation(int id){
    std::vector<Programmation*>::iterator ite = programmations.begin();
	while (ite != programmations.end()){
		if ((*ite)->getId() == id){
			if (dynamic_cast<TacheUnitairePreemptee*>((*ite)->getEvent()))
				((TacheUnitairePreemptee*)(*ite)->getEvent())->subDureeEffectuee((*ite)->getDuree());
			else 
				if (dynamic_cast<ActiviteTraditionnelle*>((*ite)->getEvent()))
					delete (*ite)->getEvent();
				else
					(*ite)->getEvent()->setProgramme(false);
			delete *ite;
			programmations.erase(ite);
			return;
		}
		++ite;
	}
	throw CalendarException("prog introuvable");
}





CreationProgrammationPreemptee::CreationProgrammationPreemptee(Evenement * e, QDate date, QTime horaire, Duree dur, QWidget * parent) : event(e), _date(date), _horaire(horaire){
	if (dur.getDureeEnMinutes() == 0)
	{
		setParent(parent);
		lay = new QGridLayout;
		valider = new QPushButton("valider");
		text = new QLabel("Choisissez la duree en heure de votre tache preemptee");
		heure = new QSpinBox(this);
		text1 = new QLabel("Choisissez la duree en minute de votre tache preemptee");
		minute = new QSpinBox(this);
		setLayout(lay);
		lay->addWidget(text, 0, 0);
		lay->addWidget(heure, 1, 0, 1, 3);
		lay->addWidget(text1, 2, 0);
		lay->addWidget(minute, 3, 0, 1, 3);
		lay->addWidget(valider, 4, 1, 1, 1);

		Duree d = ((TacheUnitairePreemptee*)e)->getDuree();
		minute->setRange(0, 60);
		minute->setSingleStep(15);
		minute->setSuffix(" minutes");
		heure->setSuffix(" heures");
		heure->setRange(0, d.getDureeEnHeures());
		show();

		QObject::connect(valider, SIGNAL(clicked()), this, SLOT(save()));
	}
	else{
		if (ProgrammationManager::getInstance().creneaulibre(_date, _horaire, dur.getDureeEnMinutes())){
			Programmation * prog = ProgrammationManager::getInstance().createProgPreemptee(event, _date, _horaire);
			try{
				prog->setDuree(dur);
				ProgrammationManager::getInstance().addItem(prog);
			}
			catch (CalendarException & e){
				delete prog;
				QMessageBox::information(this, "erreur", e.getInfo());
			}
		}
		else
			QMessageBox::information(this, "erreur", "horaire indisponible");
	}
}



void CreationProgrammationPreemptee::save(){
	if (ProgrammationManager::getInstance().creneaulibre(_date, _horaire, minute->value() + 60 * heure->value())){
		Programmation * prog = ProgrammationManager::getInstance().createProgPreemptee(event, _date, _horaire);
		try{
			prog->setDuree(Duree(heure->value(), minute->value()));
			ProgrammationManager::getInstance().addItem(prog);
		}
		catch (CalendarException & e){
			delete prog;
			QMessageBox::information(this, "erreur", e.getInfo());
		}
	}
	else
		QMessageBox::information(this, "erreur", "horaire indisponible");
	new EmploiDuTemps(_date);
	close();
}


CreationProgrammationPreemptee::~CreationProgrammationPreemptee(){
	delete lay;
	delete valider;
	delete text;
	delete text1;
	delete heure;
	delete minute;
}
