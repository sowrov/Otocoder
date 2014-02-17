#include "sstream"
#include "stack"
#include "cassert"
#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdlib"
#include "cctype"
#include "functional"
#include "deque"
#include "iomanip"
#include "list"
#include "cstring"
#include "algorithm"
#include "cstdio"
#include "vector"
#include "string"
#include "map"
#include "queue"
#include "bitset"
#include "numeric"
#include "utility"
#include "set"

using namespace std;

#define Zclr(arr) memset(arr, 0, sizeof(arr))
#define Nclr(arr) memset(arr, -1, sizeof(arr))
#define M31 1<<30
#define Pi (2.0*acos(0.0))
#define Eps (1e-9)
#define Rep(_var, _N) for (int _var=0; _var<_N; _var++ )
#define For(_var, _S,  _N) for (int _var=_S; _var<=_N; _var++ )

class EllysNewNickname {
public:
    int getLength(string nickname) {
        int out;

        return out;
    }
};

// <editor-fold defaultstate="collapsed" desc="Generated Code">
namespace otocoder {
    int run_test_case(int );
    bool run_full_test();
    // casenum<-1 to run full test set, casenum=-1 (default) to run all sample test cases,
    // casenum>-1 value to run specific sample case
    void run_test(int casenum = -1, bool quiet = false) {
        if (casenum < -1) {
            if (!run_full_test()) {
                cerr << "Illegal inputs in full test cases!" << endl;
            }
            return;
        }
        if (casenum > -1) {
            if (run_test_case(casenum) == -1 && !quiet) {
                cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
            }
            return;
        }

        int correct = 0, total = 0;
        for (int i=0;; ++i) {
            int x = run_test_case(i);
            if (x == -1) {
                if (i >= 100) break;
                continue;
            }
            correct += x;
            ++total;
        }

        if (total == 0) {
            cerr << "No test cases run." << endl;
        } else if (correct < total) {
            cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
        } else {
            cerr << "All " << total << " tests passed!" << endl;
        }
    }

    int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
        cerr << "Example " << casenum << "... "; 

        string verdict;
        vector<string> info;
        char buf[100];

        if (elapsed > CLOCKS_PER_SEC / 200) {
            sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
            info.push_back(buf);
        }

        if (expected == received) {
            verdict = "PASSED";
        } else {
            verdict = "FAILED";
        }

        cerr << verdict;
        if (!info.empty()) {
            cerr << " (";
            for (int i=0; i<(int)info.size(); ++i) {
                if (i > 0) cerr << ", ";
                cerr << info[i];
            }
            cerr << ")";
        }
        cerr << endl;

        if (verdict == "FAILED") {
            cerr << "    Expected: " << expected << endl; 
            cerr << "    Received: " << received << endl; 
        }

        return verdict == "PASSED";
    }

    int run_test_case(int casenum) {
        switch (casenum) {
        case 0: {
            string nickname = "tourist";
            int expected_ = 6;

            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 1: {
            string nickname = "eagaeoppooaaa";
            int expected_ = 6;

            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 2: {
            string nickname = "esprit";
            int expected_ = 6;

            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 3: {
            string nickname = "ayayayayayaya";
            int expected_ = 1;

            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 4: {
            string nickname = "wuuut";
            int expected_ = 3;

            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 5: {
            string nickname = "naaaaaaaanaaaanaananaaaaabaaaaaaaatmaaaaan";
            int expected_ = 16;

            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        default:
            return -1;
        }
    }

    //This method will only accept input files that are formatted in proper way.
    //Command line example: EllysNewNickname.exe -2 <EllysNewNickname.io
    bool run_full_test() {
        int testCase, N, caseNo, correct=0;
        string nickname;
        int expected_;

        std::cin>>testCase; std::cin.ignore(10, '\n');
        for (int i=0; i<testCase; i++) {
            std::cin>>caseNo; std::cin.ignore(10, '\n');
            std::getline(std::cin,nickname);
            std::cin>>expected_; std::cin.ignore(10, '\n');
            clock_t start_           = clock();
            int received_ = EllysNewNickname().getLength(nickname);
            correct += verify_case(caseNo, expected_, received_, clock()-start_);
        }//end of testCase for loop

        if (testCase == 0) {
            cerr << "No test cases run." << endl;
        } else if (correct < testCase) {
            cerr << "Some cases FAILED (passed " << correct << " of " << testCase << ")." << endl;
        } else {
            cerr << "All " << testCase << " tests passed!" << endl;
            std::ofstream ofs("EllysNewNickname.st", std::ios_base::app);
            ofs<<time(0)<<std::endl;
            ofs.close();
        }
        return true;
    }

}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        otocoder::run_test();
    } else {
        for (int i=1; i<argc; ++i)
            otocoder::run_test(atoi(argv[i]));
    }
}
// </editor-fold>
