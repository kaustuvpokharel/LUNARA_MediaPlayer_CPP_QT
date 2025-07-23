#include "ThemeManager.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ThemeManager* ThemeManager::getThemeInstance()
{
    static ThemeManager instance;
    return &instance;
}

QVariantMap ThemeManager::loadTheme()
{
    QFile file(":/defaultTheme.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Not able to load Json Theme File");
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject object = doc.object();
    QVariantMap dict = object.toVariantMap();
    QVariantMap rawTheme = dict["theme"].toMap();

    QVariantMap flat = flatten(rawTheme, "");
    return flat;

    //flat[color.primary.background] = "#ab"
}

ThemeManager::ThemeManager(QObject *parent)
{

}

QVariantMap ThemeManager::flatten(const QVariantMap &rawTheme, const QString prefix)
{
    QVariantMap flat;
    //color.something.something: value

    for(auto it = rawTheme.begin(); it != rawTheme.end(); ++it)
    {
        QString key = prefix.isEmpty() ? it.key() : prefix + "." + it.key();
        if(it.value().typeId() == QMetaType::QVariantMap)
        {
            QVariantMap nested = flatten(it.value().toMap(), key);
            for(auto nestedIt = nested.begin(); nestedIt != nested.end(); ++nestedIt)
            {
                flat.insert(nestedIt.key(), nestedIt.value());
            }
        }
        else
        {
            flat.insert(key, it.value());
        }
    }
    return flat;
}
