#include <iostream>
#include <map>

using namespace std;

int toInt(string s) {
    int res = 0;
    int pow10 = 1;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        res += (s[n - 1 - i] - '0') * pow10;
        pow10 *= 10;
    }
    return res;
}

int main() {
    map<int, pair<string, string>> students;
    cout << "Type \"Break\" to end queries.\n";
    while (true) {
        string in;
        cin >> in;
        if (in == "Break") break;
        string oper = "";
        int id;
        string idString(""), name(""), studentClass("");
        int i = 0;
        while (in[i] != '(') 
            oper += in[i++];
        i++;
        while (in[i] != ',' && in[i] != ')') 
            idString += in[i++];
        id = toInt(idString);
        if (oper == "Infor") {
            auto it = students.find(id);
            if (it == students.end()) cout << "NA,NA\n";
            else cout << (it->second).first << "," << (it->second).second << "\n";
            continue;
        }
        if (oper == "Delete") {
            students.erase(id);
            continue;
        }
        i++;
        while (in[i] != ',')
            name += in[i++];
        i++;
        while (in[i] != ')') 
            studentClass += in[i++];
        students.insert({id, {name, studentClass}});
    }
    return 0;
}