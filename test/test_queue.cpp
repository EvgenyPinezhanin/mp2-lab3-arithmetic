#include<Collection.h>

#include<gtest.h>

TEST(Queue, can_create_queue_with_positive_number_of_elements)
{
    ASSERT_NO_THROW(Queue<int> q(50));
}

TEST(Queue, cant_create_queue_with_negative_number_of_elements)
{
    ASSERT_ANY_THROW(Queue<int> q(-5));
}

TEST(Queue, created_queue_is_empty)
{
    Queue<int> q(10);
    EXPECT_EQ(true, q.isEmpty());
}

TEST(Queue, can_create_copied_queue)
{
    Queue<int> q(10);
    ASSERT_NO_THROW(Queue<int> q1(q));
}

TEST(Queue, copied_queue_is_equal_to_source_one)
{
	Queue<int> q(10);
    q.push(1);
    q.push(2);
    q.push(4);

	Queue<int> q1(q);

	EXPECT_EQ(q, q1);
}