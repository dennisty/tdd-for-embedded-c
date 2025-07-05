// Stub implementation of RuntimeError.h

#include "runtime_error_stub.h"

static const char *message = "No Error";
static int parameter = -1;
static const char *file = 0;
static int line = -1;

///
/// Allows us to reset internal stats before each test
///
void RuntimeErrorStub_Reset(void)
{
    message = "No Error";
    parameter = -1;
}

///
/// Get the last error message
/// @return the last error message
///
const char *RuntimeErrorStub_GetLastError(void)
{
    return message;
}

///
/// Implementation of RuntimeError.h - pass a message to be stored in an event log
/// @param m the message to log
/// @param p the parameter position in the function
/// @param f pointer to file
/// @param l the line number
void RuntimeError(const char *m, int p, const char *f, int l)
{
    message = m;
    parameter = p;
    file = f;
    line = l;
}

///
/// Allows tests to get the last parameter position
/// @return the last parameter number
///
int RuntimeErrorStub_GetLastParameter(void)
{
    return parameter;
}