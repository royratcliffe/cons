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
    struct cons *head = CONS_NIL;
    assert(cons_length(head) == 0);
    assert(CONS_NIL_P(cons_last(head)));
    cons(&head, &cell1);
    cons(&head, &cell2);
    cons(&head, &cell3);
    assert(cons_length(head) == 3);
    assert(cons_last(head) == &cell1);
    assert(cons_nth(head, 0) == &cell3);
    assert(cons_nth(head, 1) == &cell2);
    assert(cons_nth(head, 2) == &cell1);
    for (struct cons *cell = head; CONS_NOT_NIL_P(cell); cell = cons_cdr(cell)) {
      assert((uintptr_t)cons_car(cell) == 3 || (uintptr_t)cons_car(cell) == 2 || (uintptr_t)cons_car(cell) == 1);
    }
    assert(head == &cell3);
    assert(cons_cdr(&cell3) == &cell2);
    assert(cons_cdr(&cell2) == &cell1);
    assert(CONS_NIL_P(cons_cdr(&cell1)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head = CONS_NIL;
    cons(&head, &cell1);
    cons(&head, &cell2);
    cons(&head, &cell3);
    cons_reverse(&head);
    for (struct cons *cell = head; CONS_NOT_NIL_P(cell); cell = cons_cdr(cell)) {
      assert((uintptr_t)cons_car(cell) == 1 || (uintptr_t)cons_car(cell) == 2 || (uintptr_t)cons_car(cell) == 3);
    }
    assert(head == &cell1);
    assert(cons_cdr(&cell1) == &cell2);
    assert(cons_cdr(&cell2) == &cell3);
    assert(CONS_NIL_P(cons_cdr(&cell3)));
  }

  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head1 = CONS_NIL;
    cons_prepend(cons_prepend(cons_prepend(&head1, &cell1), &cell2), &cell3);
    assert(head1 == &cell3);
    assert(cons_cdr(&cell3) == &cell2);
    assert(cons_cdr(&cell2) == &cell1);
    assert(cons_cdr(&cell1) == CONS_NIL);
  }

  return EXIT_SUCCESS;
}
