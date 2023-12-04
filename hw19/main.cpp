#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>

/* TEST CASES
((7 + 3) * (5 - 2)) / (4 + 1)
(3.5 + 4.5) * 2 - 3 / (1 + 1)
10 - 3 * (2 + 3) + 4 / (2 / (1 + 1))
(5 + 3) * 2 + (4 / 2 - 1) * (2 + 2)
2 + 3 * 4 - 5 / (1 + 1) * (4 - 3)
((2 + 3) / 4) * (6 - (2 + 1))
((8 * 4) + (2 / (1 + 1))) - (3 * 2 + 1)
(9 + 3) * (7 - 4) + 10 / (5 - 2)
*/

using namespace std;

bool valid_expression(const string& input) {

    for (char c: input) {
        /*
         * Allowed symbols: 0-9 () + - * / . [space]
         * Forbidden symbol: ,
         */

        if (((c < 40 || c > 57) || (c == 44)) && (c != 32)) {
            return false;
        }
    }

    return true;
}

string clean(string input) {
    // Delete [space] symbols
    for (size_t i = 0; i < input.length(); i++) {
        if ((int) input[i] == 32) {
            input.erase(i--, 1);
        }
    }

    // If the first number is negative, add 0
    if (input[0] == '-') {
        input.insert(0, 1, '0');
    }

    return input;
}

int get_priority(string op) {
    // To make sure that '*' and '/' has higher priority than '-' and '+'
    if (op == "+" || op == "-") {
        return 1;
    } else if (op == "*" || op == "/") {
        return 2;
    }
    return 0;
}

queue<string> shunting_yard(string s) {
    /*
     * Shunting yard algorithm is used to turn expression into reverse polish
     * notation a.k.a. postfix notation in form of a queue
     *
     * @param string - this is cleared input from user
     * @return output - this queue holds all tokens - operands & operators in
     * correct order of RPN
     *
     */

    queue<string> output;
    stack<string> operators;

    string current_number = "";
    for (char ch: s) {
        if (isdigit(ch) || ch == '.') {
            current_number += ch;
        } else {
            // Push a number to the output queue
            if (!current_number.empty()) {
                output.push(current_number);
                current_number.clear();
            }
            // If a token is a ( just push it to operators
            if (ch == '(') {
                operators.push({ch});

            }
                // If a token is an operator push it according to priority
            else if (ch != ')') {
                while (!operators.empty() &&
                       get_priority({ch}) <= get_priority(operators.top())) {
                    output.push(operators.top());
                    operators.pop();
                }
                operators.push({ch});
            }
                // Token is a ) pop all the operators until ( is found
            else {
                while (!operators.empty() && operators.top() != "(") {
                    output.push(operators.top());
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == "(") {
                    operators.pop();
                }
            }
        }
    }

    // If there is a number left in stack, push it
    if (!current_number.empty()) {
        output.push(current_number);
    }

    // If there is an operator left in stack, push it
    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    return output;
}

bool is_float(string s) {
    // This string must be a valid float, result is false otherwise
    for (char ch: s) {
        if ((ch < '0' || ch > '9') && (ch != '.'))
            return false;
    }
    return true;
}

float evaluate_RPN(queue<string> rpn) {
    // Calculate expression in form of Reversed Polish notation (RPN)
    stack<float> tokens;
    unordered_map<string, function<void(float &, float &, float &)>> operators =
            {{"+", [](float &a, float &b, float &result) { result = b + a; }},
             {"-", [](float &a, float &b, float &result) { result = b - a; }},
             {"*", [](float &a, float &b, float &result) { result = b * a; }},
             {"/", [](float &a, float &b, float &result) { result = b / a; }}};
    while (!rpn.empty()) {
        string token = rpn.front();
        rpn.pop();

        if (is_float(token)) {
            tokens.push(stof(token));
        } else {
            float a = tokens.top();
            tokens.pop();
            float b = tokens.top();
            tokens.pop();
            float result;
            operators[token](a, b, result);
            tokens.push(result);
        }
    }

    return tokens.top();
}

int main() {

    string input;

    // Get input
    cout << "Input arithmetic equation: ";
    getline(cin, input);

    // Validate & clean input
    if (!valid_expression(input)) {
        cout << "\n [ERROR] Your equation has forbidden symbols! " << endl;
        return 0;
    }

    input = clean(input);
//    cout << "Cleaned expression: " << input << endl;

    // Run shunting yard to get reverse polish notation
    queue<string> RPN = shunting_yard(input);

    queue<string> RPN_copy = RPN;

    // Display rpn
    cout << "Reverse polish notation: ";
    while (!RPN_copy.empty()) {
        cout << RPN_copy.front();
        RPN_copy.pop();
    }
    cout << endl;

    // Calculation
    cout << "Result: " << input << " = " << evaluate_RPN(RPN) << endl;

    return 0;
}