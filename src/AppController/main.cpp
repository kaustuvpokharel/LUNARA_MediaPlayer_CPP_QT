#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include "App.hpp"
// #include "LoginAuthentication.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    App control;
    qmlRegisterSingletonInstance("LUNARA", 1, 0, "App", &control);

    // LoginAuthentication loginAuthenticate;

    // QObject::connect(&loginAuthenticate, &LoginAuthentication::loginSuccessful, [&](){
    //     qInfo()<<"Login Successful ....";
    //     loginAuthenticate.fetchProfile();
    // });

    // QObject::connect(&loginAuthenticate, &LoginAuthentication::loginFailed, [](){
    //     qInfo()<<"Login Failed";
    // });

    // QObject::connect(&loginAuthenticate, &LoginAuthentication::fetchProfileSuccessful, [&](const QString& user, const QString& email){
    //     qInfo()<<user;
    //     qInfo()<<email;
    // });

    // loginAuthenticate.login("test@example.com", "mypassword");

    const QUrl url(QStringLiteral("qrc:/MediaPlayer/Main/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
