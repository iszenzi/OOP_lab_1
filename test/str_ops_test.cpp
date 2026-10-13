#include "lab01/str_ops.hpp"

#include <gtest/gtest.h>

TEST(StrOpsTest, EmptyStringHasZeroLength) {
    EXPECT_EQ(str_len(""), 0U);
    EXPECT_EQ(str_count_words(""), 0U);
}

TEST(StrOpsTest, NullStringHasZeroLength) {
    EXPECT_EQ(str_len(nullptr), 0U);
    EXPECT_EQ(str_count_words(nullptr), 0U);
}

TEST(StrOpsTest, LengthIncludesSpaces) {
    EXPECT_EQ(str_len("hello world"), 11U);
}

TEST(StrOpsTest, CopiesStringIntoExactSizeBuffer) {
    char buffer[6]{};

    str_copy(buffer, "hello");

    EXPECT_STREQ(buffer, "hello");
    EXPECT_EQ(buffer[5], '\0');
}

TEST(StrOpsTest, CopiesEmptyStringTerminator) {
    char buffer[]{'x'};

    str_copy(buffer, "");

    EXPECT_EQ(buffer[0], '\0');
}

TEST(StrOpsTest_Fail, NullCopySourcePreservesDestination) {
    char buffer[]{'a', 'b', '\0'};

    str_copy(buffer, nullptr);

    EXPECT_STREQ(buffer, "ab");
    str_copy(nullptr, buffer);
    EXPECT_STREQ(buffer, "ab");
}

TEST(StrOpsTest, AllocatesIndependentCopy) {
    char source[]{'a', 'b', 'c', '\0'};
    char* copy = str_alloc(source);

    EXPECT_NE(copy, nullptr);
    EXPECT_NE(copy, source);
    EXPECT_STREQ(copy, "abc");
    if (copy != nullptr) {
        copy[0] = 'x';
        EXPECT_STREQ(copy, "xbc");
    }
    EXPECT_STREQ(source, "abc");

    str_delete(copy);
    EXPECT_EQ(copy, nullptr);
    str_delete(copy);
    EXPECT_EQ(copy, nullptr);
}

TEST(StrOpsTest, AllocatesEmptyString) {
    char* copy = str_alloc("");

    EXPECT_NE(copy, nullptr);
    EXPECT_STREQ(copy, "");

    str_delete(copy);
}

TEST(StrOpsTest_Fail, NullAllocationSourceReturnsNull) {
    char* copy = str_alloc(nullptr);

    EXPECT_EQ(copy, nullptr);

    str_delete(copy);
}

TEST(StrOpsTest, SpacesHaveNoWords) {
    EXPECT_EQ(str_count_words("   "), 0U);
}

TEST(StrOpsTest, IgnoresLeadingTrailingAndRepeatedSpaces) {
    EXPECT_EQ(str_count_words("  hello   world test  "), 3U);
}

TEST(StrOpsTest, FindsSubstringInAssignmentExample) {
    int position{-1};

    const bool found = str_find_substr("hello world test", "world", position);

    ASSERT_TRUE(found);
    EXPECT_EQ(position, 6);
}

TEST(StrOpsTest, ResetsMatchAfterPartialMismatch) {
    int position{-1};

    ASSERT_TRUE(str_find_substr("aabab", "ab", position));
    EXPECT_EQ(position, 1);
}

TEST(StrOpsTest, FindsEmptySubstringAtZero) {
    int position{-1};

    ASSERT_TRUE(str_find_substr("abc", "", position));
    EXPECT_EQ(position, 0);
    ASSERT_TRUE(str_find_substr("", "", position));
    EXPECT_EQ(position, 0);
}

TEST(StrOpsTest_Fail, MissingSubstringPreservesPosition) {
    int position{42};

    EXPECT_FALSE(str_find_substr("hello world test", "xyz", position));
    EXPECT_EQ(position, 42);
    EXPECT_FALSE(str_find_substr("ab", "abc", position));
    EXPECT_EQ(position, 42);
    EXPECT_FALSE(str_find_substr(nullptr, "a", position));
    EXPECT_EQ(position, 42);
    EXPECT_FALSE(str_find_substr("abc", nullptr, position));
    EXPECT_EQ(position, 42);
}
