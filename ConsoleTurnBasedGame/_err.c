#include <stdlib.h>
#include <string.h>
#include "_err.h"

Error _err_ClassNum;

void _err_init()
{
    Error *PTR_err_ClassNum = &_err_ClassNum;
    strcpy(PTR_err_ClassNum->cause, "Invalid class number.");
    strcpy(PTR_err_ClassNum->message, "Error: A proper class number is required.");
    PTR_err_ClassNum->_return = -1;

    // free(PTR_err_ClassNum);
}

Error *getErrors()
{
    Error *errors = malloc( 8 * sizeof(Error) );
    errors[0] = _err_ClassNum;

    return errors;
}