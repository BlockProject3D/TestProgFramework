// Copyright (c) 2018, BlockProject
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimer in the documentation
//       and/or other materials provided with the distribution.
//     * Neither the name of BlockProject nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <Framework/IO/BinaryReader.hpp>
#include <Framework/IO/BinaryWriter.hpp>
#include <Framework/IO/FileStream.hpp>

TEST(BinaryReadWrite, Construct_Writer)
{
    bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_WRITE);
    bpf::BinaryWriter w(f);
}

TEST(BinaryReadWrite, Construct_Reader)
{
    bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_READ);
    bpf::BinaryReader r(f);
}

TEST(BinaryReadWrite, ReadWrite_Test1)
{
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
        bpf::BinaryWriter w(f);

        w << 42 << 42.42f << 42.4242 << true;
    }
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_READ);
        bpf::BinaryReader r(f);
        int i;
        float ff;
        double d;
        bool b;

        r >> i >> ff >> d >> b;
        EXPECT_EQ(i, 42);
        EXPECT_EQ(ff, 42.42f);
        EXPECT_EQ(d, 42.4242);
        EXPECT_EQ(b, true);
    }
}

TEST(BinaryReadWrite, ReadWrite_String_Test1)
{
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
        bpf::BinaryWriter w(f);

        w << "This is a test";
    }
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_READ);
        bpf::BinaryReader r(f);
        bpf::String str;

        r >> str;
        EXPECT_STREQ(*str, "This is a test");
    }
}

TEST(BinaryReadWrite, ReadWrite_String_Test2)
{
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
        bpf::BinaryWriter w(f);

        w.SetStringSerializer(bpf::EStringSerializer::VARCHAR_16);
        w << "This is a test";
    }
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_READ);
        bpf::BinaryReader r(f);
        bpf::String str;

        r.SetStringSerializer(bpf::EStringSerializer::VARCHAR_16);
        r >> str;
        EXPECT_STREQ(*str, "This is a test");
    }
}

TEST(BinaryReadWrite, ReadWrite_String_Test3)
{
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
        bpf::BinaryWriter w(f);

        w.SetStringSerializer(bpf::EStringSerializer::VARCHAR_8);
        w << "This is a test";
    }
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_READ);
        bpf::BinaryReader r(f);
        bpf::String str;

        r.SetStringSerializer(bpf::EStringSerializer::VARCHAR_8);
        r >> str;
        EXPECT_STREQ(*str, "This is a test");
    }
}

TEST(BinaryReadWrite, ReadWrite_String_Test4)
{
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_WRITE | bpf::FILE_MODE_TRUNCATE);
        bpf::BinaryWriter w(f);

        w.SetStringSerializer(bpf::EStringSerializer::CSTYLE);
        w << "This is a test";
    }
    {
        bpf::FileStream f(bpf::File("./edit_me.txt"), bpf::FILE_MODE_READ);
        bpf::BinaryReader r(f);
        bpf::String str;

        r.SetStringSerializer(bpf::EStringSerializer::CSTYLE);
        r >> str;
        EXPECT_STREQ(*str, "This is a test");
    }
}
