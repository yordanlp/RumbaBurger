#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <userdto.h>
#include <QString>
#include <QDebug>

class UserService
{
public:
    UserService();
    bool insertUser( UserDto );
    bool deleteUser( UserDto );
    bool updateUser( UserDto );
    UserDto getUserByUsername( QString );

};

#endif // USERSERVICE_H
