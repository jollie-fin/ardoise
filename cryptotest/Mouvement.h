/*
 * Mouvement.h
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#ifndef MOUVEMENT_H_
#define MOUVEMENT_H_

#include <string>
#include "Types.h"
#include <boost/archive/xml_oarchive.hpp>

class Mouvement
{
	friend class boost::serialization::access;
	private:
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(m_date);
		}

	protected:
		long m_date;

	public:
		enum Type{Debit,Credit,Boisson,ChangeBoisson,ChangeEtudiant};
		Mouvement();
		virtual std::string to_string(bool reduit = true, bool secret = true) const;
		virtual Type type() const = 0;
		virtual long long montant() const;
		long date();
		virtual std::string boisson() const;
		virtual Types::Id id() const;
};

class MouvementDebit:public Mouvement
{
	friend class boost::serialization::access;

	protected:
		std::string m_boisson;

	public:
		MouvementDebit(const std::string &boisson = "");
		virtual std::string to_string(bool reduit = true, bool secret = true) const;
		virtual Type type() const;
		virtual long long montant() const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("mere",boost::serialization::base_object<Mouvement>(*this));
			ar & BOOST_SERIALIZATION_NVP(m_boisson);
		}
		virtual std::string boisson() const;
};

class MouvementBoisson:public Mouvement
{
	friend class boost::serialization::access;
	public:
		enum TypeBoisson{Vol,Reserve,Frigo,Consigne};

	protected:
		std::string m_boisson;
		TypeBoisson m_type;
		long m_nombre;

	public:
		MouvementBoisson(const std::string &boisson = "", long nombre = 0, TypeBoisson type = Reserve);
		virtual std::string to_string(bool reduit = true, bool secret = true) const;
		virtual Type type() const;
		virtual std::string boisson() const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("mere",boost::serialization::base_object<Mouvement>(*this));
			ar & BOOST_SERIALIZATION_NVP(m_boisson);
			ar & BOOST_SERIALIZATION_NVP(m_type);
			ar & BOOST_SERIALIZATION_NVP(m_nombre);
		}
};

class MouvementChangeBoisson:public Mouvement
{
	friend class boost::serialization::access;
	public:
		enum TypeChange{Active,Desactive,Prix};

	protected:
		std::string m_boisson;
		long m_prix;
		TypeChange m_type;

	public:
		MouvementChangeBoisson(const std::string &boisson = "", TypeChange type = Active, long prix = 0);
		virtual std::string to_string(bool reduit = true, bool secret = true) const;
		virtual Type type() const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("mere",boost::serialization::base_object<Mouvement>(*this));
			ar & BOOST_SERIALIZATION_NVP(m_boisson);
			ar & BOOST_SERIALIZATION_NVP(m_prix);
			ar & BOOST_SERIALIZATION_NVP(m_type);
		}
		virtual std::string boisson() const;
};

class MouvementChangeEtudiant:public Mouvement
{
	friend class boost::serialization::access;
	public:
		enum TypeChange{Creation,NommeRF,DechuRF,ReinitialiseMDP};

	protected:
		Types::Id m_etudiant_concerne;
		TypeChange m_type;

	public:
		MouvementChangeEtudiant(const Types::Id &etudiant_concerne = Types::Id(), TypeChange type = Creation);
		virtual std::string to_string(bool reduit = true, bool secret = true) const;
		virtual Type type() const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("mere",boost::serialization::base_object<Mouvement>(*this));
			ar & BOOST_SERIALIZATION_NVP(m_etudiant_concerne);
			ar & BOOST_SERIALIZATION_NVP(m_type);
		}
		virtual Types::Id id() const;
};

class MouvementCredit:public Mouvement
{
	friend class boost::serialization::access;
	protected:
		Types::Id m_id;
		long long m_credit;

	public:
		MouvementCredit(const Types::Id &id = Types::Id(), long long credit = 0);
		virtual std::string to_string(bool reduit = true, bool secret = true) const;
		virtual Type type() const;
		virtual long long montant() const;
		template<class Archive> void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("mere",boost::serialization::base_object<Mouvement>(*this));
			ar & BOOST_SERIALIZATION_NVP(m_id);
			ar & BOOST_SERIALIZATION_NVP(m_credit);
		}
		virtual Types::Id id() const;
};

std::ostream &operator<<(std::ostream &out, Mouvement &mvt);

#endif /* MOUVEMENT_H_ */
