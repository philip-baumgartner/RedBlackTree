#include <iostream>
#include <string>
using namespace std;
void fall1(string name)
{
    cout << "fall1:" << endl;
    cout << "vater von: " << name << " ist linkes kind seines vaters" << endl;
    cout << "onkel von: " << name << " ist rot" << endl;
}
void fall2(string name)
{
    cout << "fall2:" << endl;
    cout << "vater von: " << name << " ist linkes kind seines vaters" << endl;
    cout << "onkel von: " << name << " ist schwarz" << endl;
    cout << name << " ist rechtes kind" << endl;
}
void fall3(string name)
{
    cout << "fall3:" << endl;
    cout << "vater von: " << name << " ist linkes kind seines vaters" << endl;
    cout << "onkel von: " << name << " ist schwarz" << endl;
    cout << name << " ist linkes kind" << endl;
}
void fall4(string name)
{
    cout << "fall4:" << endl;
    cout << "vater von: " << name << " ist rechtes kind seines vaters" << endl;
    cout << "onkel von: " << name << " ist rot" << endl;
}
void fall5(string name)
{
    cout << "fall5:" << endl;
    cout << "vater von: " << name << " ist rechtes kind seines vaters" << endl;
    cout << "onkel von: " << name << " ist schwarz" << endl;
    cout << name << " ist rechtes kind" << endl;
}
void fall6(string name)
{
    cout << "fall6:" << endl;
    cout << "vater von: " << name << " ist rechtes kind seines vaters" << endl;
    cout << "onkel von: " << name << " ist schwarz" << endl;
    cout << name << " ist linkes kind" << endl;
}

