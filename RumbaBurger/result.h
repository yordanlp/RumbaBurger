#ifndef RESULT_H
#define RESULT_H
#include<QString>

enum result{
    SUCCESS, FAIL
};

template<class T>
class Result
{
public:
    Result(){}
    QString msg;
    result res;
    T data;
};

#endif // RESULT_H
