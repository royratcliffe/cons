#include <cons.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_delete(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  {
    struct cons *list = CONS_NIL;
    assert(CONS_NIL_P(cons_delete(&list, NULL)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *list = CONS_NIL;
    cons(cons(cons(&list, &cell1), &cell2), &cell3);
    assert(cons_delete(&list, (void *)1) == &cell1);
    assert(list == &cell2);
    assert(cons_cdr(&cell2) == &cell3);
    assert(CONS_NIL_P(cons_cdr(&cell3)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *list = CONS_NIL;
    cons(&list, &cell1);
    cons(&list, &cell2);
    cons(&list, &cell3);
    assert(cons_delete(&list, (void *)2) == &cell2);
    assert(list == &cell3);
    assert(cons_cdr(&cell3) == &cell1);
    assert(CONS_NIL_P(cons_cdr(&cell1)));
  }

  return EXIT_SUCCESS;
}
