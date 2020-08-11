#include "userservice.h"
#include <QSqlQuery>

UserService::UserService()
{

}


bool UserService::deleteUser(UserDto u){
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", u.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteUser: " << query.lastError().text();
    return false;
}

UserDto UserService::getUserByUsername(QString userName){
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE user = :user");
    query.bindValue(":user", userName);
    if( !query.exec() ) {
        qDebug() << "ERROR getUserByUsername: " << query.lastError().text();
        return UserDto(-1,"","","");
    }
    query.next();

    return UserDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString());
}

bool UserService::insertUser(UserDto u){
    QSqlQuery query;
    query.prepare("INSERT INTO users (user, password, name) VALUES (:user, :password, :name)");
    query.bindValue(":user", u.user);
    query.bindValue(":password", u.password);
    query.bindValue(":name", u.name);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertUser: " << query.lastError().text();
    return false;
}

bool UserService::updateUser(UserDto u){
    QSqlQuery query;
    query.prepare("UPDATE users SET user=:user, password=:password, name=:name  WHERE id=:id");
    query.bindValue(":user", u.user);
    query.bindValue(":password", u.password);
    query.bindValue(":name", u.name);
    query.bindValue(":id", u.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR updateUser: " << query.lastError().text();
    return false;
}
