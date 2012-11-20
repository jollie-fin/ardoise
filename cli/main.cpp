/*
 * main.cpp
 *
 *  Created on: 22 janv. 2011
 *      Author: phi
 */

#include <ncursesw/ncurses.h>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <utility>
#include "Saisie_texte.h"
#include "Cadre.h"
#include <locale.h>

#include <iostream>
#include <sstream>
void affiche(int envaleur)
{
    switch (envaleur)
    {
		case 0:
        	attron(A_REVERSE);
        	mvprintw(0,0,"Liquide");
            attroff(A_REVERSE);
            mvprintw(1,0,"Ardoise");
            mvprintw(2,0,"  ");
            mvprintw(3,0,"  ");
            mvprintw(2,2,"Login");
            mvprintw(3,2,"Mdp");
            break;

		case 1:
        	mvprintw(0,0,"Liquide");
        	attron(A_REVERSE);
            mvprintw(1,0,"Ardoise");
            mvprintw(2,0,"  ");
            mvprintw(3,0,"  ");
            mvprintw(2,2,"Login");
            attroff(A_REVERSE);
            mvprintw(3,2,"Mdp");
            break;


		case 2:
        	mvprintw(0,0,"Liquide");
        	attron(A_REVERSE);
            mvprintw(1,0,"Ardoise");
            mvprintw(2,0,"  ");
            mvprintw(3,0,"  ");
            attroff(A_REVERSE);
            mvprintw(2,2,"Login");
        	attron(A_REVERSE);
        	mvprintw(3,2,"Mdp");
            attroff(A_REVERSE);
			break;

    }
}

bool saisie(wint_t ch)
{
	static wint_t ancien = 0;
	static int num = 0;
	static char chemin[100]="";
	if (ch >= 32 && ch < 256)
	{
		chemin[num++] = ch;
		chemin[num] = '\0';

		mvprintw(2,9,chemin);

		mvprintw(20,10,"              ");
		mvprintw(21,10,"                                 ");


		mvprintw(20,10,"%lu",strlen(chemin));

		std::ostringstream s1;

		s1 << ancien << " " << ch;
		mvprintw(21,10,s1.str().c_str());

		ancien = ch;

		attron(A_UNDERLINE);
		mvprintw(2,9+strlen(chemin)," ");
		attroff(A_UNDERLINE);

		return true;
	}
	else
		return false;
}


void teste(Widget *appellant, int touche, void *param)
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

int main()
{
	setlocale(LC_ALL,"");
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(1));

	//init_pair(1, COLOR_RED, COLOR_BLACK);


	Saisie_texte s1(10,false, std::wstring(L"éléphant"));
	Saisie_texte s2(10,false, std::wstring(L"éléphant"));
	Cadre c1(&s1,true,true,false,true);
	Cadre c2(&s2,true,true,true,true);

	c1.ajoute_evenement(10,&Saisie_texte::toggle,&s1);
	c1.ajoute_evenement(10,&Saisie_texte::toggle,&s2);

	//s.assoc()[KEY_ENTER](NULL,0,NULL);


	bool pas_fini = true;
	int indice = 0;
	   affiche(indice);
	   refresh();
	while (pas_fini)
	{
	wint_t ch;
	//ch = getch();
	get_wch(&ch);

	  switch(ch)
	  {
		case KEY_EXIT:
			pas_fini = false;
			break;

		case KEY_UP:
			indice--;
			if (indice == -1) indice = 2;
			break;

		case KEY_DOWN:
			indice++;
			if (indice == 3) indice = 0;
			break;

		case 27:
			pas_fini = false;
			break;

		default:
			saisie(ch);
			c1.gere_clavier(ch);
			c2.gere_clavier(ch);
			break;
	   }
	   affiche(indice);
	   c2.affiche(10,7);
	   c1.affiche(10,10);
	   refresh();
	}
	endwin();
	return 0;
}

