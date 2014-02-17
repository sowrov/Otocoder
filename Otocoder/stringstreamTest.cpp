#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main () {
    string str;
    char buffer[200];
    string strText = "Searching for DRAMA in the quick search box should show a number of items, but it doesn't.\n I'm asked to nuke all stuff in the system,\n so I won't reference any items.\n Will reproduce and file proper bug report later.\n This is mostly so that I don't forget it.";
    int pos = strText.find("");
    printf("find nothing %d\n", pos);

    istringstream sstream(strText);

    while(!(sstream.eof()||sstream.bad()||sstream.fail())) {
        sstream.getline(buffer, 200);
        printf("%s\n", buffer);
    }
    str = strText.substr(strText.find_last_of(' ')+1);
    printf("\n\n--%s\n",str.c_str());
    return 0;
}
