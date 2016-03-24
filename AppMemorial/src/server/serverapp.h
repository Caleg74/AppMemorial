#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QObject>

class ServerApp  : public QObject
{
    Q_OBJECT
public:
    explicit ServerApp(QObject *parent = 0);

    /** Destructor */
    virtual ~ServerApp();

    /** Connectes all UI signals */
    void Connect();

};

#endif // SERVERAPP_H
