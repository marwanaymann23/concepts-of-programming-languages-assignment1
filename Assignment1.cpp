#include <iostream>
#include <stack>

using namespace std;

enum CallType
{
    callA,
    callB,
    callC,
    callD
};

int F(int n) // n = 3   result = 11
{
    if (n <= 1)
        return 1;

    int a = n + F(n - 1); // 8

    int b = n * F(n / 2); // 3
                          /*
                                  int c = n - 2 - (a + b) % 2;
                              int d = F(c); // 5*/

    return a + b; // 11

     //return b;
}

struct fCall
{
    CallType type;
    int a = 0, b = 0, c = 0, d = 0, res = 0;
    int n = 0;
};

int fIterative(int n)
{
    stack<fCall> s;

    fCall call;
    call.type = callA;
    call.n = n;

    s.push(call); // initial

    int res = 0;

    int a = 0, b = 0, c = 0, d = 0;
    int aRes = 0, bRes = 0;
    int a_final = a;
    bool a_Terminated = false;
    bool b_Terminated = false;
    bool back = false;

    while (!s.empty())
    {
        fCall call = s.top();
        //s.pop();


        if (a_Terminated) {
            aRes += call.n;
            s.pop();

            fCall c1;
            c1.type = callB;
            c1.n = call.n / 2;
            s.push(c1);

            continue;
        }

        if (b_Terminated) {
            bRes *= call.n;
            s.pop();
            continue;
        }

        if (call.type == callA) {
            //if(back) 
            if (call.n <= 1) {
                aRes = 1;
                a_Terminated = true;
                s.pop();
                continue;
            }
            else {
                fCall c1;
                c1.type = callA;
                c1.n = call.n - 1;
                s.push(c1);
            }
        }
        if (call.type == callB) {
            //if(back) 
            a_Terminated = false;
            if (call.n <= 1) {
                bRes = 1;
                b_Terminated = true;
                s.pop();
                continue;
            }
            else {
                fCall c1;
                c1.type = callB;
                c1.n = call.n / 2;
                s.push(c1);
            }
        }      
    }
    return aRes + bRes;
}

int main()
{
    // cout << fIterative(2) << endl;
    cout << F(6) << endl;
    cout << fIterative(6) << endl;

    return 0;
}