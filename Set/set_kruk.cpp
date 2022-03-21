#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

#include "set.hpp"
#include <string>
#include <vector>
#include <random>
#include <algorithm>

class BasicSetOperationsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BasicSetOperationsTest);
    CPPUNIT_TEST(integerSetTest);
    CPPUNIT_TEST(floatSetTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void integerSetTest()
    {
        Set<int> s;
        std::vector<int> out{};
        for (int i = 0; i < 10; i++)
        {
            out.push_back(pow(10, i));
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val : out)
        {
            s.insert(val);
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val : out)
        {
            CPPUNIT_ASSERT(s.contains(val));
            CPPUNIT_ASSERT(!s.contains(val + 5));
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val : out)
        {
            s.remove(val);
        }

        CPPUNIT_ASSERT(!s.contains(0));
    }

    void floatSetTest()
    {
        Set<float> s;
        std::vector<float> out{};
        for (int i = 0; i < 10; i++)
        {
            out.push_back(pow(10, -i));
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val : out)
        {
            s.insert(val);
        }

        CPPUNIT_ASSERT(!s.contains(10));

        std::random_shuffle(out.begin(), out.end());
        for (auto val : out)
        {
            CPPUNIT_ASSERT(s.contains(val));
            CPPUNIT_ASSERT(!s.contains(val + 0.5f));
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val : out)
        {
            s.remove(val);
        }

        CPPUNIT_ASSERT(!s.contains(out[0]));
    }
};

class TwoSetOperationsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TwoSetOperationsTest);
    CPPUNIT_TEST(unionTest);
    CPPUNIT_TEST(intersectionTest);
    CPPUNIT_TEST(differenceTest);
    CPPUNIT_TEST_SUITE_END();

    static std::vector<std::string> genStrings() noexcept
    {
        std::vector<std::string> out{};

        auto randChar = []() -> char
        {
            const std::string charset = "0123456789"
                                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz";
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, charset.size() - 1);
            return charset[dist(gen)];
        };

        for (int i = 0; i < 10; i++)
        {
            std::string str(10, 0);
            std::generate_n(str.begin(), 10, randChar);
            out.push_back(str);
        }
        return out;
    };

public:
    void unionTest()
    {
        std::vector<std::string> vec1 = genStrings(),
                                 vec2 = genStrings();

        std::random_shuffle(vec1.begin(), vec1.end());
        for (int i = 0; i < 5; i++)
        {
            vec2[i] = vec1[i];
        }

        Set<std::string> s1{}, s2{};

        for (int i = 0; i < 10; i++)
        {
            s1.insert(vec1[i]);
            s2.insert(vec2[i]);
        }

        s1.Union(s2);

        CPPUNIT_ASSERT(s1.contains(vec2[0]));
        CPPUNIT_ASSERT(s1.contains(vec2[5]));
    }

    void intersectionTest()
    {
        std::vector<std::string> vec1 = genStrings(),
                                 vec2 = genStrings();

        std::random_shuffle(vec1.begin(), vec1.end());
        for (int i = 0; i < 5; i++)
        {
            vec2[i] = vec1[i];
        }

        Set<std::string> s1{}, s2{};

        for (int i = 0; i < 10; i++)
        {
            s1.insert(vec1[i]);
            s2.insert(vec2[i]);
        }

        s1.intersection(s2);

        CPPUNIT_ASSERT(s1.contains(vec2[0]) && s1.contains(vec1[1]));
        CPPUNIT_ASSERT(!s1.contains(vec2[5]) && !s1.contains(vec1[5]));
    }

    void differenceTest()
    {
        std::vector<std::string> vec1 = genStrings(),
                                 vec2 = genStrings();

        std::random_shuffle(vec1.begin(), vec1.end());
        for (int i = 0; i < 5; i++)
        {
            vec2[i] = vec1[i];
        }

        Set<std::string> s1{}, s2{};

        for (int i = 0; i < 10; i++)
        {
            s1.insert(vec1[i]);
            s2.insert(vec2[i]);
        }

        s1.difference(s2);

        CPPUNIT_ASSERT(!s1.contains(vec1[0]) && !s1.contains(vec2[1]));
        CPPUNIT_ASSERT(s1.contains(vec1[5]));
        CPPUNIT_ASSERT(!s1.contains(vec2[5]));
    }

public:
};

CPPUNIT_TEST_SUITE_REGISTRATION(BasicSetOperationsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(TwoSetOperationsTest);
