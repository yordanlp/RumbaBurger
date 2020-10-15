#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Dto/userdto.h>
#include <QString>
#include <QDebug>
#include "result.h"

class UserService
{
public:
    UserService();
    Result<bool> insertUser( UserDto );
    Result<bool> deleteUser( UserDto );
    Result<bool> updateUser( UserDto );
    Result<UserDto> getUserById( int id );
    Result<UserDto> getUserByUsername( QString );
    static int loggedUser;
};

#endif // USERSERVICE_H
