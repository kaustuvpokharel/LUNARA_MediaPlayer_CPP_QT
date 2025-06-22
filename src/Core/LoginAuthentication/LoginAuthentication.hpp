#include <QObject>
#include <QNetworkAccessManager> //Network
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>

class LoginAuthentication: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    //C++ code be ack the MOC

public:
    LoginAuthentication(QObject* parent = nullptr);
    Q_INVOKABLE void login(QString email, QString password); // to send it to the server
    //callabale Incside QML

    bool loading();
    void setLoading(bool value);

private:
    bool m_loading = false;
    QNetworkAccessManager manager;

signals:
    void loadingChanged();
    void loginSuccessful();
    void loginFailed();
};
