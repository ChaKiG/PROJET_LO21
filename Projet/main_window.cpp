#include "main_window.h"

FenetreDepart::FenetreDepart(){
	layout = new QVBoxLayout;
	affichageEdt = new QPushButton("afficher Emploi du Temps");
	exportEdt = new QPushButton("exporter EdT");
	importEdt = new QPushButton("importer EdT");
	gestionProjet = new QPushButton("Gestion de Projets");
	exit = new QPushButton("Quitter");


	this->setLayout(layout);
	layout->addWidget(affichageEdt);
	layout->addWidget(exportEdt);
	layout->addWidget(importEdt);
	layout->addWidget(gestionProjet);
	layout->addWidget(exit);

	QObject::connect(exit, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(affichageEdt, SIGNAL(clicked()), this, SLOT(accesEdt()));
	QObject::connect(gestionProjet, SIGNAL(clicked()), this, SLOT(accesProjet()));
	QObject::connect(exportEdt, SIGNAL(clicked()), this, SLOT(save()));
	QObject::connect(importEdt, SIGNAL(clicked()), this, SLOT(load()));
}

void FenetreDepart::accesEdt(){
	ChoixSemaine * popup = new ChoixSemaine();
	popup->show();
}
void FenetreDepart::accesProjet(){
	GestionProj * popup = new GestionProj();
	popup->show();
}



void FenetreDepart::save(){

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
		stream.writeStartElement("ProjetManager");
		std::vector<Projet*> projets = ProjetManager::getInstance().getProjets();
		std::vector<Projet*>::iterator itpro = projets.begin();
		while (itpro != projets.end()){

			stream.writeStartElement("Projet");
			stream.writeAttribute("nom", (*itpro)->getTitre());
			stream.writeAttribute("debut", ProjetManager::getInstance().getProjet((*itpro)->getTitre()).getDebut().toString(Qt::ISODate));
			stream.writeAttribute("fin", ProjetManager::getInstance().getProjet((*itpro)->getTitre()).getFin().toString(Qt::ISODate));
			stream.writeStartElement("Taches");
			std::vector<Tache*> vectprojet = ProjetManager::getInstance().getProjet((*itpro)->getTitre()).getTaches();
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
			std::vector<Tache*> vectprojet1 = ProjetManager::getInstance().getProjet((*itpro)->getTitre()).getTaches();
			std::vector<Tache*>::iterator ite1 = vectprojet1.begin();
            while (ite1 != vectprojet1.end()){
				if (dynamic_cast<const TacheUnitairePreemptee*>(*ite1)){
					stream.writeStartElement("TacheUnitairePreemptee");
					stream.writeTextElement("id", QString::number((*ite1)->getId()));

					if (dynamic_cast<const TacheUnitaire*>(*ite1)->getParent() != NULL){
						QString str2;
						str2 = dynamic_cast<const TacheUnitaire*>(*ite1)->getParent()->getTitre();
						stream.writeTextElement("parent", str2);
					}
					else
						stream.writeTextElement("parent", "NULL");

					stream.writeStartElement("prerequis");
					const std::vector<Tache*> vectprerequis = dynamic_cast<const Tache*>(*ite1)->getPrerequis();

					for (std::vector<Tache*>::const_iterator it = vectprerequis.begin(); it<vectprerequis.end(); it++){

						stream.writeTextElement("id", (*it)->getTitre());
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
							str2 = dynamic_cast<const TacheUnitaire*>(*ite1)->getParent()->getTitre();
							stream.writeTextElement("parent", str2);
						}
						else
						{
							stream.writeTextElement("parent", "NULL");
						}
						stream.writeStartElement("prerequis");
						const std::vector<Tache*> vectprerequis = dynamic_cast<const Tache*>(*ite1)->getPrerequis();

						for (std::vector<Tache*>::const_iterator it = vectprerequis.begin(); it<vectprerequis.end(); it++)
						{

							stream.writeTextElement("id", (*it)->getTitre());
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
								str2 = dynamic_cast<const TacheComposite*>(*ite1)->getParent()->getTitre();
								stream.writeTextElement("parent", str2);
							}
							else
								stream.writeTextElement("parent", "NULL");

							stream.writeStartElement("prerequis");
							const std::vector<Tache*> vectprerequis = dynamic_cast<const Tache*>(*ite1)->getPrerequis();

							for (std::vector<Tache*>::const_iterator it = vectprerequis.begin(); it<vectprerequis.end(); it++){

								stream.writeTextElement("id", (*it)->getTitre());
							}

							stream.writeEndElement();
							stream.writeStartElement("sousTaches");
							const std::vector<Tache*> vectsoustaches = dynamic_cast<const TacheComposite*>(*ite1)->getSousTaches();

							for (std::vector<Tache*>::const_iterator it = vectsoustaches.begin(); it<vectsoustaches.end(); it++){

								stream.writeTextElement("id", (*it)->getTitre());
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

			itpro++;
		}


		std::vector<Programmation*> programmations = ProgrammationManager::getInstance().getProgrammations();
		std::vector<Programmation*>::iterator ite = programmations.begin();
		stream.writeStartElement("Programmations");
        while (ite != programmations.end()){
			const Evenement * event = (*ite)->getEvent();

			if (dynamic_cast<const TacheUnitairePreemptee*>(event)){
				stream.writeStartElement("TacheUnitairePreempte");
                stream.writeTextElement("Projet", ProjetManager::getInstance().getProjet((TacheUnitairePreemptee*)event).getTitre());
				stream.writeTextElement("id", QString::number(event->getId()));
				stream.writeTextElement("titre", event->getTitre());
				stream.writeTextElement("dateDispo", dynamic_cast<const TacheUnitairePreemptee*>(event)->getDateDisponibilite().toString(Qt::ISODate));
				stream.writeTextElement("dateEcheance", dynamic_cast<const TacheUnitairePreemptee*>(event)->getDateEcheance().toString(Qt::ISODate));

				QString str1;
				str1.setNum(dynamic_cast<const TacheUnitairePreemptee*>(event)->getDureeEffectuee().getDureeEnMinutes());
				stream.writeTextElement("dureeEffectuee", str1);
				stream.writeTextElement("dateChoisie", (*ite)->getDateChoisie().toString(Qt::ISODate));
				stream.writeTextElement("horaireChoisie", (*ite)->getHoraireChoisi().toString(Qt::ISODate));
				QString str2;
				str2.setNum((*ite)->getDuree().getDureeEnMinutes());
				stream.writeTextElement("duree", str2);

				stream.writeEndElement();
			}
			else {
				if (dynamic_cast<const TacheUnitaire*>(event)){
					stream.writeStartElement("TacheUnitaire");
					stream.writeTextElement("id", QString::number(event->getId()));
                    stream.writeTextElement("Projet", ProjetManager::getInstance().getProjet((TacheUnitairePreemptee*)event).getTitre());
                    stream.writeTextElement("titre", dynamic_cast<const TacheUnitaire*>(event)->getTitre());
					QString str;
					str.setNum(dynamic_cast<const TacheUnitaire*>(event)->getDuree().getDureeEnMinutes());
					stream.writeTextElement("dateChoisie", (*ite)->getDateChoisie().toString(Qt::ISODate));
					stream.writeTextElement("horaireChoisie", (*ite)->getHoraireChoisi().toString(Qt::ISODate));
					QString str1;
					str1.setNum((*ite)->getDuree().getDureeEnMinutes());
					stream.writeTextElement("duree", str1);

					stream.writeEndElement();
				}
				else{
					if (dynamic_cast<const Reunion*>(event)){
						stream.writeStartElement("Reunion");
						stream.writeTextElement("id", QString::number(event->getId()));
						stream.writeTextElement("titre", event->getTitre());
						stream.writeTextElement("lieu", dynamic_cast<const ActiviteTraditionnelle*>(event)->getLieu());
						stream.writeTextElement("dateChoisie", (*ite)->getDateChoisie().toString(Qt::ISODate));
						stream.writeTextElement("horaireChoisie", (*ite)->getHoraireChoisi().toString(Qt::ISODate));
						QString str1;
						str1.setNum((*ite)->getDuree().getDureeEnMinutes());
						stream.writeTextElement("duree", str1);
						stream.writeStartElement("Participants");
						const std::vector<QString> vectparticipants = dynamic_cast<const Reunion*>(event)->getParticipants();

						for (std::vector<QString>::const_iterator it = vectparticipants.begin(); it<vectparticipants.end(); it++)
						{

							stream.writeTextElement("id", (*it));
						}
						stream.writeEndElement();
						stream.writeEndElement();
					}
					else{
						if (dynamic_cast<const Rdv*>(event)){
							stream.writeStartElement("Rdv");
							stream.writeTextElement("id", QString::number(event->getId()));
							stream.writeTextElement("titre", event->getTitre());
							stream.writeTextElement("lieu", dynamic_cast<const ActiviteTraditionnelle*>(event)->getLieu());
							stream.writeTextElement("dateChoisie", (*ite)->getDateChoisie().toString(Qt::ISODate));
							stream.writeTextElement("horaireChoisie", (*ite)->getHoraireChoisi().toString(Qt::ISODate));
							QString str1;
							str1.setNum((*ite)->getDuree().getDureeEnMinutes());
							stream.writeTextElement("duree", str1);
							stream.writeTextElement("interlocuteur", dynamic_cast<const Rdv*>(event)->getInterlocuteur());
							stream.writeEndElement();
						}
					}
				}
			}
			ite++;
		}
		stream.writeEndElement();
		stream.writeEndElement();
		stream.writeEndDocument();
		newfile.close();
	}
	else{
		new GestionProj();
		close();
	}
}




void FenetreDepart::load()
{
	try{
		bool ok;
		const QString & text = QInputDialog::getText(this, tr("Nom du fichier"),
			tr("Rentrez le nom du fichier"), QLineEdit::Normal,
			QDir::home().dirName(), &ok);
		if (ok && !text.isEmpty()){

			file = text;
			QDate ddebutProj, dfinProj;
			QString strdebut, strfin;
			QString nomProj;
			QFile fin(file + ".xml");
			// If we can't open it, let's show an error message.
			if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
				throw CalendarException("Erreur ouverture fichier tâches");
			}
			// QXmlStreamReader takes any QIODevice.
			QXmlStreamReader xml(&fin);

			// We'll parse the XML until we reach end of it.
			while (!xml.atEnd() && !xml.hasError()) {

				// Read next element.
				QXmlStreamReader::TokenType token = xml.readNext();
				// If token is just StartDocument, we'll go to next.
				if (token == QXmlStreamReader::StartDocument) continue;
				// If token is StartElement, we'll see if we can read it.
				if (token == QXmlStreamReader::StartElement) {


					if (xml.name() == "ProjetManager") {

						while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ProjetManager")) {
							if (token == QXmlStreamReader::StartElement) {
								// If it's named projet, we'll create a project.
								if (xml.name() == "Projet") {
									QXmlStreamAttributes attributes = xml.attributes();
									if (attributes.hasAttribute("nom"))
									{
										nomProj = attributes.value("nom").toString();

									}
									if (attributes.hasAttribute("debut"))
									{
										strdebut = attributes.value("debut").toString();
										ddebutProj = QDate::fromString(strdebut, Qt::ISODate);
									}
									if (attributes.hasAttribute("fin"))
									{
										strfin = attributes.value("fin").toString();
										dfinProj = QDate::fromString(strfin, Qt::ISODate);
									}

									ProjetManager::getInstance().ajouterProjet(nomProj, ddebutProj, dfinProj);
									while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Projet")) {

										if (token == QXmlStreamReader::StartElement) {

											//on crée toutes les taches
											if (xml.name() == "Taches")
											{
												xml.readNext();

												while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Taches")) {
													if (xml.tokenType() == QXmlStreamReader::StartElement) {

														if (xml.name() == "TacheUnitaire") {

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

																	}

																	// We've found titre.
																	if (xml.name() == "titre") {
																		xml.readNext(); titre = xml.text().toString();

																	}
																	// We've found disponibilite
																	if (xml.name() == "dateDispo") {
																		xml.readNext();
																		dateDispo = QDate::fromString(xml.text().toString(), Qt::ISODate);

																	}
																	// We've found echeance
																	if (xml.name() == "dateEcheance") {
																		xml.readNext();
																		dateEcheance = QDate::fromString(xml.text().toString(), Qt::ISODate);

																	}
																	// We've found duree
																	if (xml.name() == "duree") {
																		xml.readNext();
																		duree.setDuree(xml.text().toString().toUInt());

																	}
																}
																// ...and next...
																xml.readNext();

															}
															//qDebug()<<"ajout tache "<<identificateur<<"\n";
															ProjetManager::getInstance().getProjet(nomProj).creerTache("TacheUnitaire", titre, dateDispo, dateEcheance, std::vector<Tache*>(), NULL, duree);

														}
														else {
															if (xml.name() == "TacheUnitairePreemptee") {

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

																		}

																		// We've found titre.
																		if (xml.name() == "titre") {
																			xml.readNext(); titre = xml.text().toString();

																		}
																		// We've found disponibilite
																		if (xml.name() == "dateDispo") {
																			xml.readNext();
																			dateDispo = QDate::fromString(xml.text().toString(), Qt::ISODate);

																		}
																		// We've found echeance
																		if (xml.name() == "dateEcheance") {
																			xml.readNext();
																			dateEcheance = QDate::fromString(xml.text().toString(), Qt::ISODate);

																		}
																		// We've found duree
																		if (xml.name() == "duree") {
																			xml.readNext();
																			duree.setDuree(xml.text().toString().toUInt());

																		}
																		if (xml.name() == "dureeEffectuee") {
																			xml.readNext();
																			dureeEffectuee.setDuree(xml.text().toString().toUInt());

																		}
																	}
																	// ...and next...
																	xml.readNext();

																}
																//qDebug()<<"ajout tache "<<identificateur<<"\n";
																Tache & t = ProjetManager::getInstance().getProjet(nomProj).creerTache("TacheUnitairePreemptee", titre, dateDispo, dateEcheance, std::vector<Tache*>(), NULL, duree);
																((TacheUnitairePreemptee&)t).addDureeEffectuee(dureeEffectuee);
															}
															else{
																if (xml.name() == "TacheComposite") {

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

																			}

																			// We've found titre.
																			if (xml.name() == "titre") {
																				xml.readNext(); titre = xml.text().toString();

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
																	ProjetManager::getInstance().getProjet(nomProj).creerTache("TacheComposite", titre, dateDispo, dateEcheance, std::vector<Tache*>(), NULL);
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

												xml.readNext();

												while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Dependances")) {
													if (xml.tokenType() == QXmlStreamReader::StartElement) {

														if ((xml.name() == "TacheUnitaire") || (xml.name() == "TacheUnitairePreemptee")) {

															int id;
															QString parentid;
															Tache * parent = NULL;
															QString idpre = 0;
															Tache * temprerequis;
															std::vector<Tache*>prerequis;

															xml.readNext();
															//We're going to loop over the things because the order might change.
															//We'll continue the loop until we hit an EndElement named TacheUnitaire.


															while (!(xml.tokenType() == QXmlStreamReader::EndElement && ((xml.name() == "TacheUnitaire") || (xml.name() == "TacheUnitairePreemptee")))) {

																if (xml.tokenType() == QXmlStreamReader::StartElement) {

																	// We've found identificteur.
																	if (xml.name() == "id") {
																		xml.readNext(); id = xml.text().toString().toUInt();
																		//qDebug()<<"id="<<identificateur<<"\n";
																	}

																	// We've found titre.
																	if (xml.name() == "parent") {
																		xml.readNext(); parentid = xml.text().toString();
																		if (parentid != "NULL"){
																			parent = &ProjetManager::getInstance().getProjet(nomProj).getTache(parentid);
																		}
																	}

																	if (xml.name() == "prerequis") {
																		xml.readNext();
																		while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "prerequis")) {
																			if (xml.tokenType() == QXmlStreamReader::StartElement) {
																				if (xml.name() == "id") {
																					xml.readNext(); idpre = xml.text().toString();

																					temprerequis = &ProjetManager::getInstance().getProjet(nomProj).getTache(idpre);
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
															ProjetManager::getInstance().getProjet(nomProj).getTache(id).ajoutPrerequis(prerequis);
															if (parent)
															{
																ProjetManager::getInstance().getProjet(nomProj).getTache(id).setParent(parent);
															}
															prerequis.clear();
														}
														else {
															if (xml.name() == "TacheComposite") {

																int id;
																QString parentid;
																Tache * parent = NULL;
																QString idpre = 0;
																Tache * temprerequis;
																std::vector<Tache*> prerequis;
																QString idsoustaches = 0;
																Tache * soustache;
																std::vector<Tache*> soustaches;

																xml.readNext();
																//We're going to loop over the things because the order might change.
																//We'll continue the loop until we hit an EndElement named TacheUnitaire.


																while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheComposite")) {

																	if (xml.tokenType() == QXmlStreamReader::StartElement) {
																		// We've found identificteur.
																		if (xml.name() == "id") {
																			xml.readNext(); id = xml.text().toString().toUInt();

																		}

																		// We've found titre.
																		if (xml.name() == "parent") {
																			xml.readNext(); parentid = xml.text().toString();

																			if (parentid != "NULL"){
																				parent = &ProjetManager::getInstance().getProjet(nomProj).getTache(parentid);

																			}
																		}

																		if (xml.name() == "prerequis") {
																			xml.readNext();
																			while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "prerequis")) {
																				if (xml.tokenType() == QXmlStreamReader::StartElement) {

																					if (xml.name() == "id") {
																						xml.readNext(); idpre = xml.text().toString();

																						temprerequis = &ProjetManager::getInstance().getProjet(nomProj).getTache(idpre);
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

																					if (xml.name() == "id") {

																						xml.readNext(); idsoustaches = xml.text().toString();


																						soustache = &ProjetManager::getInstance().getProjet(nomProj).getTache(idsoustaches);
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

																ProjetManager::getInstance().getProjet(nomProj).getTache(id).ajoutPrerequis(prerequis);
																if (parent)
																{
																	ProjetManager::getInstance().getProjet(nomProj).getTache(id).setParent(parent);
																}
																dynamic_cast<TacheComposite*>(&ProjetManager::getInstance().getProjet(nomProj).getTache(id))->ajouterSousTaches(soustaches);

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

							//fin du while fichier

							if (xml.name() == "Programmations") {
								while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Programmations")) {
									if (token == QXmlStreamReader::StartElement) {

										// If it's named projet, we'll create a project.
										if (xml.name() == "TacheUnitaire") {

											int id;
											Tache * tache;
                                            QString projet;
											QString titre;
											QDate dateChoisie;
											QTime HoraireChoisi;
											Duree duree;

											xml.readNext();
											//We're going to loop over the things because the order might change.
											//We'll continue the loop until we hit an EndElement named TacheUnitaire.


											while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheUnitaire")) {
												if (xml.tokenType() == QXmlStreamReader::StartElement) {
													// We've found identificteur.
                                                    if (xml.name() == "id") {
                                                        qDebug() << "iduni0";
														xml.readNext(); id = xml.text().toString().toUInt();
                                                        qDebug() << "iduni";

													}
                                                    if (xml.name() == "Projet") {
                                                        qDebug() << "iduni0";
                                                        xml.readNext(); projet = xml.text().toString().toUInt();
                                                        qDebug() << "iduni";
                                                    }
													// We've found titre.
													if (xml.name() == "titre") {
														xml.readNext(); titre = xml.text().toString();

													}
													// We've found disponibilite
													if (xml.name() == "dateChoisie") {
														xml.readNext();
														dateChoisie = QDate::fromString(xml.text().toString(), Qt::ISODate);

													}
													// We've found echeance
													if (xml.name() == "horaireChoisie") {
														xml.readNext();
														HoraireChoisi = QTime::fromString(xml.text().toString(), Qt::ISODate);

													}
													// We've found duree
													if (xml.name() == "duree") {
														xml.readNext();
														duree.setDuree(xml.text().toString().toUInt());
													}
												}
												// ...and next...
												xml.readNext();

											}
                                            tache = &ProjetManager::getInstance().getProjet(projet).getTache(titre);
											//qDebug()<<"ajout tache "<<identificateur<<"\n";
											ProgrammationManager::getInstance().creerProgrammation(tache, dateChoisie, HoraireChoisi);

										}
										else {
											if (xml.name() == "TacheUnitairePreempte") {


												int id;
												Tache * tache;
                                                QString projet;
												QString titre;
												QDate dateChoisie;
												QTime HoraireChoisi;
												Duree duree;

												xml.readNext();
												//We're going to loop over the things because the order might change.
												//We'll continue the loop until we hit an EndElement named TacheUnitaire.


												while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "TacheUnitairePreempte")) {
													if (xml.tokenType() == QXmlStreamReader::StartElement) {
														// We've found identificteur.
														if (xml.name() == "id") {
															qDebug() << "id1";
															xml.readNext(); id = xml.text().toString().toUInt();
                                                            qDebug() << "idpreempte";

														}
                                                        if (xml.name() == "Projet") {
                                                            qDebug() << "iduni0";
                                                            xml.readNext(); projet = xml.text().toString().toUInt();
                                                            qDebug() << "iduni";
                                                        }
														// We've found titre.
														if (xml.name() == "titre") {
															xml.readNext(); titre = xml.text().toString();

														}
														// We've found disponibilite
														if (xml.name() == "dateChoisie") {
															xml.readNext();
															dateChoisie = QDate::fromString(xml.text().toString(), Qt::ISODate);

														}
														// We've found echeance
														if (xml.name() == "horaireChoisie") {
															xml.readNext();
															HoraireChoisi = QTime::fromString(xml.text().toString(), Qt::ISODate);

														}
														// We've found duree
														if (xml.name() == "duree") {
															xml.readNext();
															duree.setDuree(xml.text().toString().toUInt());
														}
													}
													// ...and next...
													xml.readNext();

												}
												//qDebug()<<"ajout tache "<<identificateur<<"\n";
                                                tache = &ProjetManager::getInstance().getProjet(projet).getTache(titre);
                                                ProgrammationManager::getInstance().creerProgrammation(tache, dateChoisie, HoraireChoisi);

											}
											else{
												if (xml.name() == "Rdv") {


													int id;
													QString titre;
													QString lieu;
													QString interlocuteur;
													QDate dateChoisie;
													QTime HoraireChoisi;
													Duree duree;

													xml.readNext();
													//We're going to loop over the things because the order might change.
													//We'll continue the loop until we hit an EndElement named TacheUnitaire.


													while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Rdv")) {
														if (xml.tokenType() == QXmlStreamReader::StartElement) {
															// We've found identificteur.
															if (xml.name() == "id") {
																xml.readNext(); id = xml.text().toString().toUInt();
																qDebug() << "idrdv";


															}

															// We've found titre.
															if (xml.name() == "titre") {
																xml.readNext(); titre = xml.text().toString();

															}
															if (xml.name() == "lieu") {
																xml.readNext(); lieu = xml.text().toString();

															}
															if (xml.name() == "interlocuteur") {
																xml.readNext(); interlocuteur = xml.text().toString();

															}
															// We've found disponibilite
															if (xml.name() == "dateChoisie") {
																xml.readNext();
																dateChoisie = QDate::fromString(xml.text().toString(), Qt::ISODate);

															}
															// We've found echeance
															if (xml.name() == "horaireChoisie") {
																xml.readNext();
																HoraireChoisi = QTime::fromString(xml.text().toString(), Qt::ISODate);

															}
															// We've found duree
															if (xml.name() == "duree") {
																xml.readNext();
																duree.setDuree(xml.text().toString().toUInt());
															}
														}
														// ...and next...
														xml.readNext();

													}
													//qDebug()<<"ajout tache "<<identificateur<<"\n";
													Rdv * rdv = new Rdv(titre, duree, lieu, interlocuteur);
													ProgrammationManager::getInstance().creerProgrammation(rdv, dateChoisie, HoraireChoisi);

												}
												else
												{
													if (xml.name() == "Reunion") {


														int id;
														QString titre;
														QString lieu;
														QString personne;
														std::vector<QString> personnes;
														QDate dateChoisie;
														QTime HoraireChoisi;
														Duree duree;

														xml.readNext();
														//We're going to loop over the things because the order might change.
														//We'll continue the loop until we hit an EndElement named TacheUnitaire.


														while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Reunion")) {
															if (xml.tokenType() == QXmlStreamReader::StartElement) {
																// We've found identificteur.
																if (xml.name() == "id") {
																	qDebug() << "idreu";
																	xml.readNext(); id = xml.text().toString().toUInt();

																	qDebug() << "idreu";
																}

																// We've found titre.
																if (xml.name() == "titre") {
																	xml.readNext(); titre = xml.text().toString();
																	qDebug() << titre;
																}
																if (xml.name() == "lieu") {
																	qDebug() << "lieu";
																	xml.readNext(); lieu = xml.text().toString();
																	qDebug() << lieu;

																}

																// We've found disponibilite
																if (xml.name() == "dateChoisie") {
																	xml.readNext();
																	qDebug() << "date";
																	dateChoisie = QDate::fromString(xml.text().toString(), Qt::ISODate);

																}
																// We've found echeance
																if (xml.name() == "horaireChoisie") {
																	xml.readNext();

																	HoraireChoisi = QTime::fromString(xml.text().toString(), Qt::ISODate);

																}
																// We've found duree
																if (xml.name() == "duree") {
																	xml.readNext();
																	duree.setDuree(xml.text().toString().toUInt());
																}
																if (xml.name() == "Participants"){
																	xml.readNext();

																	while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Participants")) {
																		if (xml.tokenType() == QXmlStreamReader::StartElement) {
																			if (xml.name() == "id") {

																				xml.readNext(); personne = xml.text().toString();

																				personnes.push_back(personne);

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
														qDebug() << "part3";
														Reunion * reunion = new Reunion(titre, duree, lieu, personnes);
														qDebug() << "part6";
														ProgrammationManager::getInstance().creerProgrammation(reunion, dateChoisie, HoraireChoisi);
														qDebug() << "part5";
													}
												}//fin du premier else

											}//fin deuxieme else

										}//fin du troisieme else
									}
									xml.readNext();
								}


							}
							xml.readNext();
						}

					}

				}
				xml.readNext();
			}

			if (xml.hasError()) {
				QString str3 = "Erreur lecteur fichier taches parser xml";

				throw CalendarException(str3);
			}
			// Removes any device() or data from the reader * and resets its internal state to the initial state.
			xml.clear();
		}
	}
	catch (CalendarException & e){
		QMessageBox::information(this, "erreur", e.getInfo());
    }

}//fin de la lecture



FenetreDepart::~FenetreDepart(){
	delete importEdt;
	delete layout;
	delete affichageEdt;
	delete exportEdt;
	delete gestionProjet;
	delete exit;
    ProgrammationManager::libererInstance();
    ProjetManager::libererInstance();
}

