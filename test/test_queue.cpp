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

//TEST(Queue, created_queue_is_not_full)
//{
//    Queue<int> q(10);
//    EXPECT_EQ(false, q.isFull());
//}
