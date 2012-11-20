/*
 * Boisson.cpp
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#include <sstream>
#include <string>
#include <ctime>
#include "Outil.h"
#include "Boisson.h"
#include "Mouvement.h"
#include "Bdd.h"

Boisson::Boisson(const std::string &nom, long long prix, const std::string &mere)
{
	m_nom = nom;
	m_prix = prix;
	m_disponibilite = true;
	m_creation = std::time(NULL);
	m_total = 0;
	m_consomme = 0;
	m_consigne = 0;
	m_frigo = 0;
	m_vol = 0;
	m_reserve = 0;
	m_mere = mere;
}

bool Boisson::disponible() const
{
	return m_disponibilite;
}

std::string Boisson::to_string(bool reduit, bool secret)
{
	std::ostringstream flux;
	if (!reduit) flux << "creation " << std::ctime(&m_creation) << ": ";
	if (!secret) flux << "frigo " << m_frigo << ": reserve " << m_reserve << ": consignes presentes " << m_consigne << ": vol:consomme/total " << m_vol << ":" << m_consomme << "/" << m_total;
	flux << m_nom << ": " << Outil::currency(m_prix);
	if (!m_disponibilite) flux << ": non disponible";
	return flux.str();
}

const std::string &Boisson::nom() const
{
	return m_nom;
}

void Boisson::setnom(const std::string &nom)
{
	m_nom = nom;
}

long long Boisson::prix() const
{
	return m_prix;
}

void Boisson::setprix(long long prix)
{
	MouvementChangeBoisson mvt(m_nom,  MouvementChangeBoisson::Prix, prix);
	long idnum = Outil::numid.alloue_id();
	Bdd::changeboisson[idnum] = mvt;
	m_prix = prix;
}

void Boisson::active()
{
	MouvementChangeBoisson mvt(m_nom,  MouvementChangeBoisson::Active);
	long idnum = Outil::numid.alloue_id();
	Bdd::changeboisson[idnum] = mvt;
	m_disponibilite = true;
}


void Boisson::desactive()
{
	MouvementChangeBoisson mvt(m_nom,  MouvementChangeBoisson::Desactive);
	long idnum = Outil::numid.alloue_id();
	Bdd::changeboisson[idnum] = mvt;
	m_disponibilite = false;
}

long Boisson::rend_consigne(long nb)
{
	MouvementBoisson mvt(m_nom, nb, MouvementBoisson::Consigne);
	long idnum = Outil::numid.alloue_id();
	Bdd::mvtboisson[idnum] = mvt;
	m_historique.push_front(idnum);
	m_consigne -= nb;
	return idnum;
}

long Boisson::vol(long nb)
{
	MouvementBoisson mvt(m_nom, nb, MouvementBoisson::Vol);
	long idnum = Outil::numid.alloue_id();
	Bdd::mvtboisson[idnum] = mvt;
	m_historique.push_front(idnum);
	m_vol += nb;
	m_frigo -= nb;
	return idnum;
}

long Boisson::ajout_reserve(long nb)
{
	MouvementBoisson mvt(m_nom, nb, MouvementBoisson::Reserve);
	long idnum = Outil::numid.alloue_id();
	Bdd::mvtboisson[idnum] = mvt;
	m_historique.push_front(idnum);
	m_total += nb;
	m_reserve += nb;
	return idnum;
}

long Boisson::ajout_frigo(long nb)
{
	MouvementBoisson mvt(m_nom, nb, MouvementBoisson::Frigo);
	long idnum = Outil::numid.alloue_id();
	Bdd::mvtboisson[idnum] = mvt;
	m_historique.push_front(idnum);
	m_frigo += nb;
	m_reserve -= nb;
	return idnum;
}

long Boisson::prend_une()
{
	MouvementDebit mvt(m_nom);
	long idnum = Outil::numid.alloue_id();
	Bdd::debit[idnum] = mvt;
	m_historique.push_front(idnum);
	m_frigo--;
	m_consomme++;
	return idnum;
}

bool Boisson::operator==(const Boisson &boisson) const
{
	return m_nom == boisson.m_nom;
}

bool Boisson::operator!=(const Boisson &boisson) const
{
	return m_nom != boisson.m_nom;
}

bool Boisson::operator<(const Boisson &boisson) const
{
	return m_nom < boisson.m_nom;
}

bool Boisson::operator>(const Boisson &boisson) const
{
	return m_nom > boisson.m_nom;
}

bool Boisson::operator<=(const Boisson &boisson) const
{
	return m_nom <= boisson.m_nom;
}

bool Boisson::operator>=(const Boisson &boisson) const
{
	return m_nom >= boisson.m_nom;
}

std::ostream &operator<<(std::ostream &out, Boisson &boisson)
{
	return out << boisson.to_string();
}
