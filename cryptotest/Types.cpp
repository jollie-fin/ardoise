/*
 * Types.cpp
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */


#include "Types.h"
#include "Outil.h"
#include <string>
#include <sstream>
namespace Types
{
	bool Word512::operator==(const Word512& mdp) const
	{
		bool retour = true;
		for (int i=0; i<8; i++)
			retour = retour && (mdp.t[i] == t[i]);
		return retour;
	}

	Word512 mdp_inutile = Outil::hash("","");

	std::string Word512::to_string()
	{
		std::ostringstream flux;
		flux << std::setbase(16) << std::setfill(' ');
		for (int i=0; i<8; i++)
		{
			flux << std::setw(16) << t[i];
		}
		return flux.str();
	}

	Id::Id(const std::string &pprenom, const std::string &pnom)
	{
		nom = pnom;
		prenom = pprenom;
	}

	bool Id::operator==(const Id &id) const
	{
		return nom == id.nom && prenom == id.prenom;
	}

	bool Id::operator!=(const Id &id) const
	{
		return !(operator== (id));
	}

	bool Id::operator<(const Id &id) const
	{
		return nom<id.nom || (nom==id.nom && prenom<id.prenom);
	}

	bool Id::operator>=(const Id &id) const
	{
		return !(operator<(id));
	}
	bool Id::operator<=(const Id &id) const
	{
		return (operator<(id) && operator!=(id));
	}
	bool Id::operator>(const Id &id) const
	{
		return !(operator>(id));
	}

	std::string Id::to_string()const
	{
		return prenom + " " + nom;
	}
};

std::ostream &operator<<(std::ostream &out, Types::Id &id)
{
	return out<<id.to_string();
}

std::ostream &operator<<(std::ostream &out, Types::Word512 &w)
{
	return out<<w.to_string();
}
