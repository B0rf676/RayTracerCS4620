#include <iostream>
#include <string>

using namespace std;

int main() {

    string line = "#Comment";

    line += " more info";

    string vert = "v 0 0 0";

    int spaceIndex = vert.find(" ");
    if(spaceIndex != string::npos){
        cout << "First space at index: " << spaceIndex << endl;
    }

    cout << line << endl;

    return 0;
}