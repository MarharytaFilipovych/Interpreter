#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

class Tokens
{   
    const string functions[4] = { "pow", "abs", "min", "max" };
    bool isOperator(char symbol)
    {
        return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '=');
    }
    
        bool validateParentheses(vector<string>& tokens)
        {
            stack<string> temp;
            int count = 0;
            for (int i = 0; i < tokens.size(); i++)
            {              
                    if (tokens[i] == "(" )
                    {
                        count = 0;
                        temp.push(tokens[i]);
                    }
                    else if (tokens[i] == ")")
                    {
                        if (temp.empty() || temp.top() != "(")
                        {
                            return false;
                        }
                        if (count % 2 == 0 )
                        {
                            return false;
                        }
                        temp.pop();
                    }
                    
                    else {
                        count++;
                    }                 
            }
            if (temp.empty())
            {
                return true;
            }
            return false;
        }
        bool validateFunctions(vector<string>& tokens)
        {
            int i = 0;
            while (i < tokens.size())
            {
                bool foundFunction = false;
                for (int j = 0; j < 4; j++)  
                {
                    if (tokens[i] == functions[j])
                    {
                        foundFunction = true;
                        if (i + 1 >= tokens.size() || tokens[i + 1] != "(")
                        {
                            return false;  
                        }
                        i++;
                        int count = 0;                       
                        while (i < tokens.size() && tokens[i] != ")")
                        {
                            if (tokens[i] == ",")
                            {
                                count++;
                            }
                            i++;
                        }                     
                        if (count != 1)
                        {
                            return false;
                        }
                       
                        break;  
                    }
                }
                if (!foundFunction)
                {
                    i++;  
                }
            }
            return true;  
        }

public:
    vector<string> ParseInput(string input)
    {
        vector<string> tokens;
        int i = 0;
        while(i < input.length())
        {
            if (isdigit(input[i]) || (input[i] == '-' && (i == 0 || !isdigit(input[i - 1]))))
            {
                
                string current_token = "";
                if (input[i] == '-')
                {
                    current_token += input[i];
                    i++;
                }
                while (i < input.length() && (isdigit(input[i]) || input[i] == '.'))
                {
                    current_token += input[i];
                    i++;
                }
                tokens.push_back(current_token);
            }
            else if (isalpha(input[i]))
            {
                bool isFunction = false;
                for (int j = 0; j < 4; j++)
                {
                    if (input.substr(i, functions[j].length()) == functions[j])
                    {
                        tokens.push_back(functions[j]);
                        i += functions[j].length();
                        isFunction = true;
                        break;
                    }                  
               }
                if (!isFunction) {
                    cout << "Invalid input!" << endl;
                    return {};
                }
            }
            else {
                if (isOperator(input[i]))
                {
                    if (i >= 0 && !isdigit(input[i - 1]) && input[i] != '-')
                    {
                        cout << "Invalid input!" << endl;
                        return {};
                    }
                    tokens.push_back(string(1, input[i]));

                }
                else if (input[i] == ')' || input[i] == '(' || input[i] == ',')
                {
                    if ((input[i] == '(' && input[i + 1] == ')') || (input[i] == '(' && input[i + 2] == ')' && input[i + 1] == ','))
                    {
                        cout << "Invalid input!" << endl;
                        return {};
                    }
                    
                    tokens.push_back(string(1, input[i]));

                }
                else {
                    cout << "Invalid input !" << endl;
                    return {};
                }
                i++;
            }
        }
        if (!validateParentheses(tokens))
        {
            cout << "Parentheses mismatch!" << endl;
            return {};
        }
        if (!validateFunctions(tokens))
        {
            cout << "Functions mismatch!" << endl;
            return {};
        }
        
        return tokens;
    }
};



class ReversePolishNotation
{

};


int main()
{
    string input;
    cout << "Enter an expression:" << endl;
    getline(cin, input);
    cout << "Echo: " << input << endl;
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    Tokens tokens;
    vector<string> parts = tokens.ParseInput(input);
    for (int i = 0; i < parts.size(); i++)
    {
        cout << parts[i] << endl;
    }

}

