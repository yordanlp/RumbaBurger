#include "userdto.h"

UserDto::UserDto()
{

}

UserDto::UserDto(int _id, QString _user, QString _password, QString _name){
    id = _id;
    user = _user;
    password = _password;
    name = _name;
}
