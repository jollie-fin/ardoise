/*
 * Boisson.h
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#ifndef BOISSON_H_
#define BOISSON_H_
#include <string>
#include <ctime>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_oarchive.hpp>

class Boisson
{
	private:
		std::string m_mere;
		std::string m_nom;
		long long m_prix;
		bool m_disponibilite;
		std::list<long> m_historique;
		time_t m_creation;
		long m_frigo;
		long m_reserve;
		long m_total;
		long m_consigne;
		long m_vol;
		long m_consomme;

	public:
		Boisson(const std::string &nom = "", long long prix = 0, const std::string &mere = "");
		bool disponible() const;
		std::string to_string(bool reduit = true, bool secret = false);
		long long prix() const;
		void setprix(long long prix);

		const std::string &nom() const;
		void setnom(const std::string &nom);
		void active();
		void desactive();
		template<class Archive> void serialize(Archive& ar, unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(m_nom);
			ar & BOOST_SERIALIZATION_NVP(m_mere);
			ar & BOOST_SERIALIZATION_NVP(m_prix);
			ar & BOOST_SERIALIZATION_NVP(m_disponibilite);
			ar & BOOST_SERIALIZATION_NVP(m_creation);
			ar & BOOST_SERIALIZATION_NVP(m_historique);
			ar & BOOST_SERIALIZATION_NVP(m_frigo);
			ar & BOOST_SERIALIZATION_NVP(m_total);
			ar & BOOST_SERIALIZATION_NVP(m_consigne);
			ar & BOOST_SERIALIZATION_NVP(m_vol);
			ar & BOOST_SERIALIZATION_NVP(m_reserve);
			ar & BOOST_SERIALIZATION_NVP(m_consomme);
		}

		long vol(long nb);
		long ajout_reserve(long nb);
		long ajout_frigo(long nb);
		long prend_une();
		long rend_consigne(long nb);

		bool operator==(const Boisson &boisson) const;
		bool operator!=(const Boisson &boisson) const;
		bool operator<(const Boisson &boisson) const;
		bool operator>(const Boisson &boisson) const;
		bool operator<=(const Boisson &boisson) const;
		bool operator>=(const Boisson &boisson) const;
};

std::ostream &operator<<(std::ostream &out, Boisson &boisson);

#endif /* BOISSON_H_ */
