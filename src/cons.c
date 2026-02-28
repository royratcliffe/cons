/* SPDX-License-Identifier: MIT */
/*!
 * \file cons.c
 * \brief Implementation of cons cell operations.
 * \details This file implements functions for manipulating cons cells, which
 * are fundamental data structures in Lisp-like languages. The functions create
 * new cons cells, delete cells from a list, and reverse a list of cons cells.
 * The operations work with the structure defined in \c cons.h to construct and
 * manipulate linked lists and other complex data structures.
 * \copyright 2026, Roy Ratcliffe, Northumberland, United Kingdom
 */

#include <cons.h>

struct cons **cons(struct cons **list, struct cons *cell) {
  cons_rplacd(cell, *list);
  *list = cell;
  return &cell->cdr;
}

struct cons *cons_delete(struct cons **list, void *car) {
  struct cons *deleted = CONS_NIL, *cell = *list;
  while (CONS_NOT_NIL_P(cell)) {
    if (cons_car(cell) == car) {
      /*
       * Found the cell to delete. If it's the head of the list, update the head
       * pointer to the next cell. Otherwise, link the previous cell to the next
       * cell, effectively removing the current cell from the list. Finally,
       * return the deleted cell.
       */
      if (CONS_NIL_P(deleted)) {
        *list = cons_cdr(cell);
      } else {
        cons_rplacd(deleted, cons_cdr(cell));
      }
      return cell;
    }
    deleted = cell;
    cell = cons_cdr(cell);
  }
  /*
   * If the cell is not found after traversing the entire list, return CONS_NIL
   * to indicate that no deletion occurred.
   */
  return CONS_NIL;
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
  struct cons *reversed = CONS_NIL, *cell = *list;
  while (CONS_NOT_NIL_P(cell)) {
    struct cons *cdr = cons_cdr(cell);
    cons_rplacd(cell, reversed);
    reversed = cell;
    cell = cdr;
  }
  *list = reversed;
}
