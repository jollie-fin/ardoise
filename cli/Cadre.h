/*
 * Cadre.h
 *
 *  Created on: 27 janv. 2011
 *      Author: phi
 */

#ifndef CADRE_H_
#define CADRE_H_

#include "Widget.h"

class Cadre:public Widget {
	protected:
		Widget *m_contenu;
		bool m_gauche;
		bool m_droite;
		bool m_haut;
		bool m_bas;

	public:
		Cadre(Widget *contenu = NULL, bool gauche = false, bool droite = false, bool haut = false, bool bas = false);

		virtual ~Cadre();
		virtual bool gere_clavier(wint_t touche);
		virtual void affiche(int x, int y);
		virtual int w() const;
		virtual int h() const;

		bool getBas() const
		{
			return m_bas;
		}

		bool getDroite() const
		{
			return m_droite;
		}

		bool getGauche() const
		{
			return m_gauche;
		}

		bool getHaut() const
		{
			return m_haut;
		}

		void setBas(bool m_bas)
		{
			this->m_bas = m_bas;
		}

		void setDroite(bool m_droite)
		{
			this->m_droite = m_droite;
		}

		void setGauche(bool m_gauche)
		{
			this->m_gauche = m_gauche;
		}

		void setHaut(bool m_haut)
		{
			this->m_haut = m_haut;
		}

};

#endif /* CADRE_H_ */
