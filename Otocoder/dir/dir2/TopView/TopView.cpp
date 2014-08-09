#include "cstdlib"
#include "set"
#include "vector"
#include "map"
#include "cstdio"
#include "stack"
#include "iostream"
#include "cctype"
#include "cstring"
#include "cassert"
#include "utility"
#include "string"
#include "ctime"
#include "numeric"
#include "iomanip"
#include "bitset"
#include "algorithm"
#include "deque"
#include "sstream"
#include "functional"
#include "cmath"
#include "queue"
#include "fstream"
#include "list"

using namespace std;

#define Zclr(arr) memset(arr, 0, sizeof(arr))
#define Nclr(arr) memset(arr, -1, sizeof(arr))
#define M31 1<<30
#define Pi (2.0*acos(0.0))
#define Eps (1e-9)
#define Rep(_var, _N) for (int _var=0; _var<_N; _var++ )
#define For(_var, _S,  _N) for (int _var=_S; _var<=_N; _var++ )

class TopView {
public:
    string findOrder(vector<string> grid) {
        string out;

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

    int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
            cerr << "    Expected: \"" << expected << "\"" << endl;
            cerr << "    Received: \"" << received << "\"" << endl;
        }

        return verdict == "PASSED";
    }

    int run_test_case(int casenum) {
        switch (casenum) {
        case 0: {
            string grid[] = {"..AA..", ".CAAC.", ".CAAC."};
            string expected_ = "CA";

            clock_t start_           = clock();
            string received_ = TopView().findOrder(vector<string>(grid, grid + (sizeof grid / sizeof grid[0])));
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 1: {
            string grid[] = {"..47..", "..74.."};
            string expected_ = "ERROR!";

            clock_t start_           = clock();
            string received_ = TopView().findOrder(vector<string>(grid, grid + (sizeof grid / sizeof grid[0])));
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 2: {
            string grid[] = {"bbb666", ".655X5", "a65AA5", "a65AA5", "a65555"};
            string expected_ = "65AXab";

            clock_t start_           = clock();
            string received_ = TopView().findOrder(vector<string>(grid, grid + (sizeof grid / sizeof grid[0])));
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        case 3: {
            string grid[] = {"aabbaaaaaaaaaaaaaaaaaa", "aabbccccccccccccccaaaa", "aab11111ccccccccccaaaa", "aab12221ccccccccccaaaa", "aab12221ccccccccccaaaa", "aab12221ccccccccccaaaa", "aab12221ccccccccccaaaa", "aab12221ccccccccccaaaa", "aab12221ddddddddddaaaa", "aab13331DDDDDDDDDDaaaa", "aab13331DDDDDDDDDDaaaa", "aa.11111DDDDDDDDDDaaaa", "aaaaaaaaaaaaaaaaaaaaaa"};
            string expected_ = "ERROR!";

            clock_t start_           = clock();
            string received_ = TopView().findOrder(vector<string>(grid, grid + (sizeof grid / sizeof grid[0])));
            return verify_case(casenum, expected_, received_, clock()-start_);
        }
        default:
            return -1;
        }
    }

    const std::string currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return buf;
    }

    //This method will only accept input files that are formatted in proper way.
    //Command line example: TopView.exe -2 <TopView.io
    bool run_full_test() {
        int testCase, N, caseNo, correct=0;
        vector<string> grid;
        string grid_sin;
        string expected_;

        std::cin>>testCase; std::cin.ignore(10, '\n');
        for (int i=0; i<testCase; i++) {
            std::cin>>caseNo; std::cin.ignore(10, '\n');
            grid.clear();
            std::cin>>N; std::cin.ignore(10, '\n');
            for(int j=0; j<N; j++) {
                std::getline(std::cin,grid_sin );
                grid.push_back(grid_sin);
            }
            std::getline(std::cin,expected_);
            clock_t start_           = clock();
            string received_ = TopView().findOrder(grid);
            correct += verify_case(caseNo, expected_, received_, clock()-start_);
        }//end of testCase for loop

        if (testCase == 0) {
            cerr << "No test cases run." << endl;
        } else if (correct < testCase) {
            cerr << "Some cases FAILED (passed " << correct << " of " << testCase << ")." << endl;
        } else {
            cerr << "All " << testCase << " tests passed!" << endl;
            std::ofstream ofs("TopView.st", std::ios_base::app);
            ofs<<currentDateTime()<<std::endl;
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
