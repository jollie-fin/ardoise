/*
 * Etudiant.h
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#ifndef ETUDIANT_H_
#define ETUDIANT_H_

#include <string>
#include <list>
#include <iostream>
#include "Types.h"
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_oarchive.hpp>

class Mouvement;

class Etudiant
{
	private:
		long long m_solde;
		Types::Word512 m_mdp;
		Types::Id m_id;
		std::list<long> m_historique;
		bool m_rf;
		bool m_super_rf;
		void ajoute_mouvement(long);

	public:
		Etudiant(const Types::Id &id, long long solde = 0,  bool rf = false, bool admin = false);
		Etudiant();

		long long solde() const;
		const Types::Id &id() const;
		std::string mail() const;

		std::string to_string() const;
		const std::list<long> & historique() const;

		bool estce_mdp(const std::string &mdp) const;
		Types::Word512 hash(const std::string &mdp) const;
		void cree_etudiant(const Types::Id &id, long long solde);
		void change_rf(const Types::Id &id, bool rf);
		void credite(const Types::Id &id, long long montant);
		void consomme(const std::string &boisson);
		void change_mdp(const std::string &, const std::string &);
		void reinitialise_mdp_par_super_rf(const Types::Id &id);

		bool super_rf()const;
		bool rf()const;

		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(m_solde)
			   & BOOST_SERIALIZATION_NVP(m_mdp)
			   & BOOST_SERIALIZATION_NVP(m_id)
			   & BOOST_SERIALIZATION_NVP(m_historique)
			   & BOOST_SERIALIZATION_NVP(m_rf)
			   & BOOST_SERIALIZATION_NVP(m_super_rf);
		}
};

std::ostream &operator<<(std::ostream &out, Etudiant &etudiant);


#endif /* ETUDIANT_H_ */
