#include "dbmanager.h"
#include <QDebug>

DBManager::DBManager()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rumbaburgerdb.sqlite");
    if( !db.open() )
        qDebug() << "Database not open";
}

/** Product **/

bool DBManager::insertProduct(ProductDto p){
      QSqlQuery query;
      query.prepare("INSERT INTO product (productName, unitType, price) VALUES (:productName, :unitType, :price)");
      query.bindValue(":productName", p.productName);
      query.bindValue(":unitType", p.unitType);
      query.bindValue(":price", p.price);
      qDebug() << query.lastQuery();
      if( query.exec() ) return true;
      qDebug() << "ERROR insertProduct: " << query.lastError().text();
      return false;
}



