/*
 * Mouvement.cpp
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#include <ctime>
#include <sstream>
#include <string>
#include "Etudiant.h"
#include "Boisson.h"
#include "Mouvement.h"
#include "Outil.h"
#include "Types.h"
#include "Bdd.h"


Mouvement::Mouvement()
{
	m_date = std::time(NULL);
}

long Mouvement::date()
{
	return m_date;
}

long long Mouvement::montant() const
{
	return 0;
}

std::string Mouvement::boisson() const
{
	return std::string("");
}

Types::Id Mouvement::id() const
{
	return Types::Id();
}

std::string Mouvement::to_string(bool reduit, bool secret) const
{
	if (!reduit)
		return std::string(std::ctime(&m_date)) + ": ";
	else
		return "";
}

MouvementBoisson::MouvementBoisson(const std::string &boisson, long nombre,TypeBoisson type):Mouvement()
{
	m_boisson = boisson;
	m_nombre = nombre;
	m_type = type;
}

std::string MouvementBoisson::to_string(bool reduit, bool secret) const
{
	std::ostringstream flux;
	if (!secret)
	{
		flux << ((Mouvement*)this)->to_string(reduit,secret);
		switch (m_type)
		{
			case Reserve:
				flux << "Ajout de " << m_nombre << " " << Bdd::getboisson(m_boisson).nom() << " en reserve";
				break;

			case Frigo:
				flux << "Deplacement de " << m_nombre << " " << Bdd::getboisson(m_boisson).nom() << " au frigo";
				break;

			case Vol:
				flux << "Notification de " << m_nombre << " " << Bdd::getboisson(m_boisson).nom() << " volees";
				break;

			case Consigne:
				flux << m_nombre << " consignes de " << Bdd::getboisson(m_boisson).nom() << " rendues";
				break;
		}
	}
	return flux.str();
}

Mouvement::Type MouvementBoisson::type() const
{
	return ChangeBoisson;
}

std::string MouvementBoisson::boisson() const
{
	return m_boisson;
}

MouvementDebit::MouvementDebit(const std::string &boisson):Mouvement()
{
	m_boisson = boisson;
}

std::string MouvementDebit::to_string(bool reduit, bool secret) const
{
	std::ostringstream flux;
	flux << ((Mouvement*)this)->to_string(reduit,secret);
	flux << "Achat de " << Bdd::getboisson(m_boisson).nom() << ": " << Bdd::getboisson(m_boisson).prix();
	return flux.str();
}

Mouvement::Type MouvementDebit::type() const
{
	return Debit;
}


long long MouvementDebit::montant() const
{
	return Bdd::getboisson(m_boisson).prix();
}

std::string MouvementDebit::boisson() const
{
	return m_boisson;
}


MouvementCredit::MouvementCredit(const Types::Id &id, long long credit):Mouvement()
{
	m_id = id;
	m_credit = credit;
}

std::string MouvementCredit::to_string(bool reduit, bool secret) const
{
	std::ostringstream flux;
	flux << ((Mouvement*)this)->to_string(reduit,secret);
	flux << "Credit de " << Outil::currency(m_credit);
	if (!secret) flux << " par " << m_id.to_string();
	return flux.str();
}

Mouvement::Type MouvementCredit::type() const
{
	return Credit;
}

long long MouvementCredit::montant() const
{
	return -m_credit;
}

Types::Id MouvementCredit::id() const
{
	return m_id;
}

MouvementChangeBoisson::MouvementChangeBoisson(const std::string &boisson, TypeChange type, long prix)
{
	m_boisson = boisson;
	m_type = type;
	m_prix = prix;
}

std::string MouvementChangeBoisson::to_string(bool reduit, bool secret) const
{
	if (secret) return "";

	std::ostringstream flux;
	flux << ((Mouvement*)this)->to_string(reduit,secret);
	switch (m_type)
	{
		case Prix:
			flux << "Prix de " << m_boisson << " change pour " << Outil::currency(m_prix);
			break;

		case Active:
			flux << m_boisson << " visible";
			break;

		case Desactive:
			flux << m_boisson << " invisible";
			break;
	}
	return flux.str();
}

Mouvement::Type MouvementChangeBoisson::type() const
{
	return ChangeBoisson;
}

std::string MouvementChangeBoisson::boisson() const
{
	return m_boisson;
}

MouvementChangeEtudiant::MouvementChangeEtudiant(const Types::Id &etudiant_concerne, TypeChange type):Mouvement()
{
	m_etudiant_concerne = etudiant_concerne;
	m_type = type;
}

std::string MouvementChangeEtudiant::to_string(bool reduit, bool secret) const
{
	std::ostringstream flux;
	flux << ((Mouvement*)this)->to_string(reduit,secret);
	if (!secret)
	{
		switch(m_type)
		{
			case Creation:
				flux << "Creation de " << m_etudiant_concerne.to_string();
				break;

			case NommeRF:
				flux << m_etudiant_concerne.to_string() << " nomme RF";
				break;

			case DechuRF:
				flux << m_etudiant_concerne.to_string() << " n'est plus RF";
				break;

			case ReinitialiseMDP:
				flux << "Mot de passe de " << m_etudiant_concerne.to_string() << " reinitialise";
				break;
		}
	}
	return flux.str();
}

Mouvement::Type MouvementChangeEtudiant::type() const
{
	return Mouvement::ChangeEtudiant;
}

Types::Id MouvementChangeEtudiant::id() const
{
	return m_etudiant_concerne;
}

std::ostream &operator<<(std::ostream &out, Mouvement &mvt)
{
	return out << mvt.to_string();
}

