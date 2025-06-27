#include <QObject>
#include "LoginAuthentication.hpp"

class App: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool remember WRITE setRemember NOTIFY rememberChanged FINAL)

public:

    App(QObject* parent = nullptr);


    Q_INVOKABLE void login(QString email, QString password);
    Q_INVOKABLE void setRemember(bool value);
    Q_INVOKABLE void tryAutoLogin();

signals:
    void rememberChanged();
    void loginSuccessful();

private:

    LoginAuthentication loginAuthenticate;
};

