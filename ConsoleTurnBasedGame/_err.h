#ifndef ERR_H_
#define ERR_H_

void _err_init();

struct _err
{
    char cause[64];
    char message[128];
    int _return;
};
typedef struct _err Error;

Error *getErrors();

#endif