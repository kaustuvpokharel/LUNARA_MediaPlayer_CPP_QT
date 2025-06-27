#include "App.hpp"

App::App(QObject *parent)
{
    connect(&loginAuthenticate, &LoginAuthentication::rememberChanged, this, &App::rememberChanged);
    connect(&loginAuthenticate, &LoginAuthentication::loginSuccessful, this, &App::loginSuccessful);
}

void App::login(QString email, QString password)
{
    loginAuthenticate.login(email, password);
}

void App::setRemember(bool value)
{
    loginAuthenticate.setRemember(value);
}

void App::tryAutoLogin()
{
    loginAuthenticate.tryAutoLogin();
}
