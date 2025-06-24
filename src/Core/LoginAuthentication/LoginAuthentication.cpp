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
            emit loginSuccessful();
            if(rememberStatus)
            {
                storeToken();
            }
            else
            {
                clearToken();
            }
            qInfo()<<m_token;
        }
        else {
            emit loginFailed();
        }
        reply->deleteLater();
    });
}

void LoginAuthentication::fetchProfile()
{
    QUrl url("http://127.0.0.1:8000/profile");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer "+ m_token.toUtf8());

    QNetworkReply* reply = manager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply](){
        if(reply->error() == QNetworkReply::NoError)
        {
            auto json = QJsonDocument::fromJson(reply->readAll()).object();
            QString user = json["user"].toString();
            QString email = json["email"].toString();
            emit loginSuccessful();
            emit fetchProfileSuccessful(user, email);
        }
        else {
            emit fetchProfileFailed();
        }
        reply->deleteLater();
    });
}

void LoginAuthentication::tryAutoLogin()
{
    getToken();
    if(!m_token.isEmpty())
    {
        fetchProfile();
    }
}

bool LoginAuthentication::loading()
{
    return m_loading;
}

void LoginAuthentication::setLoading(bool value)
{
    if(m_loading != value)
    {
        m_loading = value;
        emit loadingChanged();
    }
}

bool LoginAuthentication::remember()
{
    return rememberStatus;
}

void LoginAuthentication::setRemember(bool value)
{
    if(rememberStatus != value)
    {
        rememberStatus = value;
        emit rememberChanged();
    }
}

void LoginAuthentication::storeToken()
{
    QSettings token;
    token.setValue("auth/token", m_token);
}

void LoginAuthentication::clearToken()
{
    QSettings token;
    token.clear();
}

QString LoginAuthentication::getToken()
{
    QSettings token;
    return token.value("auth/token", "").toString();
}
