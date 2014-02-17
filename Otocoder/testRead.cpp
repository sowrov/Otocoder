#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int testCase, n, caseNo;

    vector<string> str1;
    vector<string> str2;
    string str;

    cin>>testCase;
    cin.ignore(10, '\n');

    cout<<"Number of testcase: "<<testCase<<endl;
    for (int i=0; i<testCase; i++) {
        cin>>caseNo; cin.ignore(10, '\n');

        //if next input is array
        cin>>n;
        cin.ignore(10, '\n');
        //std::getline(std::cin, str); //read last newline
        cout<<"Case: "<<caseNo<<" 1st Array size: "<<n<<endl;
        for (int j=0; j<n; j++) {
            std::getline(std::cin, str);
            str1.push_back(str);
        }

        cin>>n;
        cin.ignore(10, '\n');
        cout<<"2nd Array size: "<<n<<endl;
        for (int j=0; j<n; j++) {
            std::getline(std::cin, str);
            str2.push_back(str);
        }
    }

    //for (int i=0; i<str1.size(); i++) {
    //    cout<<str1[i]<<endl;
    //}
    return 0;
}

