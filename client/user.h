#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(QString name, QString ipAddress, bool online);

    QString getName();
    void setName(QString name);

    QString getIp();
    void setIp(QString ipAddress);

    bool getOnline();
    void setOnline(bool isOnline);

    ~User();
private:
    QString name;
    QString ipAddress;
    bool online;
};

#endif // USER_H
