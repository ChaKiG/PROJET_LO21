#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QMessageBox>

/*
* \file evenement.h
* \brief Contient Classe permettant la gestion d'une duree
* \author Thomas Pelletier, Paul Buzaud, Amélie Thery
* \version 1
* \date 07/06/2015
*/


/*! \class CalendarException
* \brief permet la gestion des exceptions dans le programme
*/
class CalendarException {
public:
	/*!
	*  \brief constructeur
	*  \param message : message a afficher
	*/
	CalendarException(const QString& message) :info(message){}  
	QString getInfo() const { return info; }                      //<!renvoit le titre de l'exception>

private:
	QString info;            //<!titre de l'exception>
};



#endif
