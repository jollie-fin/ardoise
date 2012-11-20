/*
 * Widget.h
 *
 *  Created on: 23 janv. 2011
 *      Author: phi
 */



#ifndef WIDGET_H_
#define WIDGET_H_

#include <map>
#include <utility>
#include <string>
class Widget {
	public:
		typedef void (*ptr_member)(Widget *appellant, int touche, void *parametre);
		typedef std::multimap <wint_t, std::pair<void *,ptr_member> >::iterator iterator;
	protected:
		bool m_active;
		std::multimap <wint_t, std::pair<void *,ptr_member> > m_assoc;

	public:
		Widget();
		virtual bool gere_clavier(wint_t touche);
		virtual void affiche(int x, int y) = 0;
		virtual void setactive(bool active);
		virtual bool active() const;
		virtual int w() const = 0;
		virtual int h() const = 0;
		std::multimap <wint_t, std::pair<void *,ptr_member> >& assoc();
		void ajoute_evenement(int touche, ptr_member ptr, void *par);
		virtual ~Widget();
};



#endif /* WIDGET_H_ */
