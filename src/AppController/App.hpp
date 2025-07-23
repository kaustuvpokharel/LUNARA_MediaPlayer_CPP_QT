#include <QObject>
#include "LoginAuthentication.hpp"

class App: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool remember WRITE setRemember NOTIFY rememberChanged FINAL)
    Q_PROPERTY(QVariantMap Palette READ Palette NOTIFY paletteChanged)

public:

    App(QObject* parent = nullptr);


    Q_INVOKABLE void login(QString email, QString password);
    Q_INVOKABLE void setRemember(bool value);
    Q_INVOKABLE void tryAutoLogin();
    QVariantMap Palette();

signals:
    void rememberChanged();
    void loginSuccessful();
    void paletteChanged();

private:

    LoginAuthentication loginAuthenticate;
};

