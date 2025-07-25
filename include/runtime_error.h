#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

void RuntimeError(const char *message, int parameter,
                  const char *file, int line);

/// Code should use this macro instead of the function
#define RUNTIME_ERROR(description, parameter) RuntimeError(description, parameter, __FILE__, __LINE__)

#endif