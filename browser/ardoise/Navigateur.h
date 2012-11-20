#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QtWebKit>
#include <QtGui>

class Navigateur : public QMainWindow
{
    Q_OBJECT

    private:
			QUrl origine;
      QAction *actionreinitialise;
      QWebView *pagenet;

    public:
        Navigateur(const QString &q);

    private slots:
			void reinitialise();
			void quitte();
			void urlChange(const QUrl &q);
};

