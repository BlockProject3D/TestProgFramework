#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/IO/ByteBuf.hpp>

TEST(ByteBuf, Construct)
{
    bpf::ByteBuf buf(128);
    bpf::ByteBuf buf1(std::move(buf));
    
    buf1.Clear();
}

TEST(ByteBuf, Clear)
{
    bpf::ByteBuf buf(128);

    buf.Clear();
    for (bpf::fsize i = 0 ; i < buf.Size() ; ++i)
        EXPECT_EQ(buf[i], 0);
}

TEST(ByteBuf, ReadWrite_Test1)
{
    bpf::ByteBuf buf(128);
    char res[15];
    
    buf.Clear();
    for (bpf::fsize i = 0 ; i < buf.Size() ; ++i)
        EXPECT_EQ(buf[i], 0);
    EXPECT_EQ(buf.Write("This is a test", 14), 14);
    buf.Seek(0);
    EXPECT_EQ(buf.Read(res, 15), 15);
    EXPECT_STREQ("This is a test", res);
}

TEST(ByteBuf, ReadWrite_Test2)
{
    bpf::ByteBuf buf(4);
    char res[15];
    
    EXPECT_EQ(buf.Size(), 4);
    buf.Clear();
    for (bpf::fsize i = 0 ; i < buf.Size() ; ++i)
        EXPECT_EQ(buf[i], 0);
    EXPECT_EQ(buf.Write("This is a test", 14), 4);
    buf.Seek(0);
    EXPECT_EQ(buf.Read(res, 15), 4);
    res[4] = '\0';
    EXPECT_STREQ("This", res);
}

TEST(ByteBuf, ReadWrite_Test3)
{
    bpf::ByteBuf buf(128);
    char res[15];
    
    EXPECT_EQ(buf.Size(), 128);
    buf.Clear();
    for (bpf::fsize i = 0 ; i < buf.Size() ; ++i)
        EXPECT_EQ(buf[i], 0);
    EXPECT_EQ(buf.Write("This", 4), 4);
    EXPECT_EQ(buf.GetCursor(), 4);
    EXPECT_EQ(buf.Write("This", 4), 4);
    EXPECT_EQ(buf.GetCursor(), 8);
    buf.Seek(0);
    EXPECT_EQ(buf.Read(res, 9), 9);
    EXPECT_STREQ("ThisThis", res);
}
