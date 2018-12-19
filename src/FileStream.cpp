#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/IO/FileStream.hpp>
#include <Framework/IO/IOException.hpp>

TEST(FileStream, OpenExcept)
{
    try
    {
        bpf::FileStream stream(bpf::File("./doesnotexist.txt"), bpf::FILE_MODE_READ);
    }
    catch (const bpf::IOException &)
    {
        return;
    }
    ASSERT_TRUE(false);
}

TEST(FileStream, Open)
{
    bpf::File f("./doesnotexist.txt");
    bpf::FileStream stream(f, bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
    EXPECT_EQ(stream.Write("This is a test", 14), 14);
    stream.Close();
    bpf::FileStream stream1(f, bpf::FILE_MODE_READ);
    char buf[15];
    EXPECT_EQ(stream1.Read(buf, 14), 14);
    buf[14] = '\0';
    EXPECT_STREQ(buf, "This is a test");
    stream1.Close();
    f.Delete();
}
