#ifndef USERDTO_H
#define USERDTO_H
#include <QString>

class UserDto
{
public:
    int id;
    QString user, password, name;
    int role;
    UserDto();
    UserDto(int _id, QString _user, QString _password, QString _name, int _role );
};

#endif // USERDTO_H
