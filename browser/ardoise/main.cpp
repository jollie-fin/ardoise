
#include "Navigateur.h"









int main(int argc, char* argv[])
{
    QApplication app(argc, argv);


	if (argc != 2)
		return 1;
	Navigateur *nav = new Navigateur(QString(argv[1]));

		nav->showMaximized();
		nav->show();
    return app.exec();
}
