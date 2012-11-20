/*
 * Types.h
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#ifndef TYPES_H_
#define TYPES_H_
#include <crypto++/sha.h>
#include <utility>
#include <string>
#include <boost/archive/xml_oarchive.hpp>
namespace Types
{
	struct Word512
	{
		CryptoPP::word64 t[8];
		bool operator==(const Word512& mdp) const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			for (int i=0; i < 8; i++)
			{
				CryptoPP::word64 var=t[i];
				ar & BOOST_SERIALIZATION_NVP(var);
			}
		}
		std::string to_string();
	};
	extern Word512 mdp_inutile;

	struct Id
	{
		std::string nom;
		std::string prenom;

		Id(const std::string &pprenom = "", const std::string &pnom = "");
		bool operator==(const Id &) const;
		bool operator!=(const Id &) const;
		bool operator<=(const Id &) const;
		bool operator>=(const Id &) const;
		bool operator<(const Id &) const;
		bool operator>(const Id &) const;
		std::string to_string()const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(prenom) & BOOST_SERIALIZATION_NVP(nom);
		}
	};

}

std::ostream &operator<<(std::ostream &out, Types::Id &id);
std::ostream &operator<<(std::ostream &out, Types::Word512 &id);

#endif /* TYPES_H_ */
