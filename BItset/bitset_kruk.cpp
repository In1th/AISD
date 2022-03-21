#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

#include "bitset.hpp"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <bitset>

class BasicSetOperationsTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(BasicSetOperationsTest);
    CPPUNIT_TEST(OperationsMinZeroTest);
    CPPUNIT_TEST(OperationsMinNotZeroTest);
    CPPUNIT_TEST_SUITE_END();


public:

    void OperationsMinZeroTest(){
        BitSet<0,15> s;
        std::vector<int> out{};
        for (int i = 0; i < 16; i+=2){
            out.push_back(i);
        }
        std::random_shuffle(out.begin(), out.end());
        for (auto val: out){
            s.insert(val);
        }

        //printf("\nBitMap<%d,%d>: \n",0,15);
        //s.print();

        std::random_shuffle(out.begin(), out.end());
        for (auto val: out){
            CPPUNIT_ASSERT(s.contains(val));
            CPPUNIT_ASSERT(!s.contains(val+1));
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val: out){
            s.remove(val);
        }

        CPPUNIT_ASSERT(!s.contains(out[0]));

    }

    void OperationsMinNotZeroTest(){
        BitSet<2,17> s;
        std::vector<int> out{};
        for (int i = 2; i < 17; i+=2){
            out.push_back(i);
        }
        std::random_shuffle(out.begin(), out.end());
        for (auto val: out){
            s.insert(val);
        }
        //printf("\nBitMap<%d,%d>: \n",2,17);
        //s.print();

        std::random_shuffle(out.begin(), out.end());
        for (auto val: out){
            CPPUNIT_ASSERT(s.contains(val));
            CPPUNIT_ASSERT(!s.contains(val+1));
        }

        std::random_shuffle(out.begin(), out.end());
        for (auto val: out){
            s.remove(val);
        }

        CPPUNIT_ASSERT(!s.contains(out[0]));

    }

};

class TwoSetOperationsTest : public CppUnit::TestFixture{
CPPUNIT_TEST_SUITE(TwoSetOperationsTest);
        CPPUNIT_TEST(unionTest);
        CPPUNIT_TEST(intersectionTest);
        CPPUNIT_TEST(differenceTest);
    CPPUNIT_TEST_SUITE_END();

    static const int MIN = 0, MAX = 15;

    static std::vector<int> gen(int a, int b) noexcept
    {
        std::vector<int> out1{}, out{};

        for (int i = a; i <= b; i++){
            out1.push_back(i);
        }
        std::random_shuffle(out1.begin(), out1.end());
        for (int i = 0; i < 5; i++){
            out.push_back(out1[i]);
        }
        return out;
    };

public:

    void unionTest(){

        std::vector<int> vec1 = gen(MIN,MAX/2),
                vec2 = gen(MAX/2 + 1, MAX);

        std::random_shuffle(vec1.begin(), vec1.end());
        for (int i = 0; i < 3; i++){
            vec2[i] = vec1[i];
        }

        BitSet<MIN, MAX> s1{},s2{};

        for(int i = 0; i < 5; i++){
            s1.insert(vec1[i]);
            s2.insert(vec2[i]);
        }

        //std::cout << std::endl << "[union] in: "<< std::endl;
        //s1.print();
        //s2.print();
        s1.Union(s2);
        //std::cout << "out:" << std::endl;
        //s1.print();

        CPPUNIT_ASSERT(s1.contains(vec2[0]));
        CPPUNIT_ASSERT(s1.contains(vec2[3]));
    }

    void intersectionTest(){
        std::vector<int> vec1 = gen(MIN,MAX/2),
                vec2 = gen(MAX/2 + 1, MAX);

        std::random_shuffle(vec1.begin(), vec1.end());
        for (int i = 0; i < 3; i++){
            vec2[i] = vec1[i];
        }

        BitSet<MIN, MAX> s1{},s2{};

        for(int i = 0; i < 5; i++) {
            s1.insert(vec1[i]);
            s2.insert(vec2[i]);
        }

        //std::cout << std::endl << "[intersection] in: "<< std::endl;
        //s1.print();
        //s2.print();
        s1.intersection(s2);
        //std::cout << "out:" << std::endl;
        //s1.print();

        CPPUNIT_ASSERT(s1.contains(vec2[0]) && s1.contains(vec1[1]));
        CPPUNIT_ASSERT(!s1.contains(vec2[3]) && !s1.contains(vec1[3]));
    }

    void differenceTest(){
        std::vector<int> vec1 = gen(MIN,MAX/2),
                vec2 = gen(MAX/2 + 1, MAX);

        std::random_shuffle(vec1.begin(), vec1.end());
        for (int i = 0; i < 3; i++){
            vec2[i] = vec1[i];
        }

        BitSet<MIN, MAX> s1{},s2{};

        for(int i = 0; i < 5; i++){
            s1.insert(vec1[i]);
            s2.insert(vec2[i]);
        }

        //std::cout << std::endl << "[difference] in: "<< std::endl;
        //s1.print();
        //s2.print();
        s1.difference(s2);
        //std::cout << "out:" << std::endl;
        //s1.print();

        CPPUNIT_ASSERT(!s1.contains(vec1[0]) && !s1.contains(vec2[1]));
        CPPUNIT_ASSERT(s1.contains(vec1[3]));
        CPPUNIT_ASSERT(!s1.contains(vec2[3]));
    }

public:
};

CPPUNIT_TEST_SUITE_REGISTRATION(BasicSetOperationsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(TwoSetOperationsTest);
