#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
    extern "C" {
#endif

void clrscr();

int findIndexInt(int *arr, int target);
int findIndexChar(char *arr, char target);
int findIndexString(char **arr, char *target);

#ifdef __cplusplus
    }
#endif

#endif /* UTILS_H_ */