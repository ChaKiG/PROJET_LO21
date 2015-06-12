#include "fenetres_gestion_projets.h"
#include <QMessageBox>





GestionProj::GestionProj(){
	lay = new QGridLayout();
    arbre = ProjetManager::getInstance().creerArbreProjets();
	nTache = new QPushButton("ajout Sous Tache (tache selectionnee)");
	nTacheRacine = new QPushButton("ajout Tache (a la racine)");
	addprojet = new QPushButton("ajout projet");
	supprprojet = new QPushButton("supprimer projet");
	exportprojet = new QPushButton("exporter un projet en xml");
	importerprojet = new QPushButton("importer un projet en xml");

	setLayout(lay);
	lay->addWidget(arbre, 0, 0, 3, 1);
	lay->addWidget(addprojet, 0, 1);
	lay->addWidget(supprprojet, 1, 1);
	lay->addWidget(exportprojet, 2, 1);
	lay->addWidget(importerprojet, 3, 1);
	lay->addWidget(nTache, 4, 1);
	lay->addWidget(nTacheRacine, 5, 1);
	arbre->setMinimumHeight(200);
	editeur = NULL;

	QObject::connect(arbre, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(majEdit(QTreeWidgetItem *)));
	QObject::connect(supprprojet, SIGNAL(clicked()), this, SLOT(suppr()));
	QObject::connect(exportprojet, SIGNAL(clicked()), this, SLOT(exportp()));
	QObject::connect(importerprojet, SIGNAL(clicked()), this, SLOT(importp()));
	QObject::connect(addprojet, SIGNAL(clicked()), this, SLOT(ajoutprojet()));
    QObject::connect(nTache, SIGNAL(clicked()), this, SLOT(ajoutTache()));
	QObject::connect(nTacheRacine, SIGNAL(clicked()), this, SLOT(ajoutTacheRacine()));


	show();
}

void GestionProj::ajoutprojet(){
	new ajouterProjet();
	close();
}


void GestionProj::suppr(){
	new suppressionProjet();
	close();
}

void GestionProj::exportp(){
	new exportProjet();
	close();
}

void GestionProj::importp(){
	new importProjet();
	close();
}

void GestionProj::ajoutTacheRacine(){
    try{
        QTreeWidgetItem * proj = NULL;
        if((proj = arbre->currentItem())){
            while(proj->parent())
                proj = proj->parent();
            new GestionTache(ProjetManager::getInstance().getProjet(proj->text(0)));
        }
        else
            throw CalendarException("aucun projet selectionné");
		close();
    }catch (CalendarException & e){
        QMessageBox::information(this,"erreur", e.getInfo());
    }
}
void GestionProj::ajoutTache(){
    try{
        QTreeWidgetItem * proj = NULL;
        if((proj = arbre->currentItem())){
            while(proj->parent())
                proj = proj->parent();
            Projet & ptr_proj = ProjetManager::getInstance().getProjet(proj->text(0));
            Tache & ptr_tache = ptr_proj.getTache(arbre->currentItem()->text(1).toInt());
            if(dynamic_cast<TacheComposite*>(&ptr_tache))
                new GestionSousTache(ptr_proj, ptr_tache);
            else
                throw CalendarException("tache parente non composite");
			close();
        }else
            throw CalendarException("aucun projet selectionné");
    }catch (CalendarException & e){
        QMessageBox::information(this,"erreur", e.getInfo());
    }
}

void GestionProj::majEdit(QTreeWidgetItem * item){
	if (arbre->currentItem()->parent()){
		if (editeur != NULL)
			delete editeur;
		QTreeWidgetItem * p = item->parent();
		while (p->parent()) p = p->parent();
        Projet * proj = &ProjetManager::getInstance().getProjet(p->text(0));
        Tache * tache = &proj->getTache(item->text(1).toInt());
        editeur = new TacheEditeur(proj, tache);      //envoi a la fenetre editeur
		lay->addWidget(editeur, 3, 0);
		editeur->show();
	}
}


GestionProj::~GestionProj(){
	if (editeur != NULL)
		delete editeur;

	delete arbre;
	delete addprojet;
	delete supprprojet;
	delete nTache;
	delete nTacheRacine;
	delete lay;
}


suppressionProjet::suppressionProjet(){
	lay = new QGridLayout();
	text = new QLabel("Selectionner le projet à supprimer");
	box = new QComboBox();
	valider = new QPushButton("valider");
	annuler = new QPushButton("annuler");
	setLayout(lay);

	lay->addWidget(text, 0, 0);
	lay->addWidget(box, 1, 0);
	lay->addWidget(valider, 2, 0);
	lay->addWidget(annuler, 2, 1);
	show();

	const std::vector<Projet*> lProjets = ProjetManager::getInstance().getProjets();
	std::vector<Projet*>::const_iterator iteProjets = lProjets.begin();
	while (iteProjets != lProjets.end()){
		box->addItem((*iteProjets)->getTitre());
		++iteProjets;
	}

	QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(retour()));
	QObject::connect(valider, SIGNAL(clicked()), this, SLOT(deleteprojet()));
}

suppressionProjet::~suppressionProjet(){
	delete text;
	delete box;
	delete valider;
	delete lay;
	delete annuler;
}


void suppressionProjet::deleteprojet(){
	if (box->currentText() != NULL)
		ProjetManager::getInstance().supprimerProjet(box->currentText());
	else
		throw CalendarException("aucun projet n'a été choisi");

	new GestionProj();
	close();
}

void suppressionProjet::retour(){
	new GestionProj();
	close();
}


ajouterProjet::ajouterProjet(){
	lay = new QGridLayout();
	choixtitre = new QLabel("Rentrez le titre de votre nouveau projet");
	choixdateeche = new QLabel("Rentrez la date d'échéance de votre projet");
	choixdatedispo = new QLabel("Rentrez la date de début de votre projet");
	titre = new QLineEdit();
	datedispo = new QDateEdit(QDate::currentDate());
	dateeche = new QDateEdit(QDate::currentDate());
	datedispo->setMinimumDate(QDate::currentDate());


	valider = new QPushButton("valider");
	annuler = new QPushButton("annuler");
	setLayout(lay);

	lay->addWidget(choixtitre, 0, 0, 1, 0);
	lay->addWidget(titre, 1, 0, 1, 0);
	lay->addWidget(choixdatedispo, 2, 0, 1, 0);
	lay->addWidget(datedispo, 3, 0, 1, 0);
	lay->addWidget(choixdateeche, 4, 0, 1, 0);
	lay->addWidget(dateeche, 5, 0, 1, 0);
	lay->addWidget(valider, 6, 0);
	lay->addWidget(annuler, 6, 1);
	show();


	QObject::connect(datedispo, SIGNAL(dateChanged(QDate)), this, SLOT(setmindateechee(QDate)));
	QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(retour()));
	QObject::connect(valider, SIGNAL(clicked()), this, SLOT(ajoutProjet()));
}


void ajouterProjet::setmindateechee(QDate){
	dateeche->setMinimumDate(datedispo->date());
}



void ajouterProjet::ajoutProjet(){
	if (titre != NULL){
		ProjetManager::getInstance().ajouterProjet(titre->text(), datedispo->date(), dateeche->date());
		new GestionProj();
		close();
	}
	else
		throw CalendarException("pas de titre de projet rentré");
}


void ajouterProjet::retour(){
	new GestionProj();
	close();
}




ajouterProjet::~ajouterProjet(){
	delete lay;
	delete choixtitre;
	delete choixdateeche;
	delete choixdatedispo;
	delete titre;
	delete datedispo;
	delete dateeche;
	delete valider;
	delete annuler;
}



exportProjet::exportProjet(){
	lay = new QGridLayout();
	text = new QLabel("Selectionner le projet à exporter");
	box = new QComboBox();
	valider = new QPushButton("valider");
	annuler = new QPushButton("annuler");
	setLayout(lay);

	lay->addWidget(text, 0, 0);
	lay->addWidget(box, 1, 0);
	lay->addWidget(valider, 2, 0);
	lay->addWidget(annuler, 2, 1);
	show();

	const std::vector<Projet*> lProjets = ProjetManager::getInstance().getProjets();
	std::vector<Projet*>::const_iterator iteProjets = lProjets.begin();
	while (iteProjets != lProjets.end()){
		box->addItem((*iteProjets)->getTitre());
		++iteProjets;
	}

	QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(retour()));
	QObject::connect(valider, SIGNAL(clicked()), this, SLOT(expprojet()));
}


void exportProjet::expprojet(){

	bool ok;
	const QString & text = QInputDialog::getText(this, tr("Nom du fichier"),
		tr("Rentrez le nom du fichier"), QLineEdit::Normal,
		QDir::home().dirName(), &ok);
	if (ok && !text.isEmpty()){
		file = text;
		QFile newfile(file + ".xml");
		if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
		QXmlStreamWriter stream(&newfile);
		stream.setAutoFormatting(true);
		stream.writeStartDocument();

		stream.writeStartElement("Projet");
		stream.writeAttribute("nom", box->currentText());
		stream.writeAttribute("debut", ProjetManager::getInstance().getProjet(box->currentText()).getDebut().toString(Qt::ISODate));
		stream.writeAttribute("fin", ProjetManager::getInstance().getProjet(box->currentText()).getFin().toString(Qt::ISODate));
		stream.writeStartElement("Taches");
		std::vector<Tache*> vectprojet = ProjetManager::getInstance().getProjet(box->currentText()).getTaches();
		std::vector<Tache*>::iterator ite = vectprojet.begin();
		while (ite != vectprojet.end()){
			if (dynamic_cast<const TacheUnitairePreemptee*>(*ite)){
				stream.writeStartElement("TacheUnitairePreemptee");
				stream.writeTextElement("id", QString::number((*ite)->getId()));
				stream.writeTextElement("titre", (*ite)->getTitre());
				stream.writeTextElement("dateDispo", dynamic_cast<const TacheUnitairePreemptee*>(*ite)->getDateDisponibilite().toString(Qt::ISODate));
				stream.writeTextElement("dateEcheance", dynamic_cast<const TacheUnitairePreemptee*>(*ite)->getDateEcheance().toString(Qt::ISODate));
				QString str;
				str.setNum(dynamic_cast<const TacheUnitairePreemptee*>(*ite)->getDuree().getDureeEnMinutes());
				stream.writeTextElement("duree", str);
				QString str1;
				str1.setNum(dynamic_cast<const TacheUnitairePreemptee*>(*ite)->getDureeEffectuee().getDureeEnMinutes());
				stream.writeTextElement("dureeEffectuee", str1);
				stream.writeEndElement();
			}
			else{
				if (dynamic_cast<const TacheUnitaire*>(*ite)){
					stream.writeStartElement("TacheUnitaire");
					stream.writeTextElement("id", QString::number((*ite)->getId()));
					stream.writeTextElement("titre", dynamic_cast<const TacheUnitaire*>(*ite)->getTitre());
					stream.writeTextElement("dateDispo", dynamic_cast<const TacheUnitaire*>(*ite)->getDateDisponibilite().toString(Qt::ISODate));
					stream.writeTextElement("dateEcheance", dynamic_cast<const TacheUnitaire*>(*ite)->getDateEcheance().toString(Qt::ISODate));

					QString str;
					str.setNum(dynamic_cast<const TacheUnitaire*>(*ite)->getDuree().getDureeEnMinutes());

					stream.writeTextElement("duree", str);
					stream.writeEndElement();
				}

				else{
					if (dynamic_cast<const TacheComposite*>(*ite)){
						stream.writeStartElement("TacheComposite");
						stream.writeTextElement("id", QString::number((*ite)->getId()));
						stream.writeTextElement("titre", dynamic_cast<const TacheComposite*>(*ite)->getTitre());
						stream.writeTextElement("dateDispo", dynamic_cast<const TacheComposite*>(*ite)->getDateDisponibilite().toString(Qt::ISODate));
						stream.writeTextElement("dateEcheance", dynamic_cast<const TacheComposite*>(*ite)->getDateEcheance().toString(Qt::ISODate));
						stream.writeEndElement();
					}
				}
			}
			ite++;
		}
		stream.writeEndElement();
		stream.writeStartElement("Dependances");

		//enregistrement des liens entre les taches (tableaux de pointeurs etc...
		std::vector<Tache*> vectprojet1 = ProjetManager::getInstance().getProjet(box->currentText()).getTaches();
		std::vector<Tache*>::iterator ite1 = vectprojet1.begin();
        while (ite1 != vectprojet1.end()){
			if (dynamic_cast<const TacheUnitairePreemptee*>(*ite1)){
				stream.writeStartElement("TacheUnitairePreemptee");
				stream.writeTextElement("id", QString::number((*ite1)->getId()));

				if (dynamic_cast<const TacheUnitaire*>(*ite1)->getParent() != NULL){
					QString str2;
					str2.setNum(dynamic_cast<const TacheUnitaire*>(*ite1)->getParent()->getId());
					stream.writeTextElement("parent", str2);
				}
				else
					stream.writeTextElement("parent", "0");

				stream.writeStartElement("prerequis");
				const std::vector<Tache*> vectprerequis = dynamic_cast<const Tache*>(*ite1)->getPrerequis();

				for (std::vector<Tache*>::const_iterator it = vectprerequis.begin(); it<vectprerequis.end(); it++){

					stream.writeTextElement("id", QString::number((*it)->getId()));
				}

				stream.writeEndElement();
				stream.writeEndElement();
			}
			else{
				if (dynamic_cast<const TacheUnitaire*>(*ite1)){
					stream.writeStartElement("TacheUnitaire");
					stream.writeTextElement("id", QString::number((*ite1)->getId()));

					if (dynamic_cast<const TacheUnitaire*>(*ite1)->getParent() != NULL){
						QString str2;
						str2.setNum(dynamic_cast<const TacheUnitaire*>(*ite1)->getParent()->getId());
						stream.writeTextElement("parent", str2);
					}
					else
					{
						stream.writeTextElement("parent", "0");
					}
					stream.writeStartElement("prerequis");
					const std::vector<Tache*> vectprerequis = dynamic_cast<const Tache*>(*ite1)->getPrerequis();

					for (std::vector<Tache*>::const_iterator it = vectprerequis.begin(); it<vectprerequis.end(); it++)
					{

						stream.writeTextElement("id", QString::number((*it)->getId()));
					}

					stream.writeEndElement();
					stream.writeEndElement();
				}

				else{
					if (dynamic_cast<const TacheComposite*>(*ite1)){
						stream.writeStartElement("TacheComposite");
						stream.writeTextElement("id", QString::number((*ite1)->getId()));
						if (dynamic_cast<const TacheComposite*>(*ite1)->getParent() != NULL){
							QString str2;
							str2.setNum(dynamic_cast<const TacheComposite*>(*ite1)->getParent()->getId());
							stream.writeTextElement("parent", str2);
						}
						else
							stream.writeTextElement("parent", "0");

						stream.writeStartElement("prerequis");
						const std::vector<Tache*> vectprerequis = dynamic_cast<const Tache*>(*ite1)->getPrerequis();

						for (std::vector<Tache*>::const_iterator it = vectprerequis.begin(); it<vectprerequis.end(); it++){

							stream.writeTextElement("id", QString::number((*it)->getId()));
						}

						stream.writeEndElement();
						stream.writeStartElement("sousTaches");
						const std::vector<Tache*> vectsoustaches = dynamic_cast<const TacheComposite*>(*ite1)->getSousTaches();

						for (std::vector<Tache*>::const_iterator it = vectsoustaches.begin(); it<vectsoustaches.end(); it++){

							stream.writeTextElement("id", QString::number((*it)->getId()));
						}
						stream.writeEndElement();
						stream.writeEndElement();
					}
				}
			}
			ite1++;
		}
		stream.writeEndElement();
		stream.writeEndElement();
		stream.writeEndDocument();
		newfile.close();
		new GestionProj();
		close();
	}
	else{
		new GestionProj();
		close();
	}
}

void exportProjet::retour()
{
	new GestionProj();
	close();
}




exportProjet::~exportProjet(){
	delete text;
	delete box;
	delete valider;
	delete lay;
	delete annuler;
}


importProjet::importProjet(){
	lay = new QGridLayout();
	text = new QLabel("Rentrez le nom du fichier à importer");
	textedit = new QLineEdit();
	valider = new QPushButton("valider");
	annuler = new QPushButton("annuler");
	setLayout(lay);

	lay->addWidget(text, 0, 0);
	lay->addWidget(textedit, 1, 0);
	lay->addWidget(valider, 2, 0);
	lay->addWidget(annuler, 2, 1);
	show();

	QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(retour()));
	QObject::connect(valider, SIGNAL(clicked()), this, SLOT(load()));
}

importProjet::~importProjet(){
	delete text;
	delete textedit;
	delete valider;
	delete lay;
	delete annuler;
}
void importProjet::retour()
{
	new GestionProj();
	close();
}




void importProjet::load()
{
	//try{
		//qDebug()<<"debut load\n";
		file = textedit->text();
		QDate debut, dfin;
		QString strdebut, strfin;
		QString nom;
		QFile fin(file + ".xml");
		// If we can't open it, let's show an error message.
		if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
			throw CalendarException("Erreur ouverture fichier tâches");
		}
		// QXmlStreamReader takes any QIODevice.
		QXmlStreamReader xml(&fin);
		//qDebug()<<"debut fichier\n";
		// We'll parse the XML until we reach end of it.
		while (!xml.atEnd() && !xml.hasError()) {

			// Read next element.
			QXmlStreamReader::TokenType token = xml.readNext();
			// If token is just StartDocument, we'll go to next.
			if (token == QXmlStreamReader::StartDocument) continue;
			// If token is StartElement, we'll see if we can read it.
			if (token == QXmlStreamReader::StartElement) {
				// If it's named projet, we'll create a project.
				if (xml.name() == "Projet") {
					QXmlStreamAttributes attributes = xml.attributes();
					if (attributes.hasAttribute("nom"))
					{
						nom = attributes.value("nom").toString();

					}
					if (attributes.hasAttribute("debut"))
					{
						strdebut = attributes.value("debut").toString();
						debut.fromString(strdebut, Qt::ISODate);
					}
					if (attributes.hasAttribute("fin"))
					{
						strfin = attributes.value("fin").toString();
						dfin.fromString(strfin, Qt::ISODate);
					}

					ProjetManager::getInstance().ajouterProjet(nom, debut, dfin);
					while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Projet")) {

						if (token == QXmlStreamReader::StartElement) {

							//on crée toutes les taches
							if (xml.name() == "Taches")
							{
								xml.readNext();

								while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Taches")) {
									if (xml.tokenType() == QXmlStreamReader::StartElement) {

										if (xml.name() == "TacheUnitaire") {
											qDebug() << "new tache\n";
											int id;
											QString titre;
											QDate dateDispo;
											QDate dateEcheance;
											Duree duree;

											xml.readNext();
											//We're going to loop over the things because the order might change.
											//We'll continue the loop until we hit an EndElement named TacheUnitaire.


											while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheUnitaire")) {
												if (xml.tokenType() == QXmlStreamReader::StartElement) {
													// We've found identificteur.
													if (xml.name() == "id") {
														xml.readNext(); id = xml.text().toString().toUInt();
														//qDebug()<<"id="<<identificateur<<"\n";
													}

													// We've found titre.
													if (xml.name() == "titre") {
														xml.readNext(); titre = xml.text().toString();
														//qDebug()<<"titre="<<titre<<"\n";
													}
													// We've found disponibilite
													if (xml.name() == "dateDispo") {
														xml.readNext();
														dateDispo = QDate::fromString(xml.text().toString(), Qt::ISODate);
														//qDebug()<<"disp="<<disponibilite.toString()<<"\n";
													}
													// We've found echeance
													if (xml.name() == "dateEcheance") {
														xml.readNext();
														dateEcheance = QDate::fromString(xml.text().toString(), Qt::ISODate);
														//qDebug()<<"echeance="<<echeance.toString()<<"\n";
													}
													// We've found duree
													if (xml.name() == "duree") {
														xml.readNext();
														duree.setDuree(xml.text().toString().toUInt());
														//qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
													}
												}
												// ...and next...
												xml.readNext();

											}
											//qDebug()<<"ajout tache "<<identificateur<<"\n";
											ProjetManager::getInstance().getProjet(nom).creerTache("TacheUnitaire", titre, dateDispo, dateEcheance, std::vector<Tache*>(), NULL, duree);

										}
										else {
											if (xml.name() == "TacheUnitairePreemptee") {
												qDebug() << "new tache\n";
												int id;
												QString titre;
												QDate dateDispo;
												QDate dateEcheance;
												Duree duree;
												Duree dureeEffectuee;

												xml.readNext();
												//We're going to loop over the things because the order might change.
												//We'll continue the loop until we hit an EndElement named TacheUnitaire.


												while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheUnitairePreemptee")) {
													if (xml.tokenType() == QXmlStreamReader::StartElement) {
														// We've found identificteur.
														if (xml.name() == "id") {
															xml.readNext(); id = xml.text().toString().toUInt();
															//qDebug()<<"id="<<identificateur<<"\n";
														}

														// We've found titre.
														if (xml.name() == "titre") {
															xml.readNext(); titre = xml.text().toString();
															//qDebug()<<"titre="<<titre<<"\n";
														}
														// We've found disponibilite
														if (xml.name() == "dateDispo") {
															xml.readNext();
															dateDispo = QDate::fromString(xml.text().toString(), Qt::ISODate);
															//qDebug()<<"disp="<<disponibilite.toString()<<"\n";
														}
														// We've found echeance
														if (xml.name() == "dateEcheance") {
															xml.readNext();
															dateEcheance = QDate::fromString(xml.text().toString(), Qt::ISODate);
															//qDebug()<<"echeance="<<echeance.toString()<<"\n";
														}
														// We've found duree
														if (xml.name() == "duree") {
															xml.readNext();
															duree.setDuree(xml.text().toString().toUInt());
															//qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
														}
														if (xml.name() == "dureeEffectuee") {
															xml.readNext();
															dureeEffectuee.setDuree(xml.text().toString().toUInt());
															//qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
														}
													}
													// ...and next...
													xml.readNext();

												}
												//qDebug()<<"ajout tache "<<identificateur<<"\n";
												Tache & t = ProjetManager::getInstance().getProjet(nom).creerTache("TacheUnitairePreemptee", titre, dateDispo, dateEcheance, std::vector<Tache*>(), NULL, duree);
												((TacheUnitairePreemptee&)t).addDureeEffectuee(dureeEffectuee);
											}
											else{
												if (xml.name() == "TacheComposite") {
													qDebug() << "new tache\n";
													int id;
													QString titre;
													QDate dateDispo;
													QDate dateEcheance;


													xml.readNext();
													//We're going to loop over the things because the order might change.
													//We'll continue the loop until we hit an EndElement named TacheUnitaire.


													while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheComposite")) {
														if (xml.tokenType() == QXmlStreamReader::StartElement) {
															// We've found identificteur.
															if (xml.name() == "id") {
																xml.readNext(); id = xml.text().toString().toUInt();
																//qDebug()<<"id="<<identificateur<<"\n";
															}

															// We've found titre.
															if (xml.name() == "titre") {
																xml.readNext(); titre = xml.text().toString();
																//qDebug()<<"titre="<<titre<<"\n";
															}
															// We've found disponibilite
															if (xml.name() == "dateDispo") {
																xml.readNext();
																dateDispo = QDate::fromString(xml.text().toString(), Qt::ISODate);
																//qDebug()<<"disp="<<disponibilite.toString()<<"\n";
															}
															// We've found echeance
															if (xml.name() == "dateEcheance") {
																xml.readNext();
																dateEcheance = QDate::fromString(xml.text().toString(), Qt::ISODate);
																//qDebug()<<"echeance="<<echeance.toString()<<"\n";
															}

														}
														// ...and next...
														xml.readNext();

													}
													//qDebug()<<"ajout tache "<<identificateur<<"\n";
													ProjetManager::getInstance().getProjet(nom).creerTache("TacheComposite", titre, dateDispo, dateEcheance, std::vector<Tache*>(), NULL);
												}
											}//fin du premier else
										}//fin du deuxieme else
										xml.readNext();
									}//fin de l'ajout d'une tache
									xml.readNext();
								}//fin de l'ajout des Taches
							}
							//on crée les dépendances entre les taches
							if (xml.name() == "Dependances")
							{
								qDebug() << "new dependance\n";
								xml.readNext();

								while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Dependances")) {
									if (xml.tokenType() == QXmlStreamReader::StartElement) {

										if ((xml.name() == "TacheUnitaire") || (xml.name() == "TacheUnitairePreemptee")) {
											qDebug() << "set dependance\n";
											int id;
											int parentid;
											Tache * parent;
											int idpre;
											Tache * temprerequis;
											std::vector<Tache*>prerequis;

											xml.readNext();
											//We're going to loop over the things because the order might change.
											//We'll continue the loop until we hit an EndElement named TacheUnitaire.


											while (!(xml.tokenType() == QXmlStreamReader::EndElement && ((xml.name() == "TacheUnitaire") || (xml.name() == "TacheUnitairePreemptee")))) {
												qDebug() << "trouve1\n";
												if (xml.tokenType() == QXmlStreamReader::StartElement) {
													qDebug() << "set dependance1 \n";
													// We've found identificteur.
													if (xml.name() == "id") {
														xml.readNext(); id = xml.text().toString().toUInt();
														//qDebug()<<"id="<<identificateur<<"\n";
													}

													// We've found titre.
													if (xml.name() == "parent") {
														xml.readNext(); parentid = xml.text().toString().toUInt();
														if (parentid != 0){
															parentid += ProjetManager::getInstance().getProjet(nom).getCurrentId();
															parent = &ProjetManager::getInstance().getProjet(nom).getTache(parentid);
														}
													}

													if (xml.name() == "prerequis") {
														xml.readNext();
														while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "prerequis")) {
															if (xml.tokenType() == QXmlStreamReader::StartElement) {
																if (xml.name() == "id") {
																	xml.readNext(); idpre = xml.text().toString().toUInt();
																	idpre += ProjetManager::getInstance().getProjet(nom).getCurrentId();
																	temprerequis = &ProjetManager::getInstance().getProjet(nom).getTache(idpre);
																	prerequis.push_back(temprerequis);
																}

															}
															xml.readNext();
														}

													}
												}
												// ...and next...
												xml.readNext();

											}
											//qDebug()<<"ajout tache "<<identificateur<<"\n";
											ProjetManager::getInstance().getProjet(nom).getTache(id).ajoutPrerequis(prerequis);
											ProjetManager::getInstance().getProjet(nom).getTache(id).setParent(parent);
											prerequis.clear();
										}
										else {
											if (xml.name() == "TacheComposite") {
												qDebug() << "set dependance2 \n";
												int id;
												int parentid;
												Tache * parent;
												int idpre;
												Tache * temprerequis;
												std::vector<Tache*> prerequis;
												int idsoustaches;
												Tache * soustache;
												std::vector<Tache*> soustaches;

												xml.readNext();
												//We're going to loop over the things because the order might change.
												//We'll continue the loop until we hit an EndElement named TacheUnitaire.


												while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheComposite")) {
													qDebug() << "trouve2";
													if (xml.tokenType() == QXmlStreamReader::StartElement) {
														// We've found identificteur.
														if (xml.name() == "id") {
															xml.readNext(); id = xml.text().toString().toUInt();
															qDebug() << "id est mis\n";
														}

														// We've found titre.
														if (xml.name() == "parent") {
															xml.readNext(); parentid = xml.text().toString().toUInt();
															qDebug() << "parent0 \n";
															if (parentid != 0){
																parentid += ProjetManager::getInstance().getProjet(nom).getCurrentId();
																parent = &ProjetManager::getInstance().getProjet(nom).getTache(parentid);
																qDebug() << "parent different 0 \n";
															}
														}

														if (xml.name() == "prerequis") {
															xml.readNext();
															while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "prerequis")) {
																if (xml.tokenType() == QXmlStreamReader::StartElement) {
																	qDebug() << "prerequis\n";
																	if (xml.name() == "id") {
																		xml.readNext(); idpre = xml.text().toString().toUInt();
																		idpre += ProjetManager::getInstance().getProjet(nom).getCurrentId();
																		temprerequis = &ProjetManager::getInstance().getProjet(nom).getTache(idpre);
																		prerequis.push_back(temprerequis);
																	}

																}
																xml.readNext();
															}

														}

														if (xml.name() == "sousTaches") {
															xml.readNext();
															while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "sousTaches")) {
																if (xml.tokenType() == QXmlStreamReader::StartElement) {
																	qDebug() << "soustache\n";
																	if (xml.name() == "id") {
																		qDebug() << "soustache2\n";
																		xml.readNext(); idsoustaches = xml.text().toString().toUInt();
																		idsoustaches += ProjetManager::getInstance().getProjet(nom).getCurrentId();
																		soustache = &ProjetManager::getInstance().getProjet(nom).getTache(idsoustaches);
																		soustaches.push_back(soustache);
																	}

																}
																xml.readNext();
															}

														}
														// ...and next..
													}
													xml.readNext();


												}
												qDebug() << "entré donné";
												ProjetManager::getInstance().getProjet(nom).getTache(id).ajoutPrerequis(prerequis);
												ProjetManager::getInstance().getProjet(nom).getTache(id).setParent(parent);
												dynamic_cast<TacheComposite*>(&ProjetManager::getInstance().getProjet(nom).getTache(id))->ajouterSousTaches(soustaches);
												qDebug() << "sorti donné";
												soustaches.clear();
												prerequis.clear();

											}

										}//fin de la dependance

									}//fin de l'ajout des Taches
									xml.readNext();
								}

							}

						}
						//fin des 2 elements
						// Error handling
						xml.readNext();
					}//fin du while
				}//test
			}
		}//fin du while fichier

		if (xml.hasError()) {
			QString str3 = "Erreur lecteur fichier taches parser xml";

			throw CalendarException(str3);
		}


		// Removes any device() or data from the reader * and resets its internal state to the initial state.
		xml.clear();
/*	}
	catch (CalendarException & e){
		QMessageBox::information(this, "erreur", e.getInfo());
	}*/
	//qDebug()<<"fin load\n";
}//fin de la lecture



