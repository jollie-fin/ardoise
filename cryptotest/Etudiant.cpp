/*
 * Etudiant.cpp
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#include <string>
#include <iostream>
#include "Bdd.h"
#include "Types.h"
#include "Outil.h"
#include "Mouvement.h"
#include "Etudiant.h"

Etudiant::Etudiant(const Types::Id &id, long long solde, bool rf, bool super_rf)
{
		m_id = id;
		m_mdp = hash("");
		m_solde = -solde;
		m_rf = rf||super_rf;
		m_super_rf = super_rf;
}

Etudiant::Etudiant()
{
		m_id = Types::Id();
		m_mdp = hash("");
		m_solde = 0;
		m_rf = false;
		m_super_rf = false;
}

Types::Word512 Etudiant::hash(const std::string &mdp) const
{
	return Outil::hash(mdp,m_id.to_string());
}

long long Etudiant::solde() const
{
	return m_solde;
}

const Types::Id &Etudiant::id() const
{
	return m_id;
}

std::string Etudiant::mail() const
{
	return m_id.prenom + "." + m_id.nom + "@ens-lyon.fr";
}

std::string Etudiant::to_string() const
{
	return m_id.to_string() + ": " + Outil::currency(m_solde) + ((m_rf)?": rf":"");
}

const std::list<long> & Etudiant::historique() const
{
	return m_historique;
}

void Etudiant::change_mdp(const std::string &ancien_mdp, const std::string &nouveau_mdp)
{
	if (hash(ancien_mdp) == m_mdp)
		m_mdp = hash(nouveau_mdp);
	else
		throw "mot de passe invalide";
}

void Etudiant::reinitialise_mdp_par_super_rf(const Types::Id &id)
{
	if (m_super_rf)
	{
		Bdd::getetudiant(id).m_mdp = Bdd::getetudiant(id).hash("");

		long idnum = Outil::numid.alloue_id();
		MouvementChangeEtudiant mvt(id, MouvementChangeEtudiant::ReinitialiseMDP);
		Bdd::changeetudiant[idnum] = mvt;
		ajoute_mouvement(idnum);
	}
	else
		throw m_id.to_string() + " non super rf";
}

void Etudiant::cree_etudiant(const Types::Id &id, long long solde)
{
	if (m_rf)
	{
		if (Bdd::etudiants.find(id) == Bdd::etudiants.end()) //etudiant n'existe pas encore
		{
			Etudiant e(id,solde);
			Bdd::etudiants[id] = e;

			long idnum = Outil::numid.alloue_id();
			MouvementChangeEtudiant mvt(id, MouvementChangeEtudiant::Creation);
			Bdd::changeetudiant[idnum] = mvt;
			ajoute_mouvement(idnum);

			credite(id,solde);
		}
		else
		{
			throw std::string ("Etudiant ") + id.to_string() + " deja existant";
		}
	}
	else
		throw m_id.to_string() + " non RF";
}

void Etudiant::change_rf(const Types::Id &id, bool rf)
{
	if (m_super_rf)
	{
		Etudiant &e = Bdd::getetudiant(id);

		long idnum = Outil::numid.alloue_id();
		MouvementChangeEtudiant mvt(id, rf?MouvementChangeEtudiant::NommeRF:MouvementChangeEtudiant::DechuRF);
		Bdd::changeetudiant[idnum] = mvt;
		ajoute_mouvement(idnum);

		e.m_rf = rf;
	}
	else
		throw m_id.to_string() + " non RF";
}


void Etudiant::ajoute_mouvement(long idnum)
{
	m_historique.push_front(idnum);
	m_solde += Bdd::getmouvement(idnum).montant();
}

bool Etudiant::estce_mdp(const std::string &mdp) const
{
	return m_mdp == hash(mdp);
}

void Etudiant::credite(const Types::Id &id, long long montant)
{
	if (m_rf)
	{
		Etudiant &e = Bdd::getetudiant(id);
		long idnum = Outil::numid.alloue_id();
		MouvementCredit mvt(m_id, montant);
		Bdd::credit[idnum] = mvt;
		e.ajoute_mouvement(idnum);
	}
	else
		throw m_id.to_string() + " non RF";
}

void Etudiant::consomme(const std::string &boisson)
{
	long idnum = Bdd::getboisson(boisson).prend_une();
	ajoute_mouvement(idnum);
}

bool Etudiant::rf()const
{
	return m_rf;
}

bool Etudiant::super_rf()const
{
	return m_super_rf;
}

std::ostream &operator<<(std::ostream &out, Etudiant &etudiant)
{
	return out<<etudiant.to_string();
}

