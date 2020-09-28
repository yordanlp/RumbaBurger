#include "dishversionsservice.h"
#include <Services/ingredientsservice.h>

DishVersionsService::DishVersionsService()
{

}

Result<bool> DishVersionsService::createVersion(DishDto dish){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO dishVersions (id, dishName, description, price) VALUES (:id, :dishName, :description, :price)");
    query.bindValue(":id", dish.id);
    query.bindValue(":dishName", dish.dishname);
    query.bindValue(":description", dish.description);
    query.bindValue(":price", dish.price);

    if( !query.exec() ) {
        res.res = result::FAIL;
        return res;
    }

    res.res = SUCCESS;
    res.msg = "createVersion " + query.lastError().text();

    return res;
}
