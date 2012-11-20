/*
 * Outil.cpp
 *
 *  Created on: 13 janv. 2011
 *      Author: phi
 */

#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "Outil.h"
#include "Types.h"

namespace Outil
{
	std::string currency(long long valeur)
	{
		std::ostringstream flux;
		flux << valeur/100 << "." << std::setw(2) << std::setfill('0') << valeur%100 << "€";
		return flux.str();
	}

	Types::Word512 hash(const std::string &mdp,const std::string &salt)
	{
		Types::Word512 w;
		CryptoPP::SHA512 gen;
		CryptoPP::word64 entree[16] = {0};
		gen.InitState(w.t);

		for (int i=0; i<std::min(128,(int) mdp.length()); i++)
		{
			entree[i/8]=mdp[i]<<i%8;
		}
		for (int i=0; i<std::min(128,(int) salt.length()); i++)
		{
			entree[i/8]^=(salt[i]<<i%8);
		}

		for (int i=0; i<100000; i++)
		{
			gen.Transform(w.t,entree);
		}
		std::cout << w << std::endl;
		return w;
	}

	NumId::NumId()
	{
		m_id_courant = 0;
	}

	const long &NumId::alloue_id()
	{
		m_id_courant++;
		return m_id_courant;
	}

	NumId numid = NumId();
}
