/*
 * Widget.cpp
 *
 *  Created on: 23 janv. 2011
 *      Author: phi
 */

#include "Widget.h"
#include <ncursesw/ncurses.h>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

struct  Foncteur
{
	Widget *m_appelant;
	Foncteur(Widget *appelant)
	{
		m_appelant = appelant;
	}

	void operator ()(std::pair<int, std::pair<void *, Widget::ptr_member> > couple)
	{
		int touche = couple.first;
		void *par = couple.second.first;
		Widget::ptr_member ptr = couple.second.second;
		(*ptr)(m_appelant, touche, par);
	}
};

Widget::Widget()
{
}

bool Widget::gere_clavier(wint_t touche)
{
	std::pair<Widget::iterator,Widget::iterator> it = m_assoc.equal_range(touche);
	if (it.first!=it.second)
	{
		Foncteur f(this);
		std::for_each(it.first, it.second, f);
		return false;
	}
	else
		return false;
}

void Widget::setactive(bool active)
{
	m_active = active;
}

bool Widget::active() const
{
	return m_active;
}

Widget::~Widget()
{
	;
}

std::multimap <wint_t, std::pair<void *,Widget::ptr_member> >& Widget::assoc()
{
	return m_assoc;
}

void Widget::ajoute_evenement(int touche, Widget::ptr_member ptr, void *par)
{
	m_assoc.insert(std::make_pair(touche, std::make_pair(par, ptr)));
}
