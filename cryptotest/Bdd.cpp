/*
 * Bdd.cpp
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Bdd.h"
#include "Mouvement.h"
#include "Boisson.h"
#include "Etudiant.h"
#include "Types.h"
#include "Outil.h"



std::map<std::string, Boisson> Bdd::boissons;
std::map<Types::Id, Etudiant> Bdd::etudiants;

std::map<long,MouvementCredit> Bdd::credit;
std::map<long,MouvementDebit> Bdd::debit;
std::map<long,MouvementBoisson> Bdd::mvtboisson;
std::map<long,MouvementChangeEtudiant> Bdd::changeetudiant;
std::map<long,MouvementChangeBoisson> Bdd::changeboisson;

Boisson &Bdd::getboisson(const std::string &boisson)
{
	std::map<std::string, Boisson>::iterator it = boissons.find(boisson);
	if (it == boissons.end())
		throw std::string("Boisson ") + boisson + " inconnue";
	return it->second;
}

Etudiant &Bdd::getetudiant(const Types::Id &id)
{
	std::map<Types::Id, Etudiant>::iterator it = etudiants.find(id);
	if (it == etudiants.end())
		throw std::string("Etudiant ") + id.to_string() + " inconnu";
	return it->second;
}

Mouvement &Bdd::getmouvement(const long &id)
{
	std::ostringstream erreur;
	std::map<long, MouvementCredit>::iterator itcredit = credit.find(id);
	std::map<long, MouvementDebit>::iterator itdebit = debit.find(id);
	std::map<long, MouvementBoisson>::iterator itboisson = mvtboisson.find(id);
	std::map<long,MouvementChangeEtudiant>::iterator itchangeetudiant = changeetudiant.find(id);
	std::map<long,MouvementChangeBoisson>::iterator  itchangeboisson = changeboisson.find(id);

	if (itcredit != credit.end() && itdebit == debit.end() && itboisson == mvtboisson.end() && itchangeetudiant == changeetudiant.end() && itchangeboisson == changeboisson.end())
		return itcredit->second;
	else if (itcredit == credit.end() && itdebit != debit.end() && itboisson == mvtboisson.end() && itchangeetudiant == changeetudiant.end() && itchangeboisson == changeboisson.end())
		return itdebit->second;
	else if (itcredit == credit.end() && itdebit == debit.end() && itboisson != mvtboisson.end() && itchangeetudiant == changeetudiant.end() && itchangeboisson == changeboisson.end())
		return itboisson->second;
	else if (itcredit == credit.end() && itdebit == debit.end() && itboisson != mvtboisson.end() && itchangeetudiant != changeetudiant.end() && itchangeboisson == changeboisson.end())
		return itchangeetudiant->second;
	else if (itcredit == credit.end() && itdebit == debit.end() && itboisson != mvtboisson.end() && itchangeetudiant == changeetudiant.end() && itchangeboisson != changeboisson.end())
		return itchangeboisson->second;
	else if (itcredit == credit.end() && itdebit == debit.end() && itboisson == mvtboisson.end() && itchangeetudiant == changeetudiant.end() && itchangeboisson == changeboisson.end())
	{
		erreur << "Mouvement " << id << " inconnu";
		throw erreur.str();
	}
	else
	{
		erreur << "Duplicata de " << id;
		throw erreur.str();
	}
}

void Bdd::sauve_xml(const std::string &fichier)
{
	std::ofstream ofile(fichier.c_str());
	boost::archive::xml_oarchive oTextArchive(ofile);

	sauve_fichier(oTextArchive);
	ofile.close();
}

void Bdd::sauve_binaire(const std::string &fichier)
{
	std::ofstream ofile(fichier.c_str());
	boost::archive::binary_oarchive oTextArchive(ofile);

	sauve_fichier(oTextArchive);
	ofile.close();
}

void Bdd::charge_binaire(const std::string &fichier)
{
	std::ifstream ifile(fichier.c_str());
	boost::archive::binary_iarchive iTextArchive(ifile);
	Bdd bdd;
	iTextArchive >> BOOST_SERIALIZATION_NVP(bdd);    // sérialisation de d
}

