/*
 * Saisie_texte.h
 *
 *  Created on: 24 janv. 2011
 *      Author: phi
 */

#ifndef SAISIE_TEXTE_H_
#define SAISIE_TEXTE_H_

#include "Widget.h"
#include <string>

class Saisie_texte:public Widget {
	protected:
		bool m_secret;
		std::wstring m_chaine;
		bool m_reverse;
		int m_indice;
		int m_offset;
		wchar_t *m_buffer;
		int m_w;

	public:
		Saisie_texte(int w = 10, bool secret = false, std::wstring chaine = std::wstring(L""));
		bool secret();
		virtual int w() const;
		virtual int h() const;
		virtual void affiche(int x, int y);
		virtual bool gere_clavier(wint_t touche);
		const std::wstring &chaine() const;
		virtual ~Saisie_texte();
		static void toggle(Widget *appellant, int touche, void *widget);
};

#endif /* SAISIE_TEXTE_H_ */
