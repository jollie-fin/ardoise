/*
 * Cadre.cpp
 *
 *  Created on: 27 janv. 2011
 *      Author: phi
 */

#include "Cadre.h"
#include <ncursesw/ncurses.h>
Cadre::Cadre(Widget *contenu, bool gauche, bool droite, bool haut, bool bas) {
	m_contenu = contenu;
	m_gauche = gauche;
	m_droite = droite;
	m_haut = haut;
	m_bas = bas;
}

Cadre::~Cadre() {

}

bool Cadre::gere_clavier(wint_t touche)
{
	bool b = false;
	b = Widget::gere_clavier(touche);
	if (!b)
	{
		if (m_contenu)
			return m_contenu->gere_clavier(touche);
		else
			return false;
	}
	else
		return false;
}

void Cadre::affiche(int x, int y)
{
	if (m_contenu)
	{
		m_contenu->affiche(x+m_gauche, y+m_haut);
		int w = m_contenu->w();
		int h = m_contenu->h();

		if (m_haut)
		{
			if (m_gauche)
				mvprintw (y,x,"%c",'+');
			for (int i = 0; i < w; i++)
				mvprintw (y,x+i+m_gauche,"%c",'-');
			if (m_droite)
				mvprintw (y,x+w+m_gauche,"%c",'+');
		}

		if (m_bas)
		{
			if (m_gauche)
				mvprintw (y+h+m_haut,x,"%c",'+');
			for (int i = 0; i < w; i++)
				mvprintw (y+h+m_haut,x+i+m_gauche,"%c",'-');
			if (m_droite)
				mvprintw (y+h+m_haut,x+w+m_gauche,"%c",'+');
		}

		if (m_gauche)
		{
			for (int i = 0; i < h; i++)
				mvprintw (y+i+m_haut,x,"%c",'|');
		}

		if (m_droite)
		{
			for (int i = 0; i < h; i++)
				mvprintw (y+i+m_haut,x+w+m_gauche,"%c",'|');
		}
	}
	else
	{
		mvprintw(x,y,"#");
	}
}

int Cadre::w() const
{
	if (m_contenu)
		return m_contenu->w() + m_gauche + m_droite;
	else
		return 1;
}

int Cadre::h() const
{
	if (m_contenu)
		return m_contenu->h() + m_haut + m_bas;
	else
		return 1;
}

