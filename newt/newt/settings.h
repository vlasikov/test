#ifndef SETTINGS_H
#define SETTINGS_H

#include "data.h"
#include <QObject>
#include <QString>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    void write(AllUdpSettings *s);
    void read(AllUdpSettings *s);

    QSettings *settings;

signals:

public slots:

};

#endif // SETTINGS_H
