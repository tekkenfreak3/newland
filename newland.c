#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cons.h"
#include "globals.h"
#include "value.h"

int main(int argc, char *argv[])
{
    printf("%s %f\n", name, version);

    struct value tester;
    tester = new_int_value(5);
    print_value(stdout, &tester);
    printf("\n");
    tester = new_double_value(9.31);

    print_value(stdout, &tester);
    printf("\n");
    tester = new_char_value('u');
    print_value(stdout, &tester);
    printf("\n");
    tester = new_nil_value();
    print_value(stdout, &tester);
    printf("\n");

    tester = new_cons_value(new_nil_value(), new_cons(new_double_value(.01), NULL));
    print_value(stdout, &tester);
    printf("\n");
    free(tester.value.cell->cdr);
    free(tester.value.cell);
    while (1)
    {
        char *in = readline(name "> ");
        add_history(in);
        printf("%s\n", in);
        free(in);
    }
    return 0;
}
