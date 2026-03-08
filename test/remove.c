#include <cons.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_remove(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  {
    struct cons *head = CONS_NIL;
    assert(CONS_NIL_P(cons_remove(&head, CONS_NIL)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head = CONS_NIL;
    cons(cons(cons(&head, &cell1), &cell2), &cell3);
    assert(cons_remove(&head, &cell1) == &cell1);
    assert(head == &cell2);
    assert(cons_cdr(&cell2) == &cell3);
    assert(CONS_NIL_P(cons_cdr(&cell3)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head = CONS_NIL;
    cons(&head, &cell1);
    cons(&head, &cell2);
    cons(&head, &cell3);
    assert(cons_remove(&head, &cell2) == &cell2);
    assert(head == &cell3);
    assert(cons_cdr(&cell3) == &cell1);
    assert(CONS_NIL_P(cons_cdr(&cell1)));
  }

  return EXIT_SUCCESS;
}
