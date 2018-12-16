﻿#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/String.hpp>
#include <Framework/Array.hpp>
#include <Framework/EvalException.hpp>

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

TEST(String, Basic)
{
    bpf::String s("test");
    ASSERT_STREQ(*s, "test");
    ASSERT_TRUE(s.Len() == 4);
    ASSERT_TRUE(s.Size() == 4);
    s = 'A';
    ASSERT_STREQ(*s, "A");
}

TEST(String, UTF8CharToUTF32)
{
    //Source : FileFormat.info
    EXPECT_TRUE(bpf::String::UTF32("É") == 201);
    EXPECT_TRUE(bpf::String::UTF32("é") == 233);
    EXPECT_TRUE(bpf::String::UTF32("€") == 8364);
    EXPECT_TRUE(bpf::String::UTF32("¥") == 165);
    EXPECT_TRUE(bpf::String::UTF32("▦") == 9638);
    EXPECT_TRUE(bpf::String::UTF32("a") == 'a');
}

TEST(String, ByteAt)
{
    bpf::String s = "testÉé€test¥▦test";
    EXPECT_TRUE(s.ByteAt(3) == 't');
    EXPECT_TRUE(s.ByteAt(4) == (char)0xC3);
    EXPECT_TRUE(s.ByteAt(s.Size() - 1) == 't');
}

TEST(String, OperatorPlus)
{
    bpf::String s("init");
    s = s + ' ' + 42 + ',' + " the test, " + 42.42f;
    EXPECT_STREQ(*s, "init 42, the test, 42.42");
}

TEST(String, OperatorPlusEqual)
{
    bpf::String s("init");
    s += ' ';
    s += 42;
    s += ',';
    s += " the test, ";
    s += 42.42f;
    EXPECT_STREQ(*s, "init 42, the test, 42.42");
}

TEST(String, OperatorEquall)
{
    bpf::String s("init");
    s += ' ';
    s += 42;
    s += ',';
    s += " the test, ";
    s += 42.42f;
    bpf::String s1("init");
    s1 = s1 + ' ' + 42 + ',' + " the test, " + 42.42f;
    EXPECT_STREQ(*s, "init 42, the test, 42.42");
    EXPECT_STREQ(*s1, "init 42, the test, 42.42");
    EXPECT_TRUE(s == s1);
    EXPECT_TRUE(!(s != s1));
}

TEST(String, OperatorGreaterLess)
{
    bpf::String s("init");
    s += ' ';
    s += 42;
    s += ',';
    s += " the test, ";
    s += 42.42f;
    bpf::String s1("init");
    s1 = s1 + ' ' + 42 + ',' + " the test, " + 42.42f;
    EXPECT_STREQ(*s, "init 42, the test, 42.42");
    EXPECT_STREQ(*s1, "init 42, the test, 42.42");
    EXPECT_TRUE(!(s > s1));
    EXPECT_TRUE(!(s < s1));
    EXPECT_TRUE(bpf::String("TT") < bpf::String("qq"));
    EXPECT_TRUE(bpf::String("qq") > bpf::String("TT"));
}

TEST(String, Replace)
{
    bpf::String s = bpf::String("      test      ,     \t    \t  \t\t\t              yay").Replace(" ", "").Replace("\t", "");
    EXPECT_STREQ(*s, "test,yay");

    bpf::String s1 = bpf::String("a/b/c/d/e/f/").Replace("/", "\\");
    EXPECT_STREQ(*s1, "a\\b\\c\\d\\e\\f\\");
    s1 = bpf::String("a/ b/ c/ d/ e/ f/").Replace("/", "\\");
    EXPECT_STRNE(*s1, "a\\b\\c\\d\\e\\f\\");
}

TEST(String, GetUTF32CodePoint)
{
    bpf::String s = "testÉé€test¥▦test";
    EXPECT_TRUE(s.Len() == 17);
    EXPECT_TRUE(s[0] == bpf::String::UTF32("t"));
    EXPECT_TRUE(s[4] == bpf::String::UTF32("É"));
    EXPECT_TRUE(s[12] == bpf::String::UTF32("▦"));
    EXPECT_TRUE(s[11] == bpf::String::UTF32("¥"));
    EXPECT_TRUE(s[s.Len() - 1] == bpf::String::UTF32("t"));
}

TEST(String, LenAndSize)
{
    bpf::String s = "testÉé€test¥▦test";
    EXPECT_TRUE(s.Len() == 17);
    EXPECT_TRUE(s.Size() == strlen("testÉé€test¥▦test"));
}

TEST(String, IsNumeric)
{
    bpf::String s = "1234567890";
    bpf::String s1 = "42.42";
    bpf::String s2 = "42";
    bpf::String s3 = "42.";
    bpf::String s4 = ".42";
    bpf::String s5 = "a42";
    bpf::String s6 = "qq";
    bpf::String s7 = "";    
    bpf::String s8 = "\n";
    bpf::String s9 = "éèù";
    EXPECT_TRUE(s.IsNumeric());
    EXPECT_TRUE(s1.IsNumeric());
    EXPECT_TRUE(s2.IsNumeric());
    EXPECT_TRUE(s3.IsNumeric());
    EXPECT_TRUE(s4.IsNumeric());
    EXPECT_TRUE(!s5.IsNumeric());
    EXPECT_TRUE(!s6.IsNumeric());
    EXPECT_TRUE(!s7.IsNumeric());
    EXPECT_TRUE(!s8.IsNumeric());
    EXPECT_TRUE(!s9.IsNumeric());
}

TEST(String, ToUpper)
{
    bpf::String s("test");
    EXPECT_STREQ(*s, "test");
    s = s.ToUpper();
    EXPECT_STREQ(*s, "TEST");
}

TEST(String, ToLower)
{
    bpf::String s("TEST");
    EXPECT_STREQ(*s, "TEST");
    s = s.ToLower();
    EXPECT_STREQ(*s, "test");
}

TEST(String, IndexOfSingleChar)
{
    bpf::String utf8 = "testÉé€test¥▦testa";
    bpf::String ascii = "youhou";
    EXPECT_TRUE(utf8.IndexOf('t') == 0);
    EXPECT_TRUE(utf8.IndexOf('a') == utf8.Len() - 1);
    EXPECT_TRUE(ascii.IndexOf('y') == 0);
    EXPECT_TRUE(ascii.IndexOf('u') == 2);
    EXPECT_TRUE(ascii.IndexOf('A') == -1);
    EXPECT_TRUE(utf8.IndexOf('G') == -1);
}

TEST(String, IndexOfString)
{
    bpf::String utf8 = "testÉé€test¥▦testabc";
    bpf::String ascii = "youhou";
    EXPECT_TRUE(utf8.IndexOf("t") == 0);
    EXPECT_TRUE(utf8.IndexOf("É") == 4);
    EXPECT_TRUE(utf8.IndexOf("▦") == 12);
    EXPECT_TRUE(utf8.IndexOf("abc") == utf8.Len() - 3);
    EXPECT_TRUE(utf8.IndexOf("doesnotexist") == -1);
    EXPECT_TRUE(ascii.IndexOf("doesnotexist") == -1);
    EXPECT_TRUE(ascii.IndexOf("hou") == 3);
}

TEST(String, LastIndexOfSingleChar)
{
    bpf::String utf8 = "testÉé€test¥▦testa";
    bpf::String ascii = "youhou";
    EXPECT_TRUE(utf8.LastIndexOf('t') == utf8.Len() - 2);
    EXPECT_TRUE(utf8.LastIndexOf('a') == utf8.Len() - 1);
    EXPECT_TRUE(ascii.LastIndexOf('y') == 0);
    EXPECT_TRUE(ascii.LastIndexOf('u') == ascii.Len() - 1);
    EXPECT_TRUE(ascii.LastIndexOf('A') == -1);
    EXPECT_TRUE(utf8.LastIndexOf('G') == -1);
}

TEST(String, LastIndexOfString)
{
    bpf::String utf8 = "testÉé€test¥▦testabc";
    bpf::String ascii = "youhou";
    EXPECT_TRUE(utf8.LastIndexOf("t") == utf8.Len() - 4);
    EXPECT_TRUE(utf8.LastIndexOf("É") == 4);
    EXPECT_TRUE(utf8.LastIndexOf("▦") == 12);
    EXPECT_TRUE(utf8.LastIndexOf("abc") == utf8.Len() - 3);
    EXPECT_TRUE(utf8.LastIndexOf("doesnotexist") == -1);
    EXPECT_TRUE(ascii.LastIndexOf("doesnotexist") == -1);
    EXPECT_TRUE(ascii.LastIndexOf("hou") == 3);
}

TEST(String, ExplodeSingleChar)
{
    bpf::String s = "this is a test";
    bpf::String s1 = "this      is   a                 test";
    bpf::String s2 = "         this      is   a                 test         ";
    bpf::List<bpf::String> data;
    bpf::List<bpf::String> data1;
    bpf::List<bpf::String> data2;

    s.Explode(data, ' ');
    s1.Explode(data1, ' ');
    s2.Explode(data2, ' ');
    EXPECT_TRUE(data.Size() == data1.Size());
    EXPECT_TRUE(data.Size() == data2.Size());
    EXPECT_TRUE(data.Size() == 4);
    EXPECT_STREQ("this", *data[0]);
    EXPECT_STREQ("is", *data[1]);
    EXPECT_STREQ("a", *data[2]);
    EXPECT_STREQ("test", *data[3]);
    EXPECT_STREQ("this", *data1[0]);
    EXPECT_STREQ("is", *data1[1]);
    EXPECT_STREQ("a", *data1[2]);
    EXPECT_STREQ("test", *data1[3]);
    EXPECT_STREQ("this", *data2[0]);
    EXPECT_STREQ("is", *data2[1]);
    EXPECT_STREQ("a", *data2[2]);
    EXPECT_STREQ("test", *data2[3]);
}

TEST(String, ExplodeOr)
{
    bpf::String s = "this is a, test";
    bpf::List<bpf::String> data;

    s.ExplodeOr(data, " ,");
    EXPECT_TRUE(data.Size() == 4);
    EXPECT_STREQ("this", *data[0]);
    EXPECT_STREQ("is", *data[1]);
    EXPECT_STREQ("a", *data[2]);
    EXPECT_STREQ("test", *data[3]);
}

TEST(String, ExplodeString)
{
    bpf::String s = "this  is  a  test";
    bpf::String s1 = "this      is    a                  test";
    bpf::String s2 = "        this      is    a                  test          ";
    bpf::String s3 = "this is a test";
    bpf::List<bpf::String> data;
    bpf::List<bpf::String> data1;
    bpf::List<bpf::String> data2;
    bpf::List<bpf::String> data3;

    s.Explode(data, "  ");
    s1.Explode(data1, "  ");
    s2.Explode(data2, "  ");
    s3.Explode(data3, " ");
    EXPECT_TRUE(data.Size() == data1.Size());
    EXPECT_TRUE(data.Size() == data2.Size());
    EXPECT_TRUE(data3.Size() == data.Size());
    EXPECT_TRUE(data.Size() == 4);
    EXPECT_STREQ("this", *data[0]);
    EXPECT_STREQ("is", *data[1]);
    EXPECT_STREQ("a", *data[2]);
    EXPECT_STREQ("test", *data[3]);
    EXPECT_STREQ("this", *data1[0]);
    EXPECT_STREQ("is", *data1[1]);
    EXPECT_STREQ("a", *data1[2]);
    EXPECT_STREQ("test", *data1[3]);
    EXPECT_STREQ("this", *data2[0]);
    EXPECT_STREQ("is", *data2[1]);
    EXPECT_STREQ("a", *data2[2]);
    EXPECT_STREQ("test", *data2[3]);
    EXPECT_STREQ("this", *data3[0]);
    EXPECT_STREQ("is", *data3[1]);
    EXPECT_STREQ("a", *data3[2]);
    EXPECT_STREQ("test", *data3[3]);
}

TEST(String, ExplodeIgnoreSingleChar)
{
    bpf::String s = "this 'is a' test";
    bpf::String s1 = "this      'is   a'                 test";
    bpf::String s2 = "         this      'is   a'                 test         ";
    bpf::List<bpf::String> data;
    bpf::List<bpf::String> data1;
    bpf::List<bpf::String> data2;

    s.ExplodeIgnore(data, ' ', '\'');
    s1.ExplodeIgnore(data1, ' ', '\'');
    s2.ExplodeIgnore(data2, ' ', '\'');
    EXPECT_TRUE(data.Size() == data1.Size());
    EXPECT_TRUE(data.Size() == data2.Size());
    EXPECT_TRUE(data.Size() == 3);
    EXPECT_STREQ("this", *data[0]);
    EXPECT_STREQ("'is a'", *data[1]);
    EXPECT_STREQ("test", *data[2]);
    EXPECT_STREQ("this", *data1[0]);
    EXPECT_STREQ("'is   a'", *data1[1]);
    EXPECT_STREQ("test", *data1[2]);
    EXPECT_STREQ("this", *data2[0]);
    EXPECT_STREQ("'is   a'", *data2[1]);
    EXPECT_STREQ("test", *data2[2]);
}

TEST(String, ExplodeIgnoreString_Test1)
{
    bpf::String s = "this  'is  a'  test";
    bpf::String s1 = "this      'is   a'                  test";
    bpf::String s2 = "        this      'is   a'                test         ";
    bpf::List<bpf::String> data;
    bpf::List<bpf::String> data1;
    bpf::List<bpf::String> data2;

    s.ExplodeIgnore(data, "  ", "'");
    s1.ExplodeIgnore(data1, "  ", "'");
    s2.ExplodeIgnore(data2, "  ", "'");
    EXPECT_TRUE(data.Size() == data1.Size());
    EXPECT_TRUE(data.Size() == data2.Size());
    EXPECT_TRUE(data.Size() == 3);
    EXPECT_STREQ("this", *data[0]);
    EXPECT_STREQ("'is  a'", *data[1]);
    EXPECT_STREQ("test", *data[2]);
    EXPECT_STREQ("this", *data1[0]);
    EXPECT_STREQ("'is   a'", *data1[1]);
    EXPECT_STREQ("test", *data1[2]);
    EXPECT_STREQ("this", *data2[0]);
    EXPECT_STREQ("'is   a'", *data2[1]);
    EXPECT_STREQ("test", *data2[2]);
}

TEST(String, ExplodeIgnoreString_Test2)
{
    bpf::String s = "this  !'is  a!'  test";
    bpf::String s1 = "this      !'is   a!'                  test";
    bpf::String s2 = "          this      !'is   a!'                  test          ";
    bpf::List<bpf::String> data;
    bpf::List<bpf::String> data1;
    bpf::List<bpf::String> data2;

    s.ExplodeIgnore(data, "  ", "!'");
    s1.ExplodeIgnore(data1, "  ", "!'");
    s2.ExplodeIgnore(data2, "  ", "!'");
    EXPECT_TRUE(data.Size() == data1.Size());
    EXPECT_TRUE(data.Size() == data2.Size());
    EXPECT_TRUE(data.Size() == 3);
    EXPECT_STREQ("this", *data[0]);
    EXPECT_STREQ("!'is  a!'", *data[1]);
    EXPECT_STREQ("test", *data[2]);
    EXPECT_STREQ("this", *data1[0]);
    EXPECT_STREQ("!'is   a!'", *data1[1]);
    EXPECT_STREQ("test", *data1[2]);
    EXPECT_STREQ("this", *data2[0]);
    EXPECT_STREQ("!'is   a!'", *data2[1]);
    EXPECT_STREQ("test", *data2[2]);
}

TEST(String, StartsWith)
{
    bpf::String s = "this is a test";
    EXPECT_TRUE(s.StartsWith("this"));
    EXPECT_TRUE(!s.StartsWith("is a"));
    EXPECT_TRUE(s.StartsWith(""));
}

TEST(String, EndsWith)
{
    bpf::String s = "this is a test";
    EXPECT_TRUE(s.EndsWith("test"));
    EXPECT_TRUE(!s.EndsWith("a tes"));
    EXPECT_TRUE(s.EndsWith(""));
}

TEST(String, StartsWithUTF8)
{
    bpf::String s = "thïs ïs à tèst€";
    EXPECT_TRUE(s.StartsWith("thïs"));
    EXPECT_FALSE(s.StartsWith("this"));
    EXPECT_FALSE(s.StartsWith("is a"));
    EXPECT_FALSE(s.StartsWith("ïs à"));
    EXPECT_TRUE(s.StartsWith(""));
}

TEST(String, EndsWithUTF8)
{
    bpf::String s = "this is à tèst€";
    EXPECT_TRUE(s.EndsWith("tèst€"));
    EXPECT_FALSE(s.EndsWith("test€"));
    EXPECT_FALSE(s.EndsWith("à tes"));
    EXPECT_FALSE(s.EndsWith("a tes"));
    EXPECT_TRUE(s.EndsWith(""));
}

TEST(String, ContainsString)
{
    bpf::String s = "this is a test";
    EXPECT_TRUE(s.Contains(" is a "));
    EXPECT_TRUE(s.Contains("this is"));
    EXPECT_TRUE(s.Contains("a test"));
    EXPECT_TRUE(!s.Contains("go"));
}

TEST(String, ContainsChar)
{
    bpf::String s = "this is a test";
    EXPECT_TRUE(s.Contains('i'));
    EXPECT_TRUE(s.Contains('t'));
    EXPECT_TRUE(s.Contains('a'));
    EXPECT_TRUE(!s.Contains('g'));
}

TEST(String, Sub)
{
    bpf::String s = "test   test  testabc";
    EXPECT_STREQ(*s.Sub(0, 4), "test");
    EXPECT_STREQ(*s.Sub(9, 11), "st");
    EXPECT_STREQ(*s.Sub(12), " testabc");
}

TEST(String, SubUTF8)
{
    bpf::String s = "testÉé€test¥▦testabc";
    EXPECT_STREQ(*s.Sub(0, 4), "test");
    EXPECT_STREQ(*s.Sub(11, 13), "¥▦");
    EXPECT_STREQ(*s.Sub(12), "▦testabc");
}

TEST(String, SubLen)
{
    bpf::String s = "test   test  testabc";
    EXPECT_STREQ(*s.SubLen(0, 4), "test");
    EXPECT_STREQ(*s.SubLen(9, 2), "st");
    EXPECT_STREQ(*s.SubLen(12), " testabc");
}

TEST(String, SubLenUTF8)
{
    bpf::String s = "testÉé€test¥▦testabc";
    EXPECT_STREQ(*s.SubLen(0, 4), "test");
    EXPECT_STREQ(*s.SubLen(11, 2), "¥▦");
    EXPECT_STREQ(*s.SubLen(12), "▦testabc");
}

TEST(String, ToInt)
{
    bpf::String s = "42";
    EXPECT_TRUE(s.ToInt() == 42);
    s = "0";
    EXPECT_TRUE(s.ToInt() == 0);
    s = "-42";
    EXPECT_TRUE(s.ToInt() == -42);
}

TEST(String, ToFloat)
{
    bpf::String s = "42.42";
    EXPECT_TRUE(s.ToFloat() == 42.42f);
    s = "0.5";
    EXPECT_TRUE(s.ToFloat() == 0.5f);
    s = "-42.42";
    EXPECT_TRUE(s.ToFloat() == -42.42f);
}

TEST(String, ToDouble)
{
    bpf::String s = "42.42";
    EXPECT_TRUE(s.ToDouble() == 42.42);
    s = "0.5";
    EXPECT_TRUE(s.ToDouble() == 0.5);
    s = "-42.42";
    EXPECT_TRUE(s.ToDouble() == -42.42);
    s = "3.141592654";
    EXPECT_TRUE(s.ToDouble() == 3.141592654);
    s = "2.71828";
    EXPECT_TRUE(s.ToDouble() == 2.71828);
}

TEST(String, Evaluate)
{
    double res;
    res = bpf::String("4+4").Evaluate();
    EXPECT_EQ(res, 8);
    res = bpf::String("4+4*8").Evaluate();
    EXPECT_EQ(res, 36);
    res = bpf::String("4*1+4*1+2").Evaluate();
    EXPECT_EQ(res, 10);
    res = bpf::String("32/32").Evaluate();
    EXPECT_EQ(res, 1);
    res = bpf::String("32/1").Evaluate();
    EXPECT_EQ(res, 32);
    //TODO : Fix 32/32*32/1 not working without parentheses
    res = bpf::String("(((32/32)*32)/1)").Evaluate();
    EXPECT_EQ(res, 32);
    res = bpf::String("-(1 + 1)").Evaluate();
    EXPECT_EQ(res, -2);
    res = bpf::String("-1 + 1").Evaluate();
    EXPECT_EQ(res, 0);
    res = bpf::String("-(1 + 1) * (4 - 1)").Evaluate();
    EXPECT_EQ(res, -6);
}

TEST(String, EvaluateErr)
{
    double res;
    try
    {
        res = bpf::String(" 0 / 0 ").Evaluate();
    }
    catch (const bpf::EvalException &)
    {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}

TEST(String, Format)
{
    bpf::Array<bpf::String> arr;
    arr[0] = "this is a test";
    arr[1] = "yay";
    bpf::String formatted = bpf::String::Format("[16,right, ]\t[16,right, ]\t[]\t[]", -42, 42.42, 42000, arr);
    const char *expected = "             -42\t           42.42\t42000\t[this is a test, yay]";
    EXPECT_STREQ(*formatted, expected);
    EXPECT_TRUE(strlen(expected) == (size_t)formatted.Size());
}

TEST(String, ValueOf)
{
    EXPECT_STREQ(*bpf::String::ValueOf(42), "42");
    EXPECT_STREQ(*bpf::String::ValueOf(42.42f), "42.42");
    bpf::Array<bpf::String> arr;
    arr[0] = "this is a test";
    arr[1] = "yay";
    EXPECT_STREQ(*bpf::String::ValueOf(arr), "[this is a test, yay]");
}

TEST(String, Safety)
{
    bpf::String str = "this is a test";
    try
    {
        str += str[-1];
    }
    catch (const bpf::IndexException &)
    {
        ASSERT_TRUE(true);
    }
    try
    {
        str += str[9999];
    }
    catch (const bpf::IndexException &)
    {
        ASSERT_TRUE(true);
    }
    try
    {
        str += str[15];
    }
    catch (const bpf::IndexException &)
    {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}

TEST(String, Iterate)
{
    bpf::String str = "this is a test";

    for (bpf::uint32 i = 0; i != str.Len(); ++i)
    {
        std::cout << str[i];
    }
    std::cout << std::endl;
    for (bpf::uint32 i = 0; str[i]; ++i)
    {
        std::cout << str[i];
    }
    std::cout << std::endl;
}

TEST(String, IterateUTF8)
{
    bpf::String str = "thïs ïs à tést€ducultdbdc";
    bpf::String str1;

    for (bpf::uint32 i = 0; i != str.Len(); ++i)
    {
        std::cout << str[i];
    }
    std::cout << std::endl;
    for (bpf::uint32 i = 0; str[i]; ++i)
    {
        std::cout << str[i];
    }
    std::cout << std::endl;
}

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return (RUN_ALL_TESTS());
}
