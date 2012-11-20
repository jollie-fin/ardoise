#include "Navigateur.h"
        Navigateur::Navigateur(const QString &q)
				{
					origine = QUrl(q);
					pagenet = new QWebView();
					reinitialise();

					actionreinitialise = new QAction(tr("&quitte"), this);
    			actionreinitialise->setShortcut(Qt::Key_Escape);
					addAction(actionreinitialise);
			    connect(actionreinitialise, SIGNAL(triggered()), this, SLOT(quitte()));

			    connect(pagenet, SIGNAL(urlChanged(const QUrl &)), this, SLOT(urlChange(const QUrl &)));
					setCentralWidget(pagenet);

				}

			void Navigateur::reinitialise()
			{
				pagenet->load(origine);
			}

			void Navigateur::quitte()
			{
				qApp->exit();
			}


		void Navigateur::urlChange(const QUrl &q)
		{
			if (origine.host() != q.host())
				reinitialise();
		}
