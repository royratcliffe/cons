#include <cons.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_append(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  /*
   * Tests appending two lists of cons cells.
   * This test case demonstrates the use of the cons_append function to
   * concatenate two lists of cons cells and verifies that the resulting list
   * has the expected structure and contents.
   *
   * In this test, create two separate lists: the first list contains a
   * single cons cell with the value 1, and the second list contains two cons
   * cells with the values 2 and 3. Then append the second list to the first
   * list using the cons_append function. After the append operation, verify
   * that the first list now contains all three cons cells in the correct order
   * (1, 2, 3) and that the second list is correctly linked to the first list.
   * Finally, we check that the last cell in the combined list points to
   * CONS_NIL, indicating the end of the list.
   */
  {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons cell3 = CONS((void *)3, CONS_NIL);
    struct cons *head1 = CONS_NIL;
    struct cons *head2 = CONS_NIL;
    cons(&head1, &cell1);
    cons(cons(&head2, &cell2), &cell3);
    assert(cons_append(head1, head2) == head1);
    assert(cons_cdr(&cell1) == &cell2);
    assert(cons_cdr(&cell2) == &cell3);
    assert(CONS_NIL_P(cons_cdr(&cell3)));
  }

  /*
   * Tests appending a non-empty list to an empty list.
   * This test case verifies that when cons_append is called with an empty
   * first list (CONS_NIL) and a non-empty second list, the function returns
   * the second list unchanged. The test creates a second list containing two
   * cons cells with values 2 and 3, and appends it to an empty first list.
   * After the operation, the result should be the second list itself, and
   * the first list's unused cell should remain unaffected.
   */
  {
    struct cons *cell2 = cons_heap((void *)2);
    struct cons *cell3 = cons_heap((void *)3);
    struct cons *head1 = CONS_NIL;
    struct cons *head2 = CONS_NIL;
    cons(cons(&head2, cell2), cell3);
    assert(cons_append(head1, head2) == head2);
    assert(cons_cdr(cell2) == cell3);
    assert(CONS_NIL_P(cons_cdr(cell3)));
    cons_free(cell2);
    cons_free(cell3);
  }

  return EXIT_SUCCESS;
}
