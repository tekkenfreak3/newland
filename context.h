#ifndef CONTEXT_H
#define CONTEXT_H
#include "value.h"
struct context
{
    char *key[256];
    struct value *values[256];
    // context is like a dynamically constructed stack, if what we want isn't in the stack just keep going up
    // arguments are only slightly special in that they're copied rather than just thrown into the context
    struct context next_up;
}
