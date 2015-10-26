#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parselib.h"

bool is_delimiter(char c)
{
    return (isspace(c)) || c == '\0';// || c == '(' || c == ')')
}

struct value read_int(const char *str, bool *errored)
{
    int value = 0;
    while(isdigit(*str))
    {
        value *= 10;
        value += (*str) - 0x30; // ascii digit to value
        str++;
    }
    if (!is_delimiter(*str))
    {
        *errored = true;
        return new_unknown_value();
    }
    
    return new_int_value(value);
}

struct value read_double(const char *str, bool *errored)
{
    if (*str++ == '#')
    {
        if (isalnum(*str))
        {
            if (is_delimiter(*(str+1)))
            {
                return new_char_value(*str);
            }
        }
    }
    *errored = true;
    return new_unknown_value();    
}

struct value read_char(const char *str, bool *errored)
{
    if (*str++ == '#')
    {
        if (isprint(*str))
        {
            if (is_delimiter(*(str+1)))
            {
                return new_char_value(*str);
            }
        }
    }
    *errored = true;
    return new_unknown_value();
}

struct value read_nil(const char *str, bool *errored)
{
    
    if (*str == '_' && is_delimiter(*(str+1)))
        return new_nil_value();
    *errored = true;
    return new_unknown_value();
}

struct value read_value(const char *str)
{
    char *current = str;
    bool errored = false;
    struct value ret;
    enum value_type parsed_as;
    
    while(is_delimiter(*current)) {current++;} // chomp any starting nonsense
    if (*current == '#')
    {
        printf("PARSING AS CHAR\n");
        parsed_as = VAL_CHAR;
        ret = read_char(current, &errored);
        if (errored)
            goto error_state;
    }
    else if (*current == '_')
    {
        printf("PARSING AS NIL\n");
        parsed_as = VAL_NIL;
        ret = read_nil(current, &errored);
        if (errored)
            goto error_state;        
    }
    else if (isdigit(*current))
    {
        printf("PARSING AS INT\n");
        parsed_as = VAL_INT;
        ret = read_int(current, &errored);
        if (errored)
            goto error_state;        
    }
    else
    {
        parsed_as = VAL_UNKNOWN;
        ret = new_unknown_value();
        goto error_state;
    }

    return ret;
    
error_state:
    fprintf(stderr, "unable to parse %s, looked like a %s\n", current, type_strings[parsed_as]);
    return ret;
}
