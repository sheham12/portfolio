#include <iostream>
#include "TestHugeInteger.h"
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;
#include <chrono>
using namespace std::chrono;

/*
double HugeIntTiming(int n)
{
    system_clock::time_point startTime, endTime;
    double runTime = 0.0;
    double durationMs = 0.0;
    //int n = 100;
    int MAXNUMINTS = 100;
    int MAXRUN = 500;
    for (int numInts = 0; numInts < MAXNUMINTS; numInts++) {
        cpp_int huge1(n);
        cpp_int huge2(n);
        startTime = system_clock::now();
        for (int numRun = 0; numRun < MAXRUN; numRun++) {
            int huge3 = huge1<huge2;          //runtime for compareTo()
            //cpp_int huge3 = huge1 - huge2;  //runtime for subtract()
            //cpp_int huge3 = huge1 + huge2;  //runtime for add()
            //cpp_int huge3 = huge1 * huge2;  //runtime for multiply()
        }
        endTime = system_clock::now();
        durationMs = (duration<double, std::milli>(endTime - startTime)).count();
        runTime += durationMs / ((double)MAXRUN);
    }
    runTime = runTime / ((double)MAXNUMINTS);
    return runTime;
}
*/

double HugeIntTiming(int n) {
    system_clock::time_point startTime, endTime;
    double runTime = 0.0;
    double durationMs = 0.0;
    //int n = 100;
    int MAXNUMINTS = 100;
    int MAXRUN = 500;
    for (int numInts = 0; numInts < MAXNUMINTS; numInts++) {
        HugeInteger huge1(n);
        HugeInteger huge2(n);
        startTime = system_clock::now();
        for (int numRun = 0; numRun < MAXRUN; numRun++) {
            //HugeInteger huge3 = huge1.multiply(huge2);    //runtime for multiply()
            HugeInteger huge3 = huge1.add(huge2);       //runtime for add()
            //HugeInteger huge3 = huge1.subtract(huge2);  //runtime for subtract()
            //int huge3 = huge1.compareTo(huge2);         //runtime for compareTo()

        }
        endTime = system_clock::now();
        durationMs = (duration<double, std::milli>(endTime - startTime)).count();
        runTime += durationMs / ((double)MAXRUN);
    }
    runTime = runTime / ((double)MAXNUMINTS);
    return runTime;
}

int main() {
    // when test failed, the size of number <= NUM_DISPLAY, display the number
    unsigned int num_display = 1000;
    // iterate the MAX_SIZE_ARRAY MAX_RUN times
    unsigned int max_run = 50;
    // use for generating invalid string for constructor 1 (with string input)
    unsigned int max_invalid_string = 5;
    // different size for test
    vector<int> max_size_array = {1,20,50};

    double totalMark = 0;

    string demoLab = "Lab1"; // set to Lab1 or Lab2

    //HugeInteger x1("-4");
    //HugeInteger x1("64");
    //HugeInteger x2("-19");
    //HugeInteger x3=x1.add(x2);
    
    TestHugeInteger thi(num_display, max_run, max_invalid_string, max_size_array);

    if (demoLab == "Lab1"){
        totalMark += thi.testConstructorString();
        totalMark += thi.testConstructorNumber();
        totalMark += thi.testPositiveAddition();
    }else{
        totalMark += thi.testAdditionSubtraction();
        totalMark += thi.testCompareTo();
        totalMark += thi.testMultiplication();
    }
    

    cout << "******************************" << endl;
    cout << "*** FINAL TOTAL MARK IS " << totalMark << " ***" << endl;
    cout << "******************************" << endl;

    //cout << "the run time for 10 is: " << HugeIntTiming(10)<<endl;
    //cout << "the run time for 100 is: " << HugeIntTiming(100)<<endl;
    //cout << "the run time for 500 is: " << HugeIntTiming(500) << endl;
    //cout << "the run time for 1000 is: " << HugeIntTiming(1000) << endl;
    //cout << "the run time for 5000 is: " << HugeIntTiming(5000) << endl;
    //cout << "the run time for 10000 is: " << HugeIntTiming(10000) << endl;


	return 0;
}
