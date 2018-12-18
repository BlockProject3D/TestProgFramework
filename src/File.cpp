#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/IO/File.hpp>

TEST(File, Basics)
{
    bpf::File f("./doesnotexist.txt");

    EXPECT_FALSE(f.Exists());
    f.CreateDir();
    EXPECT_TRUE(f.Exists());
    f.Delete();
    EXPECT_FALSE(f.Exists());
}

TEST(File, Abs)
{
    bpf::File f("./doesnotexist.txt");

    EXPECT_FALSE(f.Exists());
    f.CreateDir();
    EXPECT_TRUE(f.Exists());
    bpf::File abs = f.GetAbsolutePath();
    std::cout << *abs.GetPath() << std::endl;
    EXPECT_TRUE(abs.Exists());
    f.Delete();
    EXPECT_FALSE(f.Exists());
}

#ifdef WINDOWS
TEST(File, AutoBackSlash)
{
    bpf::File f("./");

    EXPECT_STREQ(*f.GetPath(), ".");
    bpf::File f1 = f + "../";
    EXPECT_STREQ(*f1.GetPath(), ".\\..");
}
#else
TEST(File, AutoSlash)
{
    bpf::File f("./");

    EXPECT_STREQ(*f.GetPath(), ".");
    bpf::File f1 = f + "../";
    EXPECT_STREQ(*f1.GetPath(), "./..");
}
#endif

TEST(File, List_Test1)
{
    bpf::File f("./");
    bpf::List<bpf::File> fls = f.ListFiles();

    EXPECT_GT(fls.Size(), static_cast<bpf::uint32>(0));
}

TEST(File, List_Test2)
{
    bpf::File f(".");
    bpf::List<bpf::File> fls = f.ListFiles();

    EXPECT_GT(fls.Size(), static_cast<bpf::uint32>(0));
}

TEST(File, List_Test3)
{
    bpf::File f("..");
    bpf::List<bpf::File> fls = f.ListFiles();

    EXPECT_GT(fls.Size(), static_cast<bpf::uint32>(0));
}

TEST(File, List_Test4)
{
    bpf::File f("../");
    bpf::List<bpf::File> fls = f.ListFiles();

    EXPECT_GT(fls.Size(), static_cast<bpf::uint32>(0));
}
