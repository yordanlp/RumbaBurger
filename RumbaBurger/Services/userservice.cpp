#include "userservice.h"
#include <QSqlQuery>

int UserService::loggedUser = -1;

UserService::UserService()
{

}


Result<bool> UserService::deleteUser(UserDto u){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", u.id);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteUser: " + query.lastError().text();
    qDebug() << "ERROR deleteUser: " << query.lastError().text();
    return res;
}

Result<UserDto> UserService::getUserByUsername(QString userName){
    Result<UserDto>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE user = :user");
    query.bindValue(":user", userName);
    if( !query.exec() ) {
        res.res = result::FAIL;
        res.msg = "ERROR getUserByUsername: " + query.lastError().text();
        qDebug() << "ERROR getUserByUsername: " << query.lastError().text();
        return res;
    }

    if( query.next() ){
        res.res = result::SUCCESS;
        res.data = UserDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt());
        return res;
    }
    res.res = RECORD_NOT_FOUND;
    return res;
}

Result<bool> UserService::insertUser(UserDto u){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO users (user, password, name, role) VALUES (:user, :password, :name, :role)");
    query.bindValue(":user", u.user);
    query.bindValue(":password", u.password);
    query.bindValue(":name", u.name);
    query.bindValue(":role", u.role);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertUser: " + query.lastError().text();
    qDebug() << "ERROR insertUser: " << query.lastError().text();
    return res;
}

Result<bool> UserService::updateUser(UserDto u){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("UPDATE users SET user=:user, password=:password, name=:name, role=:role  WHERE id=:id");
    query.bindValue(":user", u.user);
    query.bindValue(":password", u.password);
    query.bindValue(":name", u.name);
    query.bindValue(":id", u.id);
    query.bindValue(":role", u.role);
    if( query.exec() ){
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR updateUser: " + query.lastError().text();
    qDebug() << "ERROR updateUser: " << query.lastError().text();
    return res;
}

Result<UserDto> UserService::getUserById(int id)
{
    Result<UserDto>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", id);
    if( !query.exec() ) {
        res.res = result::FAIL;
        res.msg = "ERROR getUserById: " + query.lastError().text();
        qDebug() << "ERROR getUserById: " << query.lastError().text();
        return res;
    }

    if( query.next() ){
        res.res = result::SUCCESS;
        res.data = UserDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt());
        return res;
    }
    res.res = RECORD_NOT_FOUND;
    return res;
}
