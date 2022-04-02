// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char oper) {
    switch (oper) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '/': return 3;
    case '*': return 3;
    case ' ': return 5;
    default: return 4;
    }
}
int calculation(char oper, int a, int b) {
    switch (oper) {
    case '+': return (b + a);
    case '-': return (b - a);
    case '*': return (b * a);
    case '/':
        if (a != 0)
            return b / a;
    default: return 0;
    }
}
std::string infx2pstfx(std::string inf) {
  std::string outp;
    char probel = ' ';

    for (int i = 0; i < inf.size(); i++) {
        if (priority(inf[i]) == 4) {
            outp.push_back(inf[i]);
            outp.push_back(probel);
        } else {
            if (priority(inf[i]) == 0) {
                stack1.push(inf[i]);
            } else if (stack1.isEmpty()) {
                stack1.push(inf[i]);
            } else if ((priority(inf[i]) > priority(stack1.get()))) {
                stack1.push(inf[i]);
            } else if (priority(inf[i]) == 1) {
                while (priority(stack1.get()) != 0) {
                    outp.push_back(stack1.get());
                    outp.push_back(probel);
                    stack1.pop();
                }
                stack1.pop();
            } else {
                while (!stack1.isEmpty() && (priority(inf[i]) <= priority(stack1.get()))) {
                    outp.push_back(stack1.get());
                    outp.push_back(probel);
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        outp.push_back(stack1.get());
        outp.push_back(probel);
        stack1.pop();
    }
    for (int i = 0; i < outp.size(); i++) {
        if (outp[outp.size() - 1] == ' ')
            outp.erase(outp.size() - 1);
    }
    return outp;
}

int eval(std::string pref) {
  int res = 0;
    for (int i = 0; i < pref.size(); i++) {
        if (priority(pref[i]) == 4) {
            stack2.push(pref[i] - '0');
        } else if (priority(pref[i]) < 4) {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            stack2.push(calculation(pref[i], a, b));
        }
    }
    res = stack2.get();
    return res;
}
