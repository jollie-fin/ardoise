/*
 * Saisie_texte.cpp
 *
 *  Created on: 24 janv. 2011
 *      Author: phi
 */

#include "Saisie_texte.h"
#include <ncursesw/ncurses.h>
#include <cctype>
#include <string>
#include <sstream>

Saisie_texte::Saisie_texte(int w,
						   bool secret,
						   std::wstring chaine) : Widget() {
	m_w = w;
	m_secret = secret;
	m_chaine = chaine;
	m_buffer = new wchar_t[m_w+1];
	m_buffer[m_w] = '\0';
	m_indice = 0;
	m_offset = 0;
	m_reverse = false;
}


int Saisie_texte::w() const
{
	return m_w;
}

int Saisie_texte::h() const
{
	return 1;
}


Saisie_texte::~Saisie_texte() {
	delete[] m_buffer;
}

bool Saisie_texte::secret()
{
	return m_secret;
}

void Saisie_texte::affiche(int x, int y)
{
	if (m_reverse)
		attron(A_REVERSE);
	int i;
	for (i = 0; i < m_w; i++)
	{
			if (i + m_offset < (int) m_chaine.length())
				if (!m_secret)
					m_buffer[i] = m_chaine[i+m_offset];
				else
					m_buffer[i] = L'*';
			else
				m_buffer[i] = L' ';
	}

	//mvaddchstr(y,x,m_buffer);
	mvaddwstr(y,x,m_buffer);


	if ((m_indice-m_offset >= 0) && (m_indice-m_offset < m_w))
	{
		wchar_t c;
		if (m_indice >= (int) m_chaine.length())
			c = ' ';
		else
			c = m_buffer[m_indice-m_offset];
		attron(A_UNDERLINE);
		mvaddnwstr(y,x+m_indice-m_offset,&c,1);
		attroff(A_UNDERLINE);

		std::ostringstream s;
		s << (unsigned long) c;
		mvprintw(20,0,"                    ");
		mvprintw(20,0,s.str().c_str());
	}
	attroff(A_REVERSE);
}

bool Saisie_texte::gere_clavier(wint_t touche)
{
	bool b = Widget::gere_clavier(touche);
	if (!b)
	{
		if (touche >= 32 && touche < 256)
		{
			m_chaine.insert(m_chaine.begin()+m_indice, (wchar_t) touche);
			m_indice++;
		}
		else if (touche == KEY_BACKSPACE)
		{
			if (m_indice > 0)
			{
				m_indice--;
				if (m_indice < 0)
					m_indice = 0;
				m_chaine.erase(m_chaine.begin()+m_indice);
			}
		}
		else if (touche == KEY_DC)
		{
			if (m_chaine.empty() == false)
			{
				if ((unsigned int) m_indice == m_chaine.length())
					m_indice--;
				if (m_indice < 0)
					m_indice = 0;
				m_chaine.erase(m_chaine.begin()+m_indice);
			}
		}
		else if (touche == KEY_LEFT)
		{
			m_indice--;
			if (m_indice < 0)
				m_indice = 0;
		}
		else if (touche == KEY_RIGHT)
		{
			m_indice++;
			if ((unsigned int) m_indice > m_chaine.length())
				m_indice = m_chaine.length();
		}
		else if (touche == KEY_HOME)
		{
			m_indice = 0;
		}
		else if (touche == KEY_END)
		{
			m_indice = m_chaine.length();
		}
		else
			return false;

		if (m_indice < m_offset)
			m_offset = m_indice;
		if (m_indice > m_offset+m_w-1)
			m_offset = m_indice-m_w+1;
	}
	return true;
}

const std::wstring &Saisie_texte::chaine() const
{
	return m_chaine;
}

void Saisie_texte::toggle(Widget *appellant, int touche, void *widget)
{
	((Saisie_texte *) widget)->m_reverse = !((Saisie_texte *) widget)->m_reverse;
}

