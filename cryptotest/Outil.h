/*
 * Outil.h
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#ifndef OUTIL_H_
#define OUTIL_H_
#include <string>
#include "Types.h"

namespace Outil
{
	std::string currency(long long montant);
	Types::Word512 hash(const std::string &mdp,const std::string &salt);

	class NumId
	{
		private:
			long m_id_courant;

		public:
			NumId();
			const long &alloue_id();
			template<class Archive> void serialize(Archive& ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(m_id_courant);
			}
	};
	extern NumId numid;

};

#endif /* OUTIL_H_ */
