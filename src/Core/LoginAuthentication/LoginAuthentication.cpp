#include "LoginAuthentication.hpp"

LoginAuthentication::LoginAuthentication(QObject *parent)
{

}

void LoginAuthentication::login(QString email, QString password)
{
    setLoading(true);
    QUrl url("http://127.0.0.1:8000/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject payload;
    payload["email"] = email;
    payload["password"] = password;

    QJsonDocument doc(payload);

    QNetworkReply* reply = manager.post(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        setLoading(false);
        if(reply->error() == QNetworkReply::NoError)
        {
            auto json = QJsonDocument::fromJson(reply->readAll()).object();
            m_token = json["token"].toString();
            storeToken(m_token);
            emit loginSuccessful();
            getToken();
        }
        else {
            emit loginFailed(reply->errorString());
            clearToken();
        }
        reply->deleteLater();
    });
}

void LoginAuthentication::fetchProfile()
{
    if(!m_token.isEmpty())
    {
        qInfo()<<"this is here";
    }

    QUrl url("http://127.0.0.1:8000/profile");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer "+ m_token.toUtf8());

    // Authorizaton: Bearer admskadad

    QNetworkReply* reply = manager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if(reply->error() == QNetworkReply::NoError)
        {
            auto json = QJsonDocument::fromJson(reply->readAll()).object();
            QString email = json["email"].toString();
            QString password = json["user"].toString();
            emit fetchProfileSuccessful(email, password);
        }
        else {
            emit fetchProfileFailed(reply->errorString());
            clearToken();
        }
        reply->deleteLater();
    });
}

bool LoginAuthentication::loading()
{
    return m_loading;
}

bool LoginAuthentication::remember()
{
    return statusRemember;
}

void LoginAuthentication::setRemember(bool value)
{
    if(statusRemember != value)
    {
        statusRemember = value;
        emit rememberChanged();
    }
}

void LoginAuthentication::setLoading(bool value)
{
    if(m_loading != value)
    {
        m_loading = value;
        emit loadingChanged();
    }
}

void LoginAuthentication::storeToken(const QString &token)
{
    QSettings settings;
    settings.setValue("auth/token", token);
}

QString LoginAuthentication::getToken()
{
    QSettings settings;
    QString token = settings.value("auth/token", "").toString();
    qInfo()<<token;
    return token;
}

void LoginAuthentication::clearToken()
{
    QSettings settings;
    settings.clear();
}
