#include "projet.h"



Projet::Projet(const QString & t, const QDate & deb, const QDate & fin) : currentId(0), titre(t), debut(deb), fin(fin){}

Projet::~Projet()
{
    taches.clear();
}


Tache* Projet::trouverTache(const QString & t) const{
	std::vector<Tache*>::const_iterator ite = taches.begin();
	while (ite != taches.end()){
		if ((*ite)->getTitre() == t)
			return *ite;
		++ite;
	}
    return NULL;
}
Tache* Projet::trouverTache(int id) const{
	std::vector<Tache*>::const_iterator ite = taches.begin();
	while (ite != taches.end()){
		if ((*ite)->getId() == id)
			return *ite;
		++ite;
	}
    return NULL;
}


Tache & Projet::creerTache(QString type, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> pre, Tache* parent, Duree du){
    Tache *t = NULL;
    try{
        if (type == "TacheComposite")
            t = new TacheComposite(currentId++, titre, dDispo, dEcheance, pre, parent);
        if (type == "TacheUnitaire")
            t = new TacheUnitaire(currentId++, titre, dDispo, dEcheance, du, pre, parent);
        if (type == "TacheUnitairePreemptee")
            t = new TacheUnitairePreemptee(currentId++, titre, dDispo, dEcheance, du, pre, parent);
        if(t != NULL)
            ajouterTache(t);
        else
            throw CalendarException("type impossible a creer");
        return *t;
    }
	catch (CalendarException & e){
        QMessageBox::information(NULL, "erreur", e.getInfo());
    }
}


void Projet::ajouterTache(Tache * t){
	taches.push_back(t);
}

const std::vector<Tache*> Projet::getTaches() const{
	return taches;
}
Tache& Projet::getTache(const QString & t){
	std::vector<Tache*>::const_iterator ite = taches.begin();
	while (ite != taches.end()){
		if ((*ite)->getTitre() == t){
			return *(*ite);
		}
		ite++;
	}
	throw CalendarException("tache introuvable");
}

Tache& Projet::getTache(int id){
	Tache * tache = trouverTache(id);
	if (!tache)
		throw CalendarException("tache introuvable");
	else return *tache;
}
const Tache& Projet::getTache(const QString & t)const{
	Tache * tache = trouverTache(t);
	if (!tache)
		throw CalendarException("tache introuvable");
	else return *tache;
}
const Tache& Projet::getTache(int id)const{
	std::vector<Tache*>::const_iterator ite = taches.begin();
	while (ite != taches.end()){
		if ((*ite)->getId() == id)
			return *(*ite);
		ite++;
	}
	throw CalendarException("tache introuvable");
}
void Projet::supprimerTache(int id){
    std::vector<Tache*>::iterator ite = taches.begin();
	while (ite != taches.end()){
		if ((*ite)->getId() == id){
			delete *ite;
			taches.erase(ite);
			return;
		}
		ite++;
	}
	throw CalendarException("tache introuvable");
}
void Projet::supprimerTache(const QString & t){
    std::vector<Tache*>::iterator ite = taches.begin();
	while (ite != taches.end()){
		if ((*ite)->getTitre() == t){
			delete *ite;
			taches.erase(ite);
			return;
		}
		ite++;
	}
	throw CalendarException("tache introuvable");
}

QTreeWidget * Projet::creerArbre() const{
    QTreeWidget *arbre = new QTreeWidget();
    std::vector<Tache*>::const_iterator ite = taches.begin();
    while (ite != taches.end()){
        if ((*ite)->getParent() == 0){
            QTreeWidgetItem * item = new QTreeWidgetItem();
            item->setText(0, (*ite)->getTitre());
            item->setText(1, QString::number((*ite)->getId()));
            if ((*ite)->isProgramme())
                item->setBackgroundColor(0, QColor(0, 255, 0, 100));
            else
                item->setBackgroundColor(0, QColor(255, 0, 0, 100));
            arbre->addTopLevelItem(item);
            if (dynamic_cast<TacheComposite*>(*ite) != NULL)
                AjouterSousTachesArbre((TacheComposite*)(*ite), *item);
        }
        ite++;
    }
    return arbre;
}
void Projet::AjouterSousTachesArbre(TacheComposite * t, QTreeWidgetItem & i) const {
    const std::vector<Tache*> l = t->getSousTaches();
    std::vector<Tache*>::const_iterator ite = l.begin();
    while (ite != l.end()){
        QTreeWidgetItem * item = new QTreeWidgetItem();
        item->setText(0, (*ite)->getTitre());
        item->setText(1, QString::number((*ite)->getId()));
        i.addChild(item);
        if ((*ite)->isProgramme())
            item->setBackgroundColor(0, QColor(0, 255, 0, 100));
        else
            item->setBackgroundColor(0, QColor(255, 0, 0, 100));
        if (dynamic_cast<TacheComposite*> (*ite) != NULL)
            AjouterSousTachesArbre((TacheComposite*)(*ite), *item);
        ite++;
    }
}












ProjetManager * ProjetManager::instance = 0;

ProjetManager& ProjetManager::getInstance(){
    if (instance == 0)
        instance = new ProjetManager();
    return *instance;
}
void ProjetManager::libererInstance(){
    if (instance)
        delete instance;
    instance = 0;
}
ProjetManager::~ProjetManager()
{
    projets.clear();
}

Projet* ProjetManager::trouverProjet(const QString &t) const{
	std::vector<Projet*>::const_iterator ite = projets.begin();
	while (ite != projets.end()){
		if ((*ite)->getTitre() == t)
			return *ite;
		++ite;
	}
    return NULL;
}



void ProjetManager::ajouterProjet(const QString& t, const QDate& dispo, const QDate& echeance){
    if(trouverProjet(t))
		CalendarException ("ce projet existe déjà");
    else
		projets.push_back(new Projet(t, dispo, echeance));
}

Projet& ProjetManager::getProjet(const QString & t){
	std::vector<Projet*>::iterator ite = projets.begin();
	while (ite != projets.end()){
		if ((*ite)->getTitre() == t){
			Projet& t = *(*ite);
			return t;
		}
		ite++;
	}
    throw CalendarException("projet introuvable");
}


const std::vector<Projet*> & ProjetManager::getProjets() const{
	return projets;
}

const Projet& ProjetManager::getProjet(const Tache* tacheCherchee) const{
    std::vector<Projet*>::const_iterator ite = projets.begin();
    while (ite != projets.end()){
        std::vector<Tache*> tachesProj = (*ite)->getTaches();
        std::vector<Tache*>::const_iterator iteTache = tachesProj.begin();
        while (iteTache != tachesProj.end()){
            if((*iteTache) == tacheCherchee)
                return *(*ite);
        iteTache++;
        }
        ite++;
    }
    throw CalendarException("projet introuvable");
}



void ProjetManager::supprimerProjet(const QString t){
	std::vector<Projet*>::iterator ite = projets.begin();
	while (ite != projets.end()){
		if ((*ite)->getTitre() == t){
			delete *ite;
			projets.erase(ite);
			return;
		}
		ite++;
	}
    throw CalendarException("projet introuvable");
}



QTreeWidget * ProjetManager::creerArbreProjets(){
	QTreeWidget * arbre = new QTreeWidget();
	const std::vector<Projet*> lProjets = getProjets();
	std::vector<Projet*>::const_iterator iteProjets = lProjets.begin();
	while (iteProjets != lProjets.end()){
		QTreeWidgetItem * itemProjet = new QTreeWidgetItem();
		itemProjet->setText(0, (*iteProjets)->getTitre());
		arbre->addTopLevelItem(itemProjet);
		const std::vector<Tache*> l = (*(*iteProjets)).getTaches();
		std::vector<Tache*>::const_iterator ite = l.begin();
		while (ite != l.end()){
			if ((*ite)->getParent() == 0){
				QTreeWidgetItem * item = new QTreeWidgetItem();
				item->setText(0, (*ite)->getTitre());
				item->setText(1, QString::number((*ite)->getId()));
				if ((*ite)->isProgramme())
					item->setBackgroundColor(0, QColor(0, 255, 0, 100));
				else
					item->setBackgroundColor(0, QColor(255, 0, 0, 100));
				itemProjet->addChild(item);
				if (dynamic_cast<TacheComposite*>(*ite) != NULL)
					AjouterSousTachesArbre((TacheComposite*)(*ite), *item);
			}
			ite++;
		}
		iteProjets++;
	}
	return arbre;
}

void ProjetManager::AjouterSousTachesArbre(TacheComposite * t, QTreeWidgetItem & i) {
	const std::vector<Tache*> l = t->getSousTaches();
	std::vector<Tache*>::const_iterator ite = l.begin();
	while (ite != l.end()){
		QTreeWidgetItem * item = new QTreeWidgetItem();
		item->setText(0, (*ite)->getTitre());
		item->setText(1, QString::number((*ite)->getId()));
		i.addChild(item);
		if ((*ite)->isProgramme())
			item->setBackgroundColor(0, QColor(0, 255, 0, 100));
		else
			item->setBackgroundColor(0, QColor(255,0,0,100));
		if (dynamic_cast<TacheComposite*> (*ite) != NULL)
			AjouterSousTachesArbre((TacheComposite*)(*ite), *item);
		ite++;
	}
}
