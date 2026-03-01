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

/*
 * for malloc and free
 */
#include <stdlib.h>

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
    struct cons *tail = cons_cdr(cell);
    cons_rplacd(cell, reversed);
    reversed = cell;
    cell = tail;
  }
  *list = reversed;
}

size_t cons_length(const struct cons *cell) {
  size_t length = 0;
  while (CONS_NOT_NIL_P(cell)) {
    length++;
    cell = cons_cdr(cell);
  }
  return length;
}

struct cons *cons_last(struct cons *cell) {
  if (CONS_NIL_P(cell)) {
    return CONS_NIL;
  }
  /*
   * The last cell in a list is the one having its cdr field equal to CONS_NIL.
   */
  struct cons *tail;
  while (CONS_NOT_NIL_P(tail = cons_cdr(cell))) {
    cell = tail;
  }
  return cell;
}

struct cons *cons_nth(struct cons *cell, size_t nth) {
  while (CONS_NOT_NIL_P(cell) && nth != 0) {
    cell = cons_cdr(cell);
    nth--;
  }
  return cell;
}

struct cons *cons_member(struct cons *cell, void *car) {
  for (; CONS_NOT_NIL_P(cell); cell = cons_cdr(cell)) {
    if (cons_car(cell) == car) {
      return cell;
    }
  }
  return CONS_NIL;
}

struct cons *cons_append(struct cons *cell1, struct cons *cell2) {
  struct cons *last = cons_last(cell1);
  if (CONS_NIL_P(last)) {
    return cell2;
  }
  cons_rplacd(last, cell2);
  return cell1;
}

struct cons *cons_heap(void *car) {
  struct cons *cell = (struct cons *)malloc(sizeof(struct cons));
  if (CONS_NOT_NIL_P(cell)) {
    cons_init(cell, car);
  }
  return cell;
}

void cons_free(struct cons *cell) { free(cell); }
