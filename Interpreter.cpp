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
public:
    const string functions[4] = { "pow", "abs", "min", "max" };
    bool isFunction(string token)
    {
        return find(begin(functions), end(functions), token) != end(functions);
    }   
    bool isOperator(char symbol)
    {
        return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '=');
    }
    bool function = false;

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
            int countAssignment = 0;
            if (input.substr(0, 3) == "var")
            {
                input.erase(0, 3);         
            }
            while (i < input.length())
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
                            function = true;
                            break;
                        }
                    }
                    if (!isFunction)
                    {
                        string variable = "";
                        while (i < input.length() && (isalpha(input[i]) || isdigit(input[i])))
                        {
                            variable += input[i];
                            i++;
                        }
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
    bool isDouble(string token)
    {
        char* end = nullptr;
        (void)strtod(token.c_str(), &end);
        return end != token.c_str() && *end == '\0';
    }

    int Precedence(string oper)
    {
        if (oper == "-" || oper == "+")
            return 1;
        else if (oper == "*" || oper == "/")
            return 2;
        else if (tokens.isFunction(oper))
            return 3;        
        return 0;
    }
    double applyOperator(string oper, double number1, double number2)
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


     bool isInContainer(string value)
     {
         return  container.find(value) != container.end();
     }

    queue<string> PostfixNotation(vector<string> tokens)
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

  void applyOperatorAndPushBack(stack<string>& stackToCalculate, string token)
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

      double GetResult(vector<string>& tokens)
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

public:
    ResultOnScreen(map<string, double>& cont) : container(cont), notation(cont) {}


    bool validateInput(string& input)
    {
        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        int countAssignment = 0;
        int commaCount = 0;
        int functionCount = 0;
        int i = 0;
        int abs = 0;
        if (input.empty())
        {
            return false;
        }
        if (input.substr(0, 3) == "var")
        {
            assignment = true;
            i += 3;
        }       
        for (i ; i < input.length(); i++)
        {
             if (tokens.isOperator(input[i]))
            {
                 if ((i == 0 && input[i] != '-') || (i < input.length() && !isdigit(input[i - 1]) && input[i - 1] != ')' && input[i] != '-' && input[i] != '=' && !isalnum(input[i - 1])))
                {
                    return false;
                }
                else if (input[i] == '=')
                {              
                    countAssignment++;
                    if (!assignment || countAssignment > 1 || i == 0 || tokens.isOperator(input[i - 1]) )
                    {
                        return false;
                    }
                }
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
                bool isFunction = false;
                for (int j = 0; j < 4; j++)
                {
                    if (input.substr(i, tokens.functions[j].length()) == tokens.functions[j])
                    {
                        i += tokens.functions[j].length();
                        isFunction = true;
                        if (tokens.functions[j] == "abs")
                        {
                            abs++;
                        }
                        functionCount++;
                    }
                }
                if (isFunction)
                {
                    if (input[i] == '(' && input[i+2] == ')' && input[i+1] == ',' && i < input.length())
                    {
                        return false;
                    }
                }
                if (!isFunction) {
                    string variableName;
                    while (i < input.length() && isalpha(input[i])) {
                        variableName += input[i];
                        i++;
                    }
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
                    i--; 
                }               
            }            
            else if(!isdigit(input[i]) && !isalpha(input[i]) && !tokens.isOperator(input[i]) && input[i]!='(' && input[i] != ')' && input[i] != '.') {
                 return false;
             }
        }
        if (abs > 0)
        {
            if (commaCount != functionCount - abs)
            {
                return false;
            }
        }
        else{
            if (commaCount != functionCount)
            {
                return false;
            }
        }
        
        return true;
    }
   
    void showContentsOfContainer()
    {
        map<string, double>::iterator it = container.begin();
        while (it != container.end())
        {
            cout << "Key: " << it->first
                << ", Value: " << it->second << endl;
            ++it;
        }
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
        //showContentsOfContainer();
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