#include <QObject>
#include <QNetworkAccessManager> //Network
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>

class LoginAuthentication: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool remember READ remember WRITE setRemember NOTIFY rememberChanged FINAL)
    //C++ code be ack the MOC

public:
    LoginAuthentication(QObject* parent = nullptr);
    Q_INVOKABLE void login(QString email, QString password); // to send it to the server
    Q_INVOKABLE void fetchProfile();
    //callabale Incside QML

    bool loading();
    bool remember();
    void setRemember(bool value);
    void setLoading(bool value);
    QString getToken();


private:
    bool m_loading = false;
    QString m_token;
    bool statusRemember = false;
    QNetworkAccessManager manager;
    void storeToken(const QString& token);
    void clearToken();

signals:
    void loadingChanged();
    void loginSuccessful();
    void loginFailed(const QString& error);
    void rememberChanged();
    void fetchProfileSuccessful(const QString& email, const QString& user);
    void fetchProfileFailed(const QString& error);
};
