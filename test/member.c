#include <cons.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_member(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head = CONS_NIL;
    cons(cons(cons(&head, &cell1), &cell2), &cell3);
    assert(cons_member(head, (void *)1) == &cell1);
    assert(cons_member(head, (void *)2) == &cell2);
    assert(cons_member(head, (void *)3) == &cell3);
    assert(CONS_NIL_P(cons_member(head, (void *)4)));
  }

  return EXIT_SUCCESS;
}
