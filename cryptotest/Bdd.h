/*
 * Bdd.h
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#ifndef BDD_H_
#define BDD_H_

#include <map>
#include <string>
#include "Boisson.h"
#include "Etudiant.h"
#include "Mouvement.h"
#include "Types.h"
#include "Outil.h"
#include <boost/serialization/map.hpp>

class Bdd
{
	private:
		template<class Archive> static void sauve_fichier(Archive &ar)
		{
			ar.register_type(static_cast<MouvementCredit *>(NULL));
			ar.register_type(static_cast<MouvementDebit *>(NULL));
			ar.register_type(static_cast<MouvementBoisson *>(NULL));
			ar.register_type(static_cast<MouvementChangeBoisson *>(NULL));
			ar.register_type(static_cast<MouvementChangeEtudiant *>(NULL));

			boost::serialization::void_cast_register(static_cast<MouvementCredit *>(NULL),static_cast<Mouvement *>(NULL));
			boost::serialization::void_cast_register(static_cast<MouvementDebit *>(NULL),static_cast<Mouvement *>(NULL));
			boost::serialization::void_cast_register(static_cast<MouvementBoisson *>(NULL),static_cast<Mouvement *>(NULL));
			boost::serialization::void_cast_register(static_cast<MouvementChangeBoisson *>(NULL),static_cast<Mouvement *>(NULL));
			boost::serialization::void_cast_register(static_cast<MouvementChangeEtudiant *>(NULL),static_cast<Mouvement *>(NULL));

			Bdd bdd;
			ar << BOOST_SERIALIZATION_NVP(bdd);
		}
	public:
		static std::map<std::string,Boisson> boissons;
		static std::map<Types::Id,Etudiant> etudiants;
		static std::map<long,MouvementCredit> credit;
		static std::map<long,MouvementDebit> debit;
		static std::map<long,MouvementBoisson> mvtboisson;
		static std::map<long,MouvementChangeEtudiant> changeetudiant;
		static std::map<long,MouvementChangeBoisson> changeboisson;
		static Boisson &getboisson(const std::string &boisson);
		static Etudiant &getetudiant(const Types::Id &id);
		static Mouvement &getmouvement(const long &id);

		static void sauve_xml(const std::string &fichier);
		static void sauve_binaire(const std::string &fichier);

		static void charge_binaire(const std::string &fichier);

		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			using namespace Outil;
			ar & BOOST_SERIALIZATION_NVP(boissons);    // sérialisation de d
			ar & BOOST_SERIALIZATION_NVP(credit);
			ar & BOOST_SERIALIZATION_NVP(debit);
			ar & BOOST_SERIALIZATION_NVP(mvtboisson);
			ar & BOOST_SERIALIZATION_NVP(changeboisson);
			ar & BOOST_SERIALIZATION_NVP(changeetudiant);
			ar & BOOST_SERIALIZATION_NVP(etudiants);    // sérialisation de d
			ar & BOOST_SERIALIZATION_NVP(numid);    // sérialisation de d
		}
};

#endif /* BDD_H_ */
