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


Tache::Tache(int id, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> pre, Tache* parent):
Evenement(id, titre), dateDispo(dDispo), dateEcheance(dEcheance), parent(parent), prerequis(std::vector<Tache*>()){
	if (dEcheance < QDate::currentDate())
		throw CalendarException("date d'echeance deja passee");
	if (dEcheance < dDispo)
		throw CalendarException("date d'echeance anterieure a la date de dispo");
	if (dynamic_cast<TacheComposite*>(parent) != NULL)
		dynamic_cast<TacheComposite*>(parent)->ajouterSousTache(this);
	else if (parent != 0)
		throw CalendarException("la tache parent n'est pas composite");
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
	std::vector<Tache*>::const_iterator ite = prerequis.begin();
	while (ite != prerequis.end()){
		if ((*ite) == this){
			throw CalendarException("on ne peut pas faire de soi meme un prerequis !");
			return;
		}
		if ((*ite) == pre){
			throw CalendarException("prerequis deja present");
			return;
		}
		if ((*ite)->getDateEcheance() < getDateEcheance()){
			throw CalendarException("date d'echeance du prerequis ulterieure a l'echeance de la tache");
			return;
		}
		std::vector<Tache*>::const_iterator itePre = ((*ite)->getPrerequis()).begin();
		while (itePre != (*ite)->getPrerequis().end()){
			if ((*itePre) == this){
				throw CalendarException("boucle de prerequis (a->b->a)");
				return;
			}
			itePre++;
		}
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

void Tache::setDateDisponibilite(const QDate & dDispo) {
    if(dDispo<dateEcheance)
        throw CalendarException("date dispo inférieure a echeance");
    else{
        /*
         *              on calcule la date dispo a partir des
         *              echeances des prerequis ou on verifie
         *              juste qu'elle soit apres ?
         * */
    }
    dateDispo = dDispo;
}

void Tache::setDateEcheance(const QDate & dEcheance){
    if (dEcheance < dateDispo)
        throw CalendarException("date echeance inferieure a date dispo");
    else{
        std::vector<Tache*>::iterator ite = prerequis.begin();
        while(ite != prerequis.end()){
            if((*ite)->getDateEcheance() < dEcheance)
                throw CalendarException("date echeance inferieure a l'echeance d'un prerequis");
            ++ite;
        }
    dateEcheance = dEcheance;
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
	Duree nDuree = dureeEffectuee;
	if (op == "=")
		nDuree = d;
	else if (op == "+=")
		nDuree += d;
	else if (op == "-=")
		nDuree -= d;
	else
		throw CalendarException("operation non reconnue");
	if (nDuree.getDureeEnMinutes() < 0)
		throw CalendarException("duree effectuee < 0");
	int nbMinRestantes = getDuree().getDureeEnMinutes() - nDuree.getDureeEnMinutes();
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
