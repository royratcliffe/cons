#include <cons.h>

struct cons **cons(struct cons **list, struct cons *cell) {
  cons_rplacd(cell, *list);
  *list = cell;
  return &cell->cdr;
}

void cons_reverse(struct cons **list) {
  /*
   * Maintain a pointer to the reversed list (initially CONS_NIL) and
   * iteratively traverse the original list. For each cell, save the next cell
   * (cdr) before reassigning the cdr of the current cell to point to the
   * reversed list. Then update the reversed list to be the current cell and
   * move to the next cell in the original list. This process continues until
   * reversing has traversed the entire original list, at which point the
   * reversed list will contain all the cells in reverse order.
   */
  struct cons *reversed = CONS_NIL;
  struct cons *cell = *list;
  while (CONS_NOT_NIL_P(cell)) {
    struct cons *cdr = cons_cdr(cell);
    cons_rplacd(cell, reversed);
    reversed = cell;
    cell = cdr;
  }
  *list = reversed;
}
