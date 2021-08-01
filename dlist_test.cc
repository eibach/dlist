#include <gtest/gtest.h>

#include "dlist.h"

struct dlist_node test_head;
struct dlist_node test_element1;
struct dlist_node test_element2;

// Demonstrate some basic assertions.
TEST(DlistTest, BasicAssertions) {
	dlist_init_node(&test_head);

	EXPECT_NE(dlist_is_empty(&test_head), 0);

	dlist_add(&test_element1, &test_head);

	EXPECT_EQ(dlist_is_empty(&test_head), 0);

	dlist_add(&test_element2, &test_head);

	EXPECT_EQ(dlist_is_empty(&test_head), 0);

	struct dlist_node *it;
	unsigned int ctr = 0;
	dlist_for_each(it, &test_head)
		ctr++;
	EXPECT_EQ(ctr, 2);
}
