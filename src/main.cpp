#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/Framework.hpp>

/*int main()
{
    bpf::String str = "é This is a test !";
    bpf::Tuple<int, float, double> tp;
    bpf::List<bpf::ModuleEntry *> testlst;

    tp.Get<0>() = 42;
    tp.Get<1>() = 42.42f;
    tp.Get<2>() = 423.423;

    std::cout << "--------------" << std::endl;
    std::cout << tp.Size() << std::endl;
    std::cout << tp.Get<int>() << std::endl;
    std::cout << tp.Get<float>() << std::endl;
    std::cout << tp.Get<double>() << std::endl;
    std::cout << "--------------" << std::endl;

    std::cout << str.Size() << std::endl;
    std::cout << str.Len() << std::endl;
    std::cout << (str[0] == bpf::String::UTF32("é")) << std::endl;

    bpf::DateTime dt = bpf::DateTime::LocalTime();
    std::cout << *dt.ToString() << std::endl;
    bpf::DateTime dt1 = dt + bpf::DateTime(3600) + bpf::DateTime(61);
    std::cout << *dt1.ToString() << std::endl;
    
    assert(dt < dt1);
    assert(dt1 > dt);
    assert(dt == dt);
    assert(dt1 == dt1);
    assert(dt != dt1);
    assert(dt1 != dt);

    system("PAUSE");
}*/

TEST(String, Create)
{
    bpf::String str = "This is a test !";
}

TEST(String, CreateUnicode)
{
    bpf::String str = " é è à ù € This is a test !";
}

TEST(String, Copy)
{
    bpf::String str = " é è à ù € This is a test !";

    bpf::String ss = str;
    for (int i = 0; i < 100; ++i)
        ss = str;
}

TEST(String, UTF8)
{
    bpf::String str = " é è à ù € This is a test !";

    EXPECT_TRUE(str[0] == bpf::String::UTF32(" "));
    EXPECT_TRUE(str[1] == bpf::String::UTF32("é"));
    EXPECT_TRUE(str[3] == bpf::String::UTF32("è"));
    EXPECT_TRUE(str[5] == bpf::String::UTF32("à"));
    EXPECT_TRUE(str[7] == bpf::String::UTF32("ù"));
    EXPECT_TRUE(str[9] == bpf::String::UTF32("€"));
    EXPECT_TRUE(str[11] == bpf::String::UTF32("T"));
}

TEST(String, Compare)
{
    bpf::String s = "abc";
    bpf::String s1 = "def";
    std::string s2 = "abc";
    std::string s3 = "def";

    EXPECT_EQ(s == s1, s2 == s3);
    EXPECT_EQ(s1 == s, s3 == s2);
    EXPECT_EQ(s != s1, s2 != s3);
    EXPECT_EQ(s1 != s, s3 != s2);
    EXPECT_EQ(s < s1, s2 < s3);
    EXPECT_EQ(s1 > s, s3 > s2);
}

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return (RUN_ALL_TESTS());
}
