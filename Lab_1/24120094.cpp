#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <cctype>
using namespace std;

void absolute(string &num);
int precedence (char operation);
int compareNumber(const string &num_1, const string &num_2);
int compareOperation(char operation_1, char operation_2);
string subtraction(string num_1, string num_2);
string addition(string num_1, string num_2);
string multiplication(string num_1, string num_2);
string division(string num_1, string num_2);
void changeToPostfix(const string &expression, queue <string>&postfix);

int main(int argc, char *argv[])
{
    string input_file_name = argv[1], output_file_name = argv[2];
    ifstream fin(input_file_name);
    ofstream fout(output_file_name);
    if (!fin.is_open() || !fout.is_open())
    {
        cerr << "Can't open file." << endl;
        exit(1);
    }
    else
    {
        string line;
        while(getline(fin, line))
        {
            stack <string> operate;
            queue <string> postfix;
            changeToPostfix(line, postfix);
            int error = 0;
            while (!postfix.empty())
            {
                if (isdigit(postfix.front()[0]) || (postfix.front()[0] == '-' && isdigit(postfix.front()[1])))
                {
                    operate.push(postfix.front());
                }
                else
                {
                    switch (postfix.front()[0])
                    {
                        case '+': 
                        {
                            if (operate.size() < 2)
                            {
                                error = 1;
                            }
                            else
                            {
                                string num_1 = operate.top();
                                operate.pop();
                                string num_2 = operate.top();
                                operate.pop();
                                operate.push(addition(num_2, num_1));
                            }
                            break;
                        }
                        case '-':
                        {
                            if (operate.size() < 2)
                            {
                                error = 1;
                            }
                            else
                            {
                                string num_1 = operate.top();
                                operate.pop();
                                string num_2 = operate.top();
                                operate.pop();
                                operate.push(subtraction(num_2, num_1));
                            }
                            break;
                        }
                        case '*':
                        {
                            if (operate.size() < 2)
                            {
                               error = 1;
                            }
                            else
                            {
                                string num_1 = operate.top();
                                operate.pop();
                                string num_2 = operate.top();
                                operate.pop();
                                operate.push(multiplication(num_2, num_1));
                            }
                            break;
                        }
                        case '/':
                        {
                            if (operate.size() < 2)
                            {
                                error = 1;
                            }
                            else
                            {
                                string num_1 = operate.top();
                                operate.pop();
                                string num_2 = operate.top();
                                operate.pop();
                                string ans = division(num_2, num_1);
                                if (ans.front() == 'E')
                                {
                                    fout << ans << endl;
                                    error = 2;
                                }
                                else 
                                {
                                    operate.push(ans);
                                }
                            }
                            break;
                        }
                    }
                }
                postfix.pop();
                if (error > 0)
                {
                    break;
                }
            }
            if (error == 1)
            {
                fout << "Error: Not enough operands." << endl;
            }
            else if (error == 0 && !operate.empty())
            {
                fout << operate.top() << endl;
            }
            while (!operate.empty())
            {
                operate.pop();
            }
            while (!postfix.empty())
            {
                postfix.pop();
            }
        }
        fin.close();
        fout.close();
    }
}

void absolute(string &num)
{
    if (num.front() == '-')
    {
        num.erase(0, 1);
    }
}

int compareNumber(const string &num_1, const string &num_2)
{
    if (num_1.length() < num_2.length())
    {
        return 0;
    }
    else if (num_1.length() > num_2.length())
    {
        return 2;
    }
    else
    {
        for (int i = 0; i < num_1.length(); i++)
        {
            if (num_1[i] > num_2[i])
            {
                return 2;
            }
            else if (num_1[i] < num_2[i])
            {
                return 0;
            }
        }
        return 1;
    }
}

string addition(string num_1, string num_2)
{
    string ans;
    stack <char> add;
    if (num_1.front() == '-' && num_2.front() == '-')
    {
        ans = "-";
        absolute(num_1);
        absolute(num_2);
    }
    else if (num_1.front() == '-' && num_2.front() != '-')
    {
        absolute(num_1);
        return subtraction(num_2, num_1);
    }
    else if (num_1.front() != '-' && num_2.front() == '-')
    {
        absolute(num_2);
        return subtraction(num_1, num_2);
    }
    else
    {
        ans = "";
    }
    int i = num_1.length() - 1, j = num_2.length() - 1, remainder = 0;
    while (i >= 0 || j >= 0 || remainder != 0)
    {
        int digit_1 = (i >= 0) ? num_1[i] - '0' : 0;
        int digit_2 = (j >= 0) ? num_2[j] - '0' : 0;
        int digit_ans = digit_1 + digit_2 + remainder;
        remainder = digit_ans / 10;
        add.push((digit_ans % 10) + '0');
        i--;
        j--;
    }
    while (!add.empty())
    {
        ans += add.top();
        add.pop();
    }
    return ans;
}

string subtraction(string num_1, string num_2)
{
    bool negative = false;
    if (num_1.front() == '-' && num_2.front() == '-')
    {
        absolute(num_1);
        absolute(num_2);
        return subtraction(num_2, num_1);
    }
    else if (num_1.front() == '-' && num_2.front() != '-')
    {
        num_2.insert(0, 1, '-');
        return addition(num_1, num_2);
    }
    else if (num_1.front() != '-' && num_2.front() == '-')
    {
        absolute(num_2);
        return addition(num_1, num_2);
    }
    else
    {
        if (compareNumber(num_1, num_2) == 1)
        {
            return "0";
        }
        else if (compareNumber(num_1, num_2) == 2)
        {
            string ans = "";
            stack <char> subtract;
            int i = num_1.length() - 1, j = num_2.length() - 1, remainder = 0, digit_ans;
            while (i >= 0 || j >= 0)
            {
                int digit_1 = (i >= 0) ? num_1[i] - '0' : 0;
                int digit_2 = (j >= 0) ? num_2[j] - '0' : 0;
                if (digit_1 < digit_2 + remainder)
                {
                    digit_ans = (digit_1 + 10) - (digit_2 + remainder);
                    remainder = 1;
                }
                else
                {
                    digit_ans = digit_1 - (digit_2 + remainder);
                    remainder = 0;
                }
                subtract.push(digit_ans + '0');
                i--;
                j--;
            }
            while (!subtract.empty())
            {
                ans += subtract.top();
                subtract.pop();
            }
            while (ans.front() == '0')
            {
                ans.erase(0, 1);
            }
            return ans;
        }
        else
        {
            string ans = "-";
            negative = true;
            stack <char> subtract;
            int i = num_1.length() - 1, j = num_2.length() - 1, remainder = 0, digit_ans;
            while (i >= 0 || j >= 0)
            {
                int digit_1 = (i >= 0) ? num_1[i] - '0' : 0;
                int digit_2 = (j >= 0) ? num_2[j] - '0' : 0;
                if (digit_2 < digit_1 + remainder)
                {
                    digit_ans = (digit_2 + 10) - (digit_1 + remainder);
                    remainder = 1;
                }
                else
                {
                    digit_ans = digit_2 - (digit_1 + remainder);
                    remainder = 0;
                }
                subtract.push(digit_ans + '0');
                i--;
                j--;
            }
            while (!subtract.empty())
            {
                ans += subtract.top();
                subtract.pop();
            }
            if (negative)
            {
                while ( ans.length() > 2 && ans[1] == '0')
                {
                    ans.erase(1, 1);
                }
            }
            else
            {
                while (ans.length() > 1 && ans[0] == '0')
                {
                    ans.erase(0, 1);
                }
            }
            return ans;
        }
    }
}

string multiplication(string num_1, string num_2)
{
    string ans = "";
    stack <char> multiply;
    bool negative = false;
    if ((num_1.front() == '-' && num_2.front() != '-') || (num_1.front() != '-' && num_2.front() == '-'))
    {
        negative = true;
    }
    absolute(num_1);
    absolute(num_2);
    for (int i = num_1.length() - 1; i >= 0; i--)
    {
        int digit_1 = num_1[i] - '0', remainder = 0;
        for (int j = num_2.length() - 1; j >= 0; j--)
        {
            int digit_2 = num_2[j] - '0';
            int digit_ans = digit_1 * digit_2 + remainder;
            remainder = digit_ans / 10;
            multiply.push((digit_ans % 10) + '0');
        }
        while (remainder != 0)
        {
            multiply.push((remainder % 10) + '0');
            remainder /= 10;
        }
        string temp = "";
        while (!multiply.empty())
        {
            temp += multiply.top();
            multiply.pop();
        }
        for (int j = num_1.length() - 1; j > i; j--)
        {
            temp += '0';
        }
        ans = addition(ans, temp);
    }
    while (ans.length() > 1 && ans.front() == '0')
    {
        ans.erase(0, 1);
    }
    if (negative)
    {
        return ans.insert(0, 1, '-');
    }
    else
    {
        return ans;
    }
}

string division(string num_1, string num_2)
{
    if (num_2 == "0")
    {
        return "Error: Divided by zero.";
    }
    string ans = "", remainder;
    bool negative = false;
    if ((num_1.front() == '-' && num_2.front() != '-') || (num_1.front() != '-' && num_2.front() == '-'))
    {
        negative = true;
    }
    absolute(num_1);
    absolute(num_2);
    if (compareNumber(num_1, num_2) == 0)
    {
        return "Error: Float division.";
    }
    for(int i = 0; i < num_1.length(); i++)
    {
        remainder += num_1[i];
        if (remainder.empty() || compareNumber(remainder, num_2) == 0)
        {
            ans += '0';
        }
        else 
        {
            int left = 1, right = 9;
            string divisor;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                string test = to_string(mid);
                int compare = compareNumber(multiplication(num_2, test), remainder);
                if (compare <= 1)
                {
                    divisor = test;
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
            ans += divisor;
            string multiply = multiplication(num_2, divisor);
            remainder = subtraction(remainder, multiply);
        }
    }
    while (remainder.length() > 1 && remainder.front() == '0')
    {
        remainder.erase(0, 1);
    }
    while (ans.length() > 1 && ans.front() == '0')
    {
        ans.erase(0, 1);
    }
    if (remainder != "0")
    {
        return "Error: float division.";
    }
    else
    {
        if (negative)
        {
            return ans.insert(0, 1, '-');
        }
        else
        {
            return ans;
        }
    }
}

int precedence (char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    else if (operation == '*' || operation == '/')
    {
        return 2;
    }
    else 
    {
        return -1;
    }
}

int compareOperation(char operation_1, char operation_2)
{
    if (precedence(operation_1) == precedence(operation_2))
    {
        return 1;
    }
    else if (precedence(operation_1) > precedence(operation_2))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void changeToPostfix(const string &expression, queue <string>&postfix)
{
    stringstream stream(expression);
    string split;
    stack <char> operation;
    stack <char> bracket;
    while (stream >> split)
    {
        bool negative = false;
        if (split.front() == '(')
        {
            if (split.back() == ')')
            {
                split.erase(0,1);
                split.pop_back();
                negative = true;
            }
            else
            {
                operation.push(split.front());
                bracket.push(split.front());
                split.erase(0,1);
            }
        }
        else if (split.back() == ')')
        {
            if (bracket.empty())
            {
                cerr << "Incorrect bracket sequence." << endl;
                return;  
            }
            else
            {
                bracket.pop();
                while (operation.top() != '(')
                {
                    postfix.push(string(1, operation.top()));
                    operation.pop();
                }
                operation.pop();
            }
            split.pop_back();
        }
        if (negative)
        {
            postfix.push(split);
        }
        else
        {
            if (isdigit(split[0]))
            {
                postfix.push(split);
            }
            else
            {
                int compare = (!operation.empty()) ? compareOperation(split[0], operation.top()) : 3;
                if (operation.empty() || operation.top() == '(')
                {
                    operation.push(split[0]);
                }
                else
                {
                    while (compare <= 1)
                    {
                        postfix.push(string(1, operation.top()));
                        operation.pop();
                        compare = (!operation.empty()) ? compareOperation(split[0], operation.top()) : 3;                
                    }
                    operation.push(split[0]);
                }
            }
        }
    }
    if (!bracket.empty())
    {
        cerr << "Error: Too many open bracket." << endl;
        return;
    }
    while (!operation.empty())
    {
        postfix.push(string(1, operation.top()));
        operation.pop();
    }
}

