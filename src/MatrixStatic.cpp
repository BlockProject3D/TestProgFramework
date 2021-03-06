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

template <typename T, bpf::fsize X, bpf::fsize Y>
static void PrintMatrix(const bpf::Matrix<T, Y, X> &other)
{
    for (bpf::fsize y = 0; y != Y; ++y)
    {
        for (bpf::fsize x = 0; x != X; ++x)
            std::cout << other(x, y) << "\t";
        std::cout << std::endl;
    }
}

template <typename T>
static void PrintVector(const bpf::Vector2<T> &other)
{
    std::cout << "V2(" << other.X << ", " << other.Y << ")" << std::endl;
}

template <typename T>
static void PrintVector(const bpf::Vector3<T> &other)
{
    std::cout << "V3(" << other.X << ", " << other.Y << ", " << other.Z << ")" << std::endl;
}

template <typename T>
static void PrintVector(const bpf::Vector4<T> &other)
{
    std::cout << "V4(" << other.X << ", " << other.Y << ", " << other.Z << ", " << other.W <<")" << std::endl;
}

template <typename T, bpf::fsize X, bpf::fsize Y>
static void ExpectMatrixEq(const bpf::Matrix<T, Y, X> &mat, const bpf::Matrix<T, Y, X> &mat1)
{
    for (bpf::fsize y = 0; y != Y; ++y)
    {
        for (bpf::fsize x = 0; x != X; ++x)
            EXPECT_EQ(mat(x, y), mat1(x, y));
    }
}

template <typename T>
static void ExpectVectorEq(const bpf::Vector2<T> &v, const bpf::Vector2<T> &v1)
{
    EXPECT_EQ(v.X, v1.X);
    EXPECT_EQ(v.Y, v1.Y);
}

template <typename T>
static void ExpectVectorEq(const bpf::Vector3<T> &v, const bpf::Vector3<T> &v1)
{
    EXPECT_EQ(v.X, v1.X);
    EXPECT_EQ(v.Y, v1.Y);
    EXPECT_EQ(v.Z, v1.Z);
}

template <typename T>
static void ExpectVectorEq(const bpf::Vector4<T> &v, const bpf::Vector4<T> &v1)
{
    EXPECT_EQ(v.X, v1.X);
    EXPECT_EQ(v.Y, v1.Y);
    EXPECT_EQ(v.Z, v1.Z);
    EXPECT_EQ(v.W, v1.W);
}

TEST(MatrixStatic, Create_Test1)
{
    bpf::Matrix<int, 2, 3> mat;
    bpf::Matrix<int, 2, 3> mat1;

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

TEST(MatrixStatic, Create_Test2)
{
    bpf::Matrix3<int> mat = bpf::Matrix3<int>::Identity;
    bpf::Matrix3<int> mat1 = { 1, 0, 0,
                               0, 1, 0,
                               0, 0, 1 };

    ExpectMatrixEq(mat, mat1);
}

TEST(MatrixStatic, Transpose_Square)
{
    bpf::Matrix3<int> mat = bpf::Matrix3<int>::Identity;
    bpf::Matrix3<int> mat1 = mat.Transpose();

    ExpectMatrixEq(mat, mat1);
}

TEST(MatrixStatic, Transpose_NonSquare)
{
    bpf::Matrix<int, 2, 3> mat;
    bpf::Matrix<int, 3, 2> mat1 = {
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

TEST(MatrixStatic, SwapRows_Square)
{
    bpf::Matrix3<int> mat = bpf::Matrix3<int>::Identity;
    bpf::Matrix3<int> mat1 = {
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

TEST(MatrixStatic, SwapRows_NonSquare)
{
    bpf::Matrix<int, 2, 3> mat;
    bpf::Matrix<int, 2, 3> mat1 = {
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

TEST(MatrixStatic, SwapColumns_Square)
{
    bpf::Matrix3<int> mat = bpf::Matrix3<int>::Identity;
    bpf::Matrix3<int> mat1 = {
        3, 0, 1,
        2, 1, 0,
        1, 0, 4
    };

    //Input
    //1 0 3
    //0 1 2
    //4 0 1
    //SwapColumns 0, 2
    //3 0 1
    //2 1 0
    //1 0 4
    mat(2, 0) = 3;
    mat(2, 1) = 2;
    mat(0, 2) = 4;
    mat.SwapColumns(0, 2);
    ExpectMatrixEq(mat, mat1);
}

TEST(MatrixStatic, SwapColumns_NonSquare)
{
    bpf::Matrix<int, 2, 3> mat;
    bpf::Matrix<int, 2, 3> mat1 = {
        0, 1, 3,
        1, 0, 2
    };

    //Input
    //1 0 3
    //0 1 2
    //SwapColumns 0, 1
    //0 1 3
    //1 0 2
    mat(0, 0) = 1;
    mat(1, 1) = 1;
    mat(2, 0) = 3;
    mat(2, 1) = 2;
    mat.SwapColumns(0, 1);
    ExpectMatrixEq(mat, mat1);
}


TEST(MatrixStatic, Multiply_Square_Test1)
{
    bpf::Matrix3<int> mat = bpf::Matrix3<int>::Identity;
    bpf::Matrix3<int> mat1 = bpf::Matrix3<int>::Identity;

    ExpectMatrixEq(mat, mat * mat1);
}

TEST(MatrixStatic, Multiply_Square_Test2)
{
    bpf::Matrix3<int> mat = {
        2, 5, 6,
        9, 8, 7,
        3, 1, 0
    };
    bpf::Matrix3<int> mat1 = bpf::Matrix3<int>::Identity;

    ExpectMatrixEq(mat, mat * mat1);
}

TEST(MatrixStatic, Multiply_NonSquare_Test1)
{
    bpf::Matrix<int, 4, 3> mat = {
        2, 5, 6,
        9, 8, 7,
        3, 1, 0,
        8, 4, 5,
    };
    bpf::Matrix<int, 3, 4> mat1 = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
    bpf::Matrix<int, 4, 4> res = mat * mat1;
    bpf::Matrix<int, 4, 4> expected = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    ExpectMatrixEq(res, expected);
}

TEST(MatrixStatic, Multiply_NonSquare_Test2)
{
    bpf::Matrix<int, 4, 3> mat = {
        2, 5, 6,
        9, 8, 7,
        3, 1, 0,
        8, 4, 5,
    };
    bpf::Matrix<int, 3, 4> mat1 = {
        2, 5, 6, 1,
        9, 8, 7, 1,
        3, 1, 0, 1,
    };
    bpf::Matrix<int, 4, 4> res = mat * mat1;
    bpf::Matrix<int, 4, 4> expected = {
        67, 56, 47, 13,
        111, 116, 110, 24,
        15, 23, 25, 4,
        67, 77, 76, 17
    };

    ExpectMatrixEq(res, expected);
}

TEST(MatrixStatic, Multiply_NonSquare_Test3)
{
    bpf::Matrix<int, 4, 5> mat = {
        2, 5, 6, 8, 9,
        9, 8, 7, 7, 1,
        3, 1, 0, 6, 8,
        8, 4, 5, 0, 2
    };
    bpf::Matrix<int, 5, 6> mat1 = {
        2, 5, 6, 1, 0, 6,
        9, 8, 7, 1, 0, 6,
        3, 1, 0, 1, 0, 6,
        3, 1, 0, 1, 0, 6,
        3, 1, 0, 1, 0, 6
    };
    bpf::Matrix<int, 4, 6> res = mat * mat1;
    bpf::Matrix<int, 4, 6> expected = {
        118, 73, 47, 30, 0, 180,
        135, 124, 110, 32, 0, 192,
        57, 37, 25, 18, 0, 108,
        73, 79, 76, 19, 0, 114
    };

    ExpectMatrixEq(res, expected);
}

TEST(MatrixStatic, Matrix_Inverse)
{
    bpf::Matrix2f mat = {
        0, 6,
        9, 5
    };
    bpf::Matrix2f res = mat * mat.Invert();
    bpf::Matrix2f expected = {
        1, 0,
        0, 1
    };
    
    ExpectMatrixEq(res, expected);
}

TEST(MatrixStatic, Multiply_Vec2)
{
    bpf::Matrix2<int> mat = {
        5, 9,
        7, 2
    };
    bpf::Vector2<int> vec(6, 5);
    bpf::Vector2<int> res = mat * vec;
    bpf::Vector2<int> expected(75, 52);

    ExpectVectorEq(res, expected);
}

TEST(MatrixStatic, Multiply_Vec3)
{
    bpf::Matrix3<int> mat = {
        5, 9, 8,
        7, 2, 6,
        3, 4, 1
    };
    bpf::Vector3<int> vec(6, 5, 3);
    bpf::Vector3<int> res = mat * vec;
    bpf::Vector3<int> expected(99, 70, 41);

    ExpectVectorEq(res, expected);
}

TEST(MatrixStatic, Multiply_Vec4)
{
    bpf::Matrix4<int> mat = {
        5, 9, 8, 5,
        7, 2, 6, 7,
        3, 4, 1, 6,
        4, 5, 8, 1
    };
    bpf::Vector4<int> vec(6, 5, 3, 2);
    bpf::Vector4<int> res = mat * vec;
    bpf::Vector4<int> expected(109, 84, 53, 75);

    ExpectVectorEq(res, expected);
}

TEST(MatrixStatic, HomogeneousCoords_2D)
{
    bpf::Matrix3f mat = bpf::Matrix3f::Identity;
    bpf::Matrix3f expected = {
        1, 0, 2,
        0, 1, 2,
        0, 0, 1
    };

    mat.Translate(bpf::Vector2<float>(2, 2));
    ExpectMatrixEq(mat, expected);
}

TEST(MatrixStatic, HomogeneousCoords_3D)
{
    bpf::Matrix4f mat = bpf::Matrix4f::Identity;
    bpf::Matrix4f expected = {
        1, 0, 0, 2,
        0, 1, 0, 2,
        0, 0, 1, 2,
        0, 0, 0, 1
    };

    mat.Translate(bpf::Vector3<float>(2, 2, 2));
    ExpectMatrixEq(mat, expected);
}
