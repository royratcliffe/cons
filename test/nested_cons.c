#include <cons.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_nested_cons(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  /*!
   * Tests nested cons operations.
   * This test case demonstrates the use of nested cons operations
   * to build a list in a single expression.
   */
  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *list = CONS_NIL;
    cons(cons(cons(&list, &cell1), &cell2), &cell3);
    for (struct cons *cell = list; CONS_NOT_NIL_P(cell); cell = cons_cdr(cell)) {
      assert((uintptr_t)cons_car(cell) == 1 || (uintptr_t)cons_car(cell) == 2 || (uintptr_t)cons_car(cell) == 3);
    }
    assert(list == &cell1);
    assert(cons_cdr(&cell1) == &cell2);
    assert(cons_cdr(&cell2) == &cell3);
    assert(CONS_NIL_P(cons_cdr(&cell3)));
  }

  /*
   * Tests another nested cons scenario.
   * This test case demonstrates a different way to build a list
   * using nested cons operations.
   */
  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head = CONS_NIL;
    cons(cons(&head, &cell1), &cell2);
    cons(&head, &cell3);
    assert(head == &cell3);
    assert(cons_cdr(&cell3) == &cell1);
    assert(cons_cdr(&cell1) == &cell2);
    assert(CONS_NIL_P(cons_cdr(&cell2)));
  }

  return EXIT_SUCCESS;
}
