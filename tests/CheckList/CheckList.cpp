#include "gtest/gtest.h"
#include <stdexcept>
#include "../../include/CheckList.h"

TEST(CheckListTask, construct_and_destruct) {
    ASSERT_NO_THROW(CheckListTask("TestCase", true));
}

TEST(CheckListTask, bool_conversion) {
    CheckListTask task1("", true);
    ASSERT_TRUE(task1);
    CheckListTask task2("", false);
    ASSERT_FALSE(task2);
}

TEST(CheckListTask, set_and_get) {
    CheckListTask task("TestCase", true);
    ASSERT_EQ(task.caption(), "TestCase");
    ASSERT_TRUE(task.checked());
    task.setChecked(false);
    ASSERT_FALSE(task.checked());
    task.setCaption("Another TestCase");
    ASSERT_EQ(task.caption(), "Another TestCase");
}

TEST(CheckListTask, eq_test) {
    CheckListTask task1("TestCase", true);
    CheckListTask task2("TestCase", false);
    ASSERT_FALSE(task1 == task2);
    task2.setChecked(true);
    ASSERT_TRUE(task1 == task2);
    task2.setCaption("Another TestCase");
    ASSERT_FALSE(task1 == task2);
}

TEST(CheckListTask, ne_test) {
    CheckListTask task1("TestCase", true);
    CheckListTask task2("TestCase", false);
    ASSERT_TRUE(task1 != task2);
    task2.setChecked(true);
    ASSERT_FALSE(task1 != task2);
    task2.setCaption("Another TestCase");
    ASSERT_TRUE(task1 != task2);
}

TEST(CheckList, construct_and_destruct) {
    ASSERT_NO_THROW(CheckList());
}

TEST(CheckList, add_remove) {
    CheckList list;
    list.add(0, "TestCase");
    ASSERT_EQ(list.count(), 1);
    CheckListTask task("Another TestCase");
    list.add(1, task);
    ASSERT_EQ(list.count(), 2);
    list.remove(0);
    ASSERT_EQ(list.count(), 1);
}

TEST(CheckList, at) {
    CheckList list;
    list.add(0, "TestCase");
    ASSERT_EQ(list.at(0), list[0]);
    ASSERT_EQ(list.at(0).caption(), "TestCase");
}

TEST(CheckList, on_add_no_rewrite) {
    CheckList list;
    list.add(0, "TestCase");
    ASSERT_THROW(list.add(0, "Another TestCase"), std::logic_error);
    ASSERT_EQ(list.count(), 1);
    ASSERT_EQ(list.at(0).caption(), "TestCase");
}

TEST(CheckList, pop) {
    CheckList list;
    CheckListTask task("TestCase");
    list.add(0, task);
    ASSERT_EQ(task, list.pop(0));
    ASSERT_EQ(list.count(), 0);
}

TEST(CheckList, index) {
    CheckList list;
    list.add(0, "TestCase", true);
    list.add(1, "Another TestCase");
    list.add(2, "One TestCase");
    list.add(3, "One TestCase");
    ASSERT_EQ(list.index("TestCase", true), 0);
    EXPECT_EQ(list.index("One TestCase", false), 2);
    ASSERT_THROW(list.index("More TestCases", false), std::out_of_range);
}

TEST(CheckList, data) {
    CheckList list;
    CheckListTypes::dataType data;
    list.add(0, "TestCase");
    ASSERT_NE(data, list.data());
    list.data() = data;
    ASSERT_EQ(data, list.data());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
