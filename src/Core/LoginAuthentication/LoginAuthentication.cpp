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
            emit loginSuccessful();
        }
        else {
            emit loginFailed();
        }
        reply->deleteLater();
    });
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
