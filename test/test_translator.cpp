#include "list.h"

#include <gtest.h>

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> l(5));
}

TEST(List, can_copy_list)
{
	List<int> l1(5);
	ASSERT_NO_THROW(List<int> l2(l1));
}

TEST(List, copied_list_has_its_own_memory) 
{

	int n = 5;
	List<int> l1(n);
	for (int i = 0; i < n; i++)
		l1[i] = 2;

	List<int> l2(l1);

	l2[0] = 10;

	ASSERT_EQ(l1[0], 2);
	ASSERT_EQ(l2[0], 10);
}

TEST(List, can_assign_lists_of_equal_size) 
{

	List<int> l1(5);
	List<int> l2(5);

	ASSERT_NO_THROW(l1 = l2);
}

TEST(List, can_assign_lists_of_not_equal_size) 
{

	List<int> l1(5);
	List<int> l2(10);

	ASSERT_NO_THROW(l1 = l2);
}

TEST(List, assign_operator_change_list_size) 
{

	List<int> l1(5);
	List<int> l2(10);

	l1 = l2;

	ASSERT_EQ(l1.size(), l2.size());
}

TEST(List, can_assign_list_to_itself)
{
	List<int> l(5);

	ASSERT_NO_THROW(l = l);

}

TEST(List, print)
{
	List<int> l(5);

	l.print();
	std::cout << "\n" << std::endl;

}

TEST(List, correctly_retrun_size) 
{
	List<int> l(5);

	EXPECT_EQ(5, l.size());
}


TEST(List, correctly_insert_elem) 
{
	List<int> l(5);

	l.insert(2, l.find(0));

	EXPECT_EQ(6, l.size());
	EXPECT_EQ(l[1], 2);
}

TEST(List, correctly_insert_elem_to_empty_list)
{
	List<int> l;

	l.insert_front(2);

	EXPECT_EQ(1, l.size());
	EXPECT_EQ(l[0], 2);
	
}


TEST(List, correctly_insert_front_elem)
{
	List<int> l(5);

	l.insert_front(2);

	EXPECT_EQ(6, l.size());
	EXPECT_EQ(l[0], 2);
}

TEST(List, correctly_erase_elem)
{
	List<int> l(5);
	int k = 0;
	for (int i = 0; i < 5; i++) {
		l[i]+=k;
		k++;

	}

	l.erase(l.find(0));

	EXPECT_EQ(4, l.size());
	EXPECT_EQ(l[1], 2);

}

TEST(List, correctly_erase_elem_from_empty)
{
	List<int> l;

	ASSERT_ANY_THROW(l.erase_front());
}

TEST(List, correctly_erase_front_elem)
{
	List<int> l(5);
	int k = 0;
	for (int i = 0; i < 5; i++) {
		l[i] += k;
		k++;
	}

	l.erase_front();

	EXPECT_EQ(4, l.size());
	EXPECT_EQ(l[0], 1);

}

TEST(List, can_set_and_get_elem)
{
	List<int> l(5);
	
	l[1] = 4;

	EXPECT_EQ(4, l[1]);
}

TEST(List, can_find_elem)
{
	List<int> l(5);
	int k = 0;
	for (int i = 0; i < 5; i++) {
		l[i] += k;
		k++;
	}

	EXPECT_EQ(l.find(0), l.get_first());
}

//задача #5
TEST(List, task_5_not_even) {
	List<int> l(5);
	int k = 0;
	for (int i = 0; i < 5; i++) {
		l[i] += k;
		k++;
	}
	l.print();
	std::cout << '\n' << std::endl;
	//0 1 2 3 4  
	l.del_mid_elem();
	l.print();

	//0 1 4 
	EXPECT_EQ(3, l.size());
	EXPECT_EQ(l[0], 0);
	EXPECT_EQ(l[1], 1);
	EXPECT_EQ(l[2], 4);
}

TEST(List, task_5_even) {
	List<int> l(6);
	int k = 0;
	for (int i = 0; i < 6; i++) {
		l[i] += k;
		k++;
	}
	l.print();
	std::cout << '\n' << std::endl;
	//0 1 2 3 4 5 
	l.del_mid_elem();
	l.print();

	//0 1 2 4 5 
	EXPECT_EQ(5, l.size());
	EXPECT_EQ(l[0], 0);
	EXPECT_EQ(l[1], 1);
	EXPECT_EQ(l[2], 2);
	EXPECT_EQ(l[3], 4);
	EXPECT_EQ(l[4], 5);
}