#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <map>

class Tokens
{
    string constructNumber(const string& input, int& i)
    {
        string current_number = "";
        if (input[i] == '-')
        {
            current_number += input[i];
            i++;
        }
        while (i < input.length() && (isdigit(input[i]) || input[i] == '.'))
        {
            current_number += input[i];
            i++;
        }
        return current_number;
    }

    bool isFunction(const string& input, int& i, vector<string>& tokens, bool& function)
    {
        for (int j = 0; j < 4; j++)
        {
            if (input.substr(i, functions[j].length()) == functions[j])
            {
                tokens.push_back(functions[j]);
                i += functions[j].length();
                function = true;
                return true;
                break;
            }
        }
        return false;
    }

public:
    string getVariableName(const string& input, int& i)
    {
        string variable = "";
        while (i < input.length() && isalnum(input[i]))
        {
            variable += input[i];
            i++;
        }
        return variable;
    }

    const string functions[4] = { "pow", "abs", "min", "max" };

    bool isFunction(const string token)
    {
        return find(begin(functions), end(functions), token) != end(functions);
    }   

    bool isOperator(const char symbol)
    {
        return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '=');
    }

    bool function = false;

    bool validateParentheses(const vector<string>& tokens)
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
            else 
            {
                count++;
            }                 
        }
        if (temp.empty())
        {
            return true;
        }
        return false;
    }

    vector<string> ParseInput(string& input)
    {
        vector<string> tokens;
        int i = 0;
        if (input.substr(0, 3) == "var")
        {
            input.erase(0, 3);         
        }
        while (i < input.length())
        {
            if (isdigit(input[i]) || (input[i] == '-' && (i == 0 || !isdigit(input[i - 1]))))
            {
                string current_number = constructNumber(input, i);
                tokens.push_back(current_number);
            }              
            else if (isalpha(input[i]))
            {
                if (!isFunction(input, i, tokens, function))
                {
                    string variable = getVariableName(input, i);
                    tokens.push_back(variable);
                }
            }
            else
            {
                tokens.push_back(string(1, input[i]));
                i++;
            }
        }
        return tokens;
    }
};

class ReversePolishNotation
{
    map<string, double>& container;
    Tokens tokens;

    bool isDouble(const string token)
    {
        char* end = nullptr;
        (void)strtod(token.c_str(), &end);
        return end != token.c_str() && *end == '\0';
    }

    int Precedence(const string oper)
    {
        if (oper == "-" || oper == "+")
            return 1;
        else if (oper == "*" || oper == "/")
            return 2;
        else if (tokens.isFunction(oper))
            return 3;        
        return 0;
    }

    double applyOperator(const string oper, const double number1, const double number2)
    {
        if (oper == "-")
        {return number2 - number1;}
        else if(oper == "+")
        {return number2 + number1;}
        else if(oper == "*")
        {return number2 * number1;}
        else if(oper == "/")
        {return number2 / number1;}
        else if(oper == "min")
        {return min(number1, number2);}
        else if (oper == "max")
        {return max(number1, number2);}        
        else if (oper == "pow")
        {return pow(number2, number1);}
        else if (oper == "abs")
        {return abs(number1);}
        else
        {
            cout << "Sth went wrong!" << endl;
            return 0 ;
        }
    }

public: 
    ReversePolishNotation(map<string, double>& cont) : container(cont) {}

     bool isInContainer(const string value)
     {
         return  container.find(value) != container.end();
     }

    queue<string> PostfixNotation(const vector<string> tokens)
    {
        stack<string> callStack;
        queue<string> queueOutput;
        for (int i = 0; i < tokens.size(); i++)
        {
            if (isDouble(tokens[i]) || isInContainer(tokens[i]))
            {
                queueOutput.push(tokens[i]);
            }
            else if (tokens[i] == "(")
            {
                callStack.push(tokens[i]);
            }
            else if ((tokens[i] == ")" || tokens[i] == ",") && callStack.size() > 0)
            {
                while (!callStack.empty() && callStack.top() != "(")
                {
                    queueOutput.push(callStack.top());
                    callStack.pop();
                }
                if (tokens[i] == ")")
                {
                    callStack.pop();
                }
            }
            else
            {
               
                 if (callStack.size() > 0 && Precedence(tokens[i]) <= Precedence(callStack.top()))
                    {
                        queueOutput.push(callStack.top());
                        callStack.pop();
                    }
                    callStack.push(tokens[i]);
                
            }
        }
        while (!callStack.empty())
        {
            queueOutput.push(callStack.top());
            callStack.pop();
        }
        return queueOutput;
    }

  double GetNumberFromStack(stack<string>& stackToCalculate)
  {
      double number = stod(stackToCalculate.top());
      stackToCalculate.pop();
      return number;
  }

  void applyOperatorAndPushBack(stack<string>& stackToCalculate, const string token)
  {
      if (token == "abs")
      {
          double number1 = GetNumberFromStack(stackToCalculate);
          string number = to_string(applyOperator(token, number1, 0));
          stackToCalculate.push(number);
      }
      else {
          double number1 = GetNumberFromStack(stackToCalculate);
          double number2 = GetNumberFromStack(stackToCalculate);
          string number = to_string(applyOperator(token, number1, number2));
          stackToCalculate.push(number);
      }
  }

    double Calculate(queue<string>& queueOutput)
    {
        stack<string> stackToCalculate;
        while (!queueOutput.empty() )
        {
            string token = queueOutput.front();
            if (isDouble(token))
            {
                stackToCalculate.push(token);                  
            }
            else if (isInContainer(token))
            {
                stackToCalculate.push(to_string(container.at(token)));                
            }
            else {
                  
                applyOperatorAndPushBack(stackToCalculate, token);
            }   
            queueOutput.pop();
        }
        return stod(stackToCalculate.top());
    }

    double GetResult(const vector<string>& tokens)
    {
        queue<string> postfix = PostfixNotation(tokens);
        return Calculate(postfix);
    }
};

class ResultOnScreen
{    
    map<string, double>& container;
    ReversePolishNotation notation;
    Tokens tokens;
    bool assignment = false;

    bool isAssignment(const string& input, int& i)
    {
        if (input.substr(0, 3) == "var")
        {
            assignment = true;
            i += 3;
            return true;
        }
        return false;
    }

    bool handleOperators(const string& input, int& i, bool assignment, int& countAssignment)
    {
        if (tokens.isOperator(input[i]))
        {
            if ((i == 0 && input[i] != '-') || (i > 0 && !isdigit(input[i - 1]) && input[i - 1] != ')' && input[i] != '-' && input[i] != '=' && !isalnum(input[i - 1])))
            {
                return false;
            }
            else if (input[i] == '=')
            {
                countAssignment++;
                if (!assignment || countAssignment > 1 || i == 0 || tokens.isOperator(input[i - 1]))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isFunction(const string& input, int& i, int& abs, int& functionCount)
    {
        for (int j = 0; j < 4; j++)
        {
            if (input.substr(i, tokens.functions[j].length()) == tokens.functions[j])
            {
                i += tokens.functions[j].length();

                if (tokens.functions[j] == "abs")
                {
                    abs++;
                }
                functionCount++;
                return true;
                break;
            }
        }
        return false;
    }

    bool handleVariables(const string& input, int& i, bool& assignment)
    {
        string variableName = tokens.getVariableName(input, i);
        if (i < input.length())
        {
            if (input.substr(0, 3) != "var" && input[i] == '=' && i < input.size() && notation.isInContainer(variableName))
            {
                assignment = true;
            }
            else if (!notation.isInContainer(variableName) && input.substr(0, 3) != "var")
            {
                return false;
            }
        }
        return true;
    }

    bool isValidSymbol(const string& input, int& i)
    {
        return isdigit(input[i]) || isalpha(input[i]) || tokens.isOperator(input[i]) || input[i] == '(' || input[i] == ')' || input[i] == '.';
    }

public:
    ResultOnScreen(map<string, double>& cont) : container(cont), notation(cont) {}

    bool validateInput(string& input)
    {
        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        if (input.empty())
        {
            return false;
        }
        int countAssignment = 0;
        int commaCount = 0;
        int functionCount = 0;
        int i = 0;
        int abs = 0;       
        assignment = isAssignment(input, i);
        for (; i < input.length(); i++)
        {
            if (!handleOperators(input, i, assignment, countAssignment))
            {
                return false;
            }
            else if (input[i] == ',')
            {
                commaCount++;
            }
            else if ((input[i] == '(' && input[i + 1] == ')') || (input[i] == '(' && input[i + 2] == ')' && input[i + 1] == ','))
            {
                return false;
            }
            else if (isalpha(input[i]))
            {
                if (isFunction(input, i, abs, functionCount))
                {
                    if (input[i] == '(' && input[i + 2] == ')' && input[i + 1] == ',' && i < input.length())
                    {
                        return false;
                    }
                }
                else {
                    if (!handleVariables(input, i, assignment))
                    {
                        return false;
                    }
                    i--;
                }
            }
            else if (!isValidSymbol(input, i)) {
                return false;
            }
        }
        if ((abs > 0 && commaCount != functionCount - abs) || (abs == 0 && commaCount != functionCount)) {
            return false;
        }
        return true;
    }
   
    void TakeUserInput(string& input)
    {
        vector<string> parts = tokens.ParseInput(input);
        if (!tokens.validateParentheses(parts))
        {
            cout << "Invalid input!" << endl;
            return;
        }      
        if (assignment)
        {           
            string variable_name = parts[0];
            parts.erase(parts.begin(), parts.begin() + 2); 
            double var_value = notation.GetResult(parts);
            cout << "Echo: "<< variable_name << " = " << var_value << endl;
            container[variable_name] = var_value;
        }
        else
        {
            cout << "Echo: " << notation.GetResult(parts) << endl;
        }
    }
};

int main()
{
    map<string, double> container;
    while (true)
    {
        string input;
        Tokens tokens;
        cout << ">";
        getline(cin, input);
        if (input == "exit")
        {
            return 0;
        }
        ResultOnScreen result(container);
        while (!result.validateInput(input)) {
            cout << "Invalid input!" << endl;
            cout << ">";
            getline(cin, input);
        }
        result.TakeUserInput(input);
    }
    return 0;
}