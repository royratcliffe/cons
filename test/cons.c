#include <cons.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_cons(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *list = CONS_NIL;
    cons(&list, &cell1);
    cons(&list, &cell2);
    cons(&list, &cell3);
    assert(cons_length(list) == 3);
    for (struct cons *cell = list; CONS_NOT_NIL_P(cell); cell = cons_cdr(cell)) {
      assert((uintptr_t)cons_car(cell) == 3 || (uintptr_t)cons_car(cell) == 2 || (uintptr_t)cons_car(cell) == 1);
    }
    assert(list == &cell3);
    assert(cons_cdr(&cell3) == &cell2);
    assert(cons_cdr(&cell2) == &cell1);
    assert(CONS_NIL_P(cons_cdr(&cell1)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *list = CONS_NIL;
    cons(&list, &cell1);
    cons(&list, &cell2);
    cons(&list, &cell3);
    cons_reverse(&list);
    for (struct cons *cell = list; CONS_NOT_NIL_P(cell); cell = cons_cdr(cell)) {
      assert((uintptr_t)cons_car(cell) == 1 || (uintptr_t)cons_car(cell) == 2 || (uintptr_t)cons_car(cell) == 3);
    }
    assert(list == &cell1);
    assert(cons_cdr(&cell1) == &cell2);
    assert(cons_cdr(&cell2) == &cell3);
    assert(CONS_NIL_P(cons_cdr(&cell3)));
  }

  return EXIT_SUCCESS;
}
