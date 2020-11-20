#include<Collection.h>

#include<gtest.h>

TEST(Stack, can_create_stack_with_positive_number_of_elements)
{
    ASSERT_NO_THROW(Stack<int> s(50));
}

TEST(Stack, cant_create_stack_with_negative_number_of_elements)
{
    ASSERT_ANY_THROW(Stack<int> s(-5));
}