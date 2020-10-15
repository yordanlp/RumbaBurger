#include "userdto.h"

UserDto::UserDto()
{

}

UserDto::UserDto(int _id, QString _user, QString _password, QString _name, int _role){
    id = _id;
    user = _user;
    password = _password;
    name = _name;
    role = _role;
}
