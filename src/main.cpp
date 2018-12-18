#include <cassert>
#include <iostream>
#include <gtest/gtest.h>

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

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return (RUN_ALL_TESTS());
}
