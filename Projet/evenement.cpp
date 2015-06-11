#include "evenement.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////       EVENEMENT        ////////////////////////////
////////////////////////////////////////////////////////////////////////////////


Evenement::Evenement(int id, const QString & t) : titre(t), id(id), prog(false){}
const QString& Evenement::getTitre() const{return titre;}
int Evenement::getId() const{return id;}
void Evenement::setTitre(const QString & t){titre = t;}
Evenement::~Evenement(){}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////       TACHE        ////////////////////////////
////////////////////////////////////////////////////////////////////////////////


Tache::Tache(int id, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> pre, Tache* parnt):
Evenement(id, titre), dateDispo(dDispo), dateEcheance(dEcheance), parent(NULL), prerequis(std::vector<Tache*>()){
    if(dynamic_cast<TacheComposite*>(parnt)){
            parent = parnt;
            ((TacheComposite*)parent)->ajouterSousTache(this);
    }else if (parnt != NULL)
        throw CalendarException("parent non composite");
    setDatesDisponibiliteEcheance(dDispo, dEcheance);
    ajoutPrerequis(pre);
}

void Tache::setProgramme(bool effectue) {
	Evenement::setProgramme(effectue);
	if (parent != NULL){
		((TacheComposite*)parent)->updateProg();
	}
}


void Tache::setParent(Tache* n_parent){ parent = n_parent; } ///verifier si pas de boucles ou appartient prerequis

void Tache::ajoutPrerequi(Tache * pre){ 
    if (pre == this)
        throw CalendarException("on ne peut pas faire de soi meme un prerequis !");
    if (pre->getDateEcheance() > getDateDisponibilite())
        throw CalendarException("date echeancedu prerequis supérieure a la date de dispo de la tache");
    if (pre == this)
        throw CalendarException("on ne peut pas faire de soi meme un prerequis !");
    std::vector<Tache*>::const_iterator itePre = pre->getPrerequis().begin();
    while (itePre != pre->getPrerequis().end()){
        if ((*itePre) == this)
            throw CalendarException("boucle de prerequis (a->b->a)");
        itePre++;
    }
    std::vector<Tache*>::const_iterator ite = prerequis.begin();
	while (ite != prerequis.end()){	
        if ((*ite) == pre)
			throw CalendarException("prerequis deja present");
		ite++;
	}
	prerequis.push_back(pre);
}

void Tache::ajoutPrerequis(std::vector<Tache*> vec){
    std::vector<Tache*>::const_iterator ite = vec.begin();
    while(ite != vec.end()){
		ajoutPrerequi(*ite);
        ++ite;
    }
}

void Tache::setPrerequis(std::vector<Tache*> vec){
    std::vector<Tache*> ancien_pre = prerequis;
    try{
        prerequis.clear();
        ajoutPrerequis(vec);
    }catch(CalendarException & e){
        prerequis.clear();
        ajoutPrerequis(ancien_pre);
        QMessageBox::information(NULL, "erreur", e.getInfo());
    }
}

void Tache::setDatesDisponibiliteEcheance(const QDate &dDispo, const QDate & dEcheance){
	if (dDispo>dEcheance)
			throw CalendarException("date dispo superieure a echeance");
	else{
		std::vector<Tache*>::iterator ite = prerequis.begin();
		while (ite != prerequis.end()){
            if ((*ite)->getDateEcheance() > dDispo)
                throw CalendarException("date dispo inferieure a l'echeance d'un prerequis");
            ++ite;
		}
		dateEcheance = dEcheance;
		dateDispo = dDispo;
	}
}


Tache::~Tache(){}



///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////         Tache Unitaire      /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////         Tache Unitaire Preemptee     ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void TacheUnitairePreemptee::setDureeEffectuee(const Duree& dEffectuee) {

	checkPossible("=", dEffectuee);
	dureeEffectuee = dEffectuee;
}
void TacheUnitairePreemptee::addDureeEffectuee(const Duree& dEffectuee) {
	checkPossible("+=", dEffectuee);
	dureeEffectuee += dEffectuee;
}

void TacheUnitairePreemptee::subDureeEffectuee(const Duree& dSupprimmee) {
	checkPossible("-=", dSupprimmee);
	dureeEffectuee -= dSupprimmee;
}

void TacheUnitairePreemptee::checkPossible(std::string op, Duree d) {
    int nDuree = dureeEffectuee.getDureeEnMinutes();
    if (op == "=")
        nDuree = d.getDureeEnMinutes();
    else if (op == "+=")
        nDuree += d.getDureeEnMinutes();
    else if (op == "-=")
        nDuree -= d.getDureeEnMinutes();
    else
        throw CalendarException("operation non reconnue");
    if (nDuree < 0)
        throw CalendarException("duree effectuee < 0");
    int nbMinRestantes = getDuree().getDureeEnMinutes() - nDuree;
    if (nbMinRestantes == 0)
        setProgramme(true);
    if (nbMinRestantes > 0)
        setProgramme(false);
    if (nbMinRestantes < 0)
        throw CalendarException("tentative de programmer plus longtemps que la duree");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////       TACHE COMPOSITE        //////////////////////////
////////////////////////////////////////////////////////////////////////////////



TacheComposite::TacheComposite(TacheComposite& other):
    Tache(other.getId(), other.getTitre(), other.getDateDisponibilite(), other.getDateEcheance(), other.getPrerequis(), other.getParent()){
        std::vector<Tache*>::const_iterator ite = other.sousTaches.begin();
        while(ite != other.sousTaches.end()){
            ajouterSousTache(*ite);
            ++ite;
        }
}

TacheComposite& TacheComposite::operator=(TacheComposite& other){
	sousTaches.clear();
	std::vector<Tache*>::const_iterator ite = other.sousTaches.begin();
	while (ite != other.sousTaches.end()){
		sousTaches.push_back(*ite);
		ite++;
	}
    return *this;
}

void TacheComposite::updateProg(){
	std::vector<Tache*>::const_iterator ite = sousTaches.begin();
	while (ite != sousTaches.end()){
		if (!(*ite)->isProgramme()){
			setProgramme(false);
			return;
		}
		ite++;
	}
	setProgramme(true);
}

void TacheComposite::ajouterSousTache(Tache* ssTache){
    if(ssTache->getDateDisponibilite() < getDateDisponibilite())
        throw CalendarException("date dispo de la sous tache inferieure a la tache");
    else if(ssTache->getDateEcheance() > getDateEcheance())
        throw CalendarException("date echeance de la sous tache superieure a la date d'echeance");
        else
            sousTaches.push_back(ssTache);
}

void TacheComposite::ajouterSousTaches(const std::vector<Tache*> ssTaches){
    std::vector<Tache*>::const_iterator ite = ssTaches.begin();
    while(ite != ssTaches.end()){
        ajouterSousTache(*ite);
        ++ite;
    }
}

Tache* TacheComposite::trouverSousTache(const QString & titreSousTache) const{
    std::vector<Tache*>::const_iterator ite = sousTaches.begin();
    while(ite != sousTaches.end()){
        if((*ite)->getTitre() == titreSousTache)
            return *ite;
        ++ite;
    }
    return 0;
}

Tache* TacheComposite::trouverSousTache(int idSousTache) const{
    std::vector<Tache*>::const_iterator ite = sousTaches.begin();
    while(ite != sousTaches.end()){
        if((*ite)->getId() == idSousTache)
            return *ite;
        ++ite;
    }
    return 0;
}

const std::vector<Tache*> & TacheComposite::getSousTaches() const {
    return sousTaches;
}

const Tache& TacheComposite::getSousTache(const QString & titreSousTache){
    Tache * tache = trouverSousTache(titreSousTache);
    if(tache==0)
        throw CalendarException("sous tache introuvable");
    return *tache;
}

const Tache& TacheComposite::getSousTache(int idSousTache){
    Tache * tache = trouverSousTache(idSousTache);
    if(tache==0)
        throw CalendarException("sous tache introuvable");
    return *tache;


}

void TacheComposite::supprimerSousTache(int idSousTache){
    std::vector<Tache*>::iterator ite = sousTaches.begin();
    while(ite != sousTaches.end()){
        if((*ite)->getId() == idSousTache){
			delete *ite;
            sousTaches.erase(ite);
			return;
        }
        ++ite;
    }
    throw CalendarException("sous tache introuvable");
}

void TacheComposite::supprimerSousTache(const QString & titreSousTache){
    std::vector<Tache*>::iterator ite = sousTaches.begin();
    while(ite != sousTaches.end()){
        if((*ite)->getTitre() == titreSousTache){
			delete *ite;
            sousTaches.erase(ite);
			return;
        }
        ++ite;
    }
    throw CalendarException("sous tache introuvable");
}

Duree TacheComposite::getDuree() const {
	Duree d(0);
	std::vector<Tache*>::const_iterator ite = sousTaches.begin();
	while (ite != sousTaches.end()){
		d += (*ite)->getDuree();
		ite++;
	}
	return d;
}



TacheComposite::~TacheComposite(){}




////////////////////////////////////////////////////////////////////////////////
/////////////////////       ACTIVITE TRADITIONNELLE        /////////////////////
////////////////////////////////////////////////////////////////////////////////

int ActiviteTraditionnelle::currentId = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////       Reunions       ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


void Reunion::supprimmerParticipant(const QString & parti){
    std::vector<QString>::iterator ite = participants.begin();
    while(ite != participants.end()){
        if((*ite) == parti){
            participants.erase(ite);
			return;
        }
        ++ite;
    }
    throw CalendarException( "personne non presente");
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////         Rendez-vous           ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
