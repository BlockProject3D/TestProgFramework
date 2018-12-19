#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/IO/FileStream.hpp>
#include <Framework/IO/IOException.hpp>
#include <Framework/IO/MemoryMapper.hpp>

static void SetupTestFile(bpf::File &f)
{
    bpf::FileStream stream(f, bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
    EXPECT_EQ(stream.Write("This is a test", 14), 14);
    stream.Close();
}

TEST(MemoryMapper, Map_Test1)
{
    bpf::File f("./map_me.txt");
    SetupTestFile(f);
    bpf::MemoryMapper mapper(f, bpf::FILE_MODE_READ);
    mapper.Map(0, 14);
    char *txt = reinterpret_cast<char *>(*mapper);
    char buf[15];
    memcpy(buf, txt, 14);
    buf[14] = '\0';
    EXPECT_STREQ(buf, "This is a test");
}

TEST(MemoryMapper, Map_Test2)
{
    bpf::File f("./map_me.txt");
    SetupTestFile(f);
    bpf::MemoryMapper mapper(f, bpf::FILE_MODE_READ | bpf::FILE_MODE_WRITE);
    mapper.Map(0, 1);
    char *txt = reinterpret_cast<char *>(*mapper);
    EXPECT_EQ(txt[0], 'T');
    mapper.Map(1, 1);
    txt = reinterpret_cast<char *>(*mapper);
    EXPECT_EQ(txt[0], 'h');
}

TEST(MemoryMapper, Map_Test3)
{
    bpf::File f("./map_me.txt");
    SetupTestFile(f);
    bpf::MemoryMapper mapper(f, bpf::FILE_MODE_READ);
    mapper.Map(13, 1);
    char *txt = reinterpret_cast<char *>(*mapper);
    EXPECT_EQ(txt[0], 't');
}

TEST(MemoryMapper, Map_Test4)
{
    bpf::File f("./map_me.txt");
    SetupTestFile(f);
    bpf::MemoryMapper mapper(f, bpf::FILE_MODE_READ);
    try
    {
        mapper.Map(14, 1);
    }
    catch (const bpf::IOException &)
    {
        return;
    }
    ASSERT_TRUE(false);
}

TEST(MemoryMapper, Map_Test5)
{
    bpf::File f("./map_me.txt");
    SetupTestFile(f);
    bpf::MemoryMapper mapper(f, bpf::FILE_MODE_READ);
    try
    {
        mapper.Map(100000, 1); //Obviously it's not gonna work :)
    }
    catch (const bpf::IOException &)
    {
        return;
    }
    ASSERT_TRUE(false);
}
