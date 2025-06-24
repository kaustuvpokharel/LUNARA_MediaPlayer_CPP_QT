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
    Q_INVOKABLE void tryAutoLogin();
    //callabale Incside QML

    bool loading();
    void setLoading(bool value);
    bool remember();
    void setRemember(bool value);
    void storeToken();
    void clearToken();
    QString getToken();

private:
    bool m_loading = false;
    QString m_token;
    bool statusRemember = false;
    QNetworkAccessManager manager;

signals:
    void loadingChanged();
    void loginSuccessful();
    void loginFailed();
    void rememberChanged();
    void fetchProfileSuccessful(const QString& user, const QString& email);
    void fetchProfileFailed();
};
