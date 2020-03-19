#include "user.h"

User::User()
{

}

User::User(QString name, QString ipAddress, bool online)
{
    this->name = name;
    this->ipAddress = ipAddress;
    this->online = online;
}

User::~User()
{
    delete this;
}

QString User::getName()
{
    return this->name;
}

void User::setName(QString name)
{
    this->name = name;
}

QString User::getIp()
{
    return this->ipAddress;
}

void User::setIp(QString ipAddress)
{
    this->ipAddress = ipAddress;
}

bool User::getOnline()
{
    return this->online;
}

void User::setOnline(bool isOnline)
{
    this->online = isOnline;
}




