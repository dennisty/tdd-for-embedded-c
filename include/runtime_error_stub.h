
#ifndef RUNTIME_ERROR_STUB_H
#define RUNTIME_ERROR_STUB_H

#include "runtime_error.h"

///
/// Allows test code to reset the stub
///
void RuntimeErrorStub_Reset(void);

///
/// Retrieve the last error message passed to the stub
/// @return the last error message passed to the stub
///
const char *RuntimeErrorStub_GetLastError(void);

///
/// Retrieve the position of the last parameter that caused the error
/// @return the position of the last parameter that caused the error
///
int RuntimeErrorStub_GetLastParameter(void);

#endif