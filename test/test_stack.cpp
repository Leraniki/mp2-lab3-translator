#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_stack) {
	ASSERT_NO_THROW(Stack<int> s);
}

TEST(Stack, can_push_to_stack) {
	Stack<int> s;

	s.push(2);

	EXPECT_EQ(1,s.size());
}

TEST(Stack, can_pop_from_stack) {
	Stack<int> s;

	s.push(2);

	ASSERT_NO_THROW(s.pop());
}

TEST(Stack, can_top_stack) {
	Stack<int> s;

	s.push(2);
	s.push(5);

	ASSERT_NO_THROW(s.top());
	EXPECT_EQ(5, s.top());
}

TEST(Stack, check_empty_stack) {
	Stack<int> s;

	s.push(2);
	s.push(5);

	EXPECT_EQ(false, s.empty());
}

TEST(Stack, get_size_of_stack) {
	Stack<int> s;

	s.push(2);
	s.push(5);

	EXPECT_EQ(2, s.size());
}

TEST(Stack, pop_push) {
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);

	s.pop();
	s.pop();

	s.push(4);
	s.push(5);

	s.pop();
	s.pop();
	s.pop();

	EXPECT_EQ(0, s.size());
}