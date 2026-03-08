#include <cons_node.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int test_node(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  {
    struct cons_node node1 = CONS_NODE_NULL;
    struct cons_node node2 = CONS_NODE_NULL;
    struct cons_node node3 = CONS_NODE_NULL;

    (void)cons_node(&node2, &node1);
    (void)cons_node(&node3, &node1);

    assert(cons_car_node(&node1) == NULL);
    assert(cons_cdr_node(&node1) == NULL);
    assert(cons_sub_node(&node1) == &node3);

    assert(cons_car_node(&node2) == &node1);
    assert(cons_cdr_node(&node2) == NULL);
    assert(cons_sub_node(&node2) == NULL);

    assert(cons_car_node(&node3) == &node1);
    assert(cons_cdr_node(&node3) == &node2);
    assert(cons_sub_node(&node3) == NULL);

    (void)cons_node(&node2, NULL);
    assert(cons_car_node(&node1) == NULL);
    assert(cons_cdr_node(&node1) == NULL);
    assert(cons_sub_node(&node1) == &node3);
    assert(cons_car_node(&node2) == NULL);
    assert(cons_cdr_node(&node2) == NULL);
    assert(cons_sub_node(&node2) == NULL);
    assert(cons_car_node(&node3) == &node1);
    assert(cons_cdr_node(&node3) == NULL); /* now NULL */
    assert(cons_sub_node(&node3) == NULL);

    (void)cons_node(&node3, NULL);
    assert(cons_car_node(&node1) == NULL);
    assert(cons_cdr_node(&node1) == NULL);
    assert(cons_sub_node(&node1) == NULL);
    assert(cons_car_node(&node2) == NULL);
    assert(cons_cdr_node(&node2) == NULL);
    assert(cons_sub_node(&node2) == NULL);
    assert(cons_car_node(&node3) == NULL); /* now NULL */
    assert(cons_cdr_node(&node3) == NULL);
    assert(cons_sub_node(&node3) == NULL);
  }

  return EXIT_SUCCESS;
}
