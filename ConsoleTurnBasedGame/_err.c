#include <stdlib.h>
#include <string.h>
#include "_err.h"

Error _err_ClassNum;
Error _err_ClassDuplicate;

void _err_init()
{
    Error *PTR_err_ClassNum = &_err_ClassNum;
    strcpy(PTR_err_ClassNum->cause, "Invalid class number.");
    strcpy(PTR_err_ClassNum->message, "Error: A proper class number is required.");
    PTR_err_ClassNum->_return = -1;
    
    Error *PTR_err_ClassDuplicate = &_err_ClassDuplicate;
    strcpy(PTR_err_ClassDuplicate->cause, "Invalid class selection.");
    strcpy(PTR_err_ClassDuplicate->message, "Error: Each player must select a different class.");
    PTR_err_ClassDuplicate->_return = -1;

}

Error *getErrors()
{
    Error *errors = malloc( 8 * sizeof(Error) );
    errors[0] = _err_ClassNum;
    errors[1] = _err_ClassDuplicate;

    return errors;
}