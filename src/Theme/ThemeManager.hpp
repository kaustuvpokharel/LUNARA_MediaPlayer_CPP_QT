#include <QObject>

class ThemeManager: public QObject
{
public:
    static ThemeManager* getThemeInstance();

    QVariantMap loadTheme();

private:
    ThemeManager(QObject* parent = nullptr);
    QVariantMap flatten(const QVariantMap& rawTheme, const QString prefix);
};
