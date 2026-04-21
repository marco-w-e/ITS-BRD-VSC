#ifndef Stack_H
#define Stack_H

/*
 ****************************************************************************************
 * @brief : This function stores a value(int) on the stack
 *
 * @return A 0 will be returned. In case of an error Stack Overflow will
 *         be returned.
 ****************************************************************************************/
int push(int *val);
/*
 ****************************************************************************************
 * @brief : This function returns the first value on the Stack
 *
 * @return Next token will be returned. In case of an error the UNEXPTECTED token will
 *         be returned.
 ****************************************************************************************/

int pop(int *val);

int  peek(char *str);

int clearStack(void);

int peekALL (int *x);

#endif
// eof 