#include <iostream>
#include "Mouvement.h"
#include "Boisson.h"
#include "Outil.h"
#include "Etudiant.h"
#include "Bdd.h"
#include "Types.h"
int main()
{
	try
	{
		std::cout << "creation elie" << std::endl;
		Etudiant e(Types::Id("elie","gedeon"),0,true,true);

		std::cout << "est ce mdp " << e.estce_mdp("1234") << std::endl;
		e.change_mdp("","12");
		std::cout << "est ce mdp " << e.estce_mdp("1234") << std::endl;
		std::cout << "est ce mdp " << e.estce_mdp("12") << std::endl;
		Bdd::etudiants[e.id()] = e;


		Boisson b("biere",10);
		Bdd::boissons[b.nom()] = b;
		Boisson b2("biere2",10);
		Bdd::boissons[b2.nom()] = b2;
		Bdd::getetudiant(Types::Id("elie","gedeon")).consomme("biere");
		Bdd::getetudiant(Types::Id("elie","gedeon")).credite(Types::Id("elie","gedeon"),10);



		std::cout << Bdd::getetudiant(Types::Id("elie","gedeon")).solde() << std::endl;

		std::cout << "Enregistrement" << std::endl;

		Bdd::sauve_binaire("test");
		Bdd::sauve_xml("test.xml");
		Bdd::getetudiant(Types::Id("elie","gedeon")).credite(Types::Id("elie","gedeon"),20);

		std::cout << Bdd::getetudiant(Types::Id("elie","gedeon")).solde() << std::endl;

		std::cout << "Lecture" << std::endl;
		Bdd::charge_binaire("test");

		std::cout << "Fin Lecture" << std::endl;
		std::cout << Bdd::getetudiant(Types::Id("elie","gedeon")).solde() << std::endl;
		//std::cout << Bdd::getetudiant(Types::Id("elie","gedeon")).historique().size() << std::endl;
	}
	catch (std::string &s)
	{
		std::cout << s << std::endl;
	}
	catch (char const *s)
	{
		std::cout << s << std::endl;
	}

}

