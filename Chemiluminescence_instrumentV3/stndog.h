#ifndef STNDOG_H
#define STNDOG_H
extern "C" //由于是C版的dll文件，在C++中引入其头文件要加extern "C" {},注意  -----已完成
{
    #include "hasp_api.h"
}
class StnDog
{
public:
    StnDog();
    hasp_status_t status;

};

#endif // STNDOG_H
