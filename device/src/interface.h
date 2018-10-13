#ifndef __INTERFACE_H__
#define __INTERFACE_H__

typedef struct {
  char *name,
       *type,
       *args;
} Method;

void caller(void);

extern const int numberOfMethods;
extern const Method methods[];

#endif
