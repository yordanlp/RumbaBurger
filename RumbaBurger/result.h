#ifndef RESULT_H
#define RESULT_H
#include<QString>

enum result{
    SUCCESS, FAIL, RECORDNOTFOUND
};

template<class T>
class Result
{
public:
    Result(){
        res = result::FAIL;
    }
    QString msg;
    result res;
    T data;
};

#endif // RESULT_H
