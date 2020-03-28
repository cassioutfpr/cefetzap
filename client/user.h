#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(QString name, QString ipAddress, bool online, quint16 port);

    QString getName();
    void setName(QString name);

    QString getIp();
    void setIp(QString ipAddress);

    bool getOnline();
    void setOnline(bool isOnline);

    quint16 getPort();
    void setPort(quint16 port);

    ~User();
private:
    QString name;
    QString ipAddress;
    quint16 port;
    bool online;
};

#endif // USER_H
