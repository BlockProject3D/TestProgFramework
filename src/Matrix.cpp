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
#include <Framework/Math/BMath.hpp>
#include <Framework/Math/Matrix.hpp>

template <bpf::fsize X, bpf::fsize Y, typename T>
static void PrintMatrix(const bpf::Matrix<Y, X, T> &other)
{
    for (bpf::fsize y = 0; y != Y; ++y)
    {
        for (bpf::fsize x = 0; x != X; ++x)
            std::cout << other(x, y) << "\t";
        std::cout << std::endl;
    }
}

template <bpf::fsize X, bpf::fsize Y, typename T>
static void ExpectMatrixEq(const bpf::Matrix<Y, X, T> &mat, const bpf::Matrix<Y, X, T> &mat1)
{
    for (bpf::fsize y = 0; y != Y; ++y)
    {
        for (bpf::fsize x = 0; x != X; ++x)
            EXPECT_EQ(mat(x, y), mat1(x, y));
    }
}

TEST(Matrix, Create_Test1)
{
    bpf::Matrix<2, 3, int> mat;
    bpf::Matrix<2, 3, int> mat1;

    ExpectMatrixEq(mat, mat1);
    mat(0, 0) = 1;
    mat(1, 1) = 1;
    mat(2, 1) = 1;
    mat(2, 0) = 3;
    mat1(0, 0) = 1;
    mat1(1, 1) = 1;
    mat1(2, 1) = 1;
    mat1(2, 0) = 3;
    ExpectMatrixEq(mat, mat1);
}

TEST(Matrix, Create_Test2)
{
    bpf::Matrix<3, 3, int> mat = bpf::Matrix<3, 3, int>::Identity;
    bpf::Matrix<3, 3, int> mat1 = { 1, 0, 0,
                                    0, 1, 0,
                                    0, 0, 1 };

    ExpectMatrixEq(mat, mat1);
}

TEST(Matrix, Transpose_Square)
{
    bpf::Matrix<3, 3, int> mat = bpf::Matrix<3, 3, int>::Identity;
    bpf::Matrix<3, 3, int> mat1 = mat.Transpose();

    ExpectMatrixEq(mat, mat1);
}

TEST(Matrix, Transpose_NonSquare)
{
    bpf::Matrix<2, 3, int> mat;
    bpf::Matrix<3, 2, int> mat1 = {
        1, 0,
        0, 1,
        3, 1
    };;

    mat(0, 0) = 1;
    mat(1, 1) = 1;
    mat(2, 1) = 1;
    mat(2, 0) = 3;
    ExpectMatrixEq(mat.Transpose(), mat1);
}

TEST(Matrix, SwapRows_Square)
{
    bpf::Matrix<3, 3, int> mat = bpf::Matrix<3, 3, int>::Identity;
    bpf::Matrix<3, 3, int> mat1 = {
        4, 0, 1,
        0, 1, 2,
        1, 0, 3
    };

    //Input
    //1 0 3
    //0 1 2
    //4 0 1
    //SwapRows 0, 2
    //4 0 1
    //0 1 2
    //1 0 3
    mat(2, 0) = 3;
    mat(2, 1) = 2;
    mat(0, 2) = 4;
    mat.SwapRows(0, 2);
    ExpectMatrixEq(mat, mat1);
}

TEST(Matrix, SwapRows_NonSquare)
{
    bpf::Matrix<2, 3, int> mat;
    bpf::Matrix<2, 3, int> mat1 = {
        0, 1, 2,
        1, 0, 3
    };

    //Input
    //1 0 3
    //0 1 2
    //SwapRows 0, 1
    //0 1 2
    //1 0 3
    mat(0, 0) = 1;
    mat(1, 1) = 1;
    mat(2, 0) = 3;
    mat(2, 1) = 2;
    mat.SwapRows(0, 1);
    ExpectMatrixEq(mat, mat1);
}

TEST(Matrix, Multiply_Square_Test1)
{
    bpf::Matrix<3, 3, int> mat = bpf::Matrix<3, 3, int>::Identity;
    bpf::Matrix<3, 3, int> mat1 = bpf::Matrix<3, 3, int>::Identity;

    ExpectMatrixEq(mat, mat * mat1);
}

TEST(Matrix, Multiply_Square_Test2)
{
    bpf::Matrix<3, 3, int> mat = {
        2, 5, 6,
        9, 8, 7,
        3, 1, 0
    };
    bpf::Matrix<3, 3, int> mat1 = bpf::Matrix<3, 3, int>::Identity;

    ExpectMatrixEq(mat, mat * mat1);
}

TEST(Matrix, Multiply_NonSquare_Test1)
{
    bpf::Matrix<4, 3, int> mat = {
        2, 5, 6,
        9, 8, 7,
        3, 1, 0,
        8, 4, 5,
    };
    bpf::Matrix<3, 4, int> mat1 = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
    bpf::Matrix<4, 4, int> res = mat * mat1;
    bpf::Matrix<4, 4, int> expected = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    ExpectMatrixEq(res, expected);
}

TEST(Matrix, Multiply_NonSquare_Test2)
{
    bpf::Matrix<4, 3, int> mat = {
        2, 5, 6,
        9, 8, 7,
        3, 1, 0,
        8, 4, 5,
    };
    bpf::Matrix<3, 4, int> mat1 = {
        2, 5, 6, 1,
        9, 8, 7, 1,
        3, 1, 0, 1,
    };
    bpf::Matrix<4, 4, int> res = mat * mat1;
    bpf::Matrix<4, 4, int> expected = {
        67, 56, 47, 13,
        111, 116, 110, 24,
        15, 23, 25, 4,
        67, 77, 76, 17
    };

    ExpectMatrixEq(res, expected);
}

TEST(Matrix, Multiply_NonSquare_Test3)
{
    bpf::Matrix<4, 5, int> mat = {
        2, 5, 6, 8, 9,
        9, 8, 7, 7, 1,
        3, 1, 0, 6, 8,
        8, 4, 5, 0, 2
    };
    bpf::Matrix<5, 6, int> mat1 = {
        2, 5, 6, 1, 0, 6,
        9, 8, 7, 1, 0, 6,
        3, 1, 0, 1, 0, 6,
        3, 1, 0, 1, 0, 6,
        3, 1, 0, 1, 0, 6
    };
    bpf::Matrix<4, 6, int> res = mat * mat1;
    bpf::Matrix<4, 6, int> expected = {
        118, 73, 47, 30, 0, 180,
        135, 124, 110, 32, 0, 192,
        57, 37, 25, 18, 0, 108,
        73, 79, 76, 19, 0, 114
    };

    ExpectMatrixEq(res, expected);
}

TEST(Matrix, Matrix_Inverse)
{
    bpf::Matrix<2, 2, float> mat = {
        0, 6,
        9, 5
    };
    bpf::Matrix<2, 2, float> res = mat * mat.Invert();
    bpf::Matrix<2, 2, float> expected = {
        1, 0,
        0, 1
    };
    
    ExpectMatrixEq(res, expected);
}
