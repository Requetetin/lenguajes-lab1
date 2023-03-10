#include "Headers/Cleaner.h"
#include <iostream>

Cleaner::Cleaner() = default;

string Cleaner::cleanString(string regex) {
  regex = Cleaner::removeSpaces(regex);
  regex = Cleaner::shortenUnary(regex);
  regex = Cleaner::replacePlus(regex);
  regex = Cleaner:: replaceQuestion(regex);
  return regex;
}

/**
 * Removes spaces from input string
 */
string Cleaner::removeSpaces(string regex) {
  regex.erase(remove(regex.begin(), regex.end(), ' '), regex.end());
  return regex;
}

/**
 * Makes consecutive unary operators a single one
 */
string Cleaner::shortenUnary(string regex) {
  string finalRegex;
  for (int i = 0; i < regex.length(); i++) {
    if (regex[i] == '*' && regex[i-1] != '*') {
      finalRegex.push_back(regex[i]);
    } else if (regex[i] == '+' && regex[i-1] != '+') {
      finalRegex.push_back(regex[i]);
    } else if (regex[i] == '?' && regex[i-1] != '?') {
      finalRegex.push_back(regex[i]);
    } else if (isalnum(regex[i]) || regex[i] == '(' || regex[i] == ')' || regex[i] == '|') {
      finalRegex.push_back(regex[i]);
    }
  }
  return finalRegex;
}

/**
 * Replaces:
 *     a+
 * With:
 *     aa*
 */
string Cleaner::replacePlus(string regex) {
  while (regex.find('+') != string::npos) {
    int index = regex.find('+');
    if (index == 0) {
      cout << "ERROR! Can't use operator + at the start" << endl;
      exit(-1);
    }
    if (regex.at(index - 1) != ')') {
      char operable = regex.at(index - 1);
      string replacement;
      replacement.push_back(operable);
      replacement.push_back(operable);
      replacement.push_back('*');
      regex.erase(index - 1, 2);
      regex.insert(index - 1, replacement);
    } else {
      string replacement;
      for (int i = index - 1; regex[i] != '('; i--) {
        replacement.push_back(regex[i]);
      }
      replacement.push_back('(');
      reverse(replacement.begin(), replacement.end());
      replacement += '*';
      regex.erase(index, 1);
      regex.insert(index, replacement);
    }
  }
  return regex;
}

/**
 * Replaces:
 *     a?
 * With:
 *     (a|e)
 */
string Cleaner::replaceQuestion(string regex) {
  while (regex.find('?') != string::npos) {
    int index = regex.find('?');
    if (index == 0) {
      cout << "ERROR! Can't use operator ? at the start" << endl;
      exit(-1);
    }
    if (regex.at(index - 1) != ')') {
      char operable = regex.at(index - 1);
      string replacement;
      replacement.push_back('(');
      replacement.push_back(operable);
      replacement.push_back('|');
      replacement.push_back('e');
      replacement.push_back(')');
      regex.erase(index - 1, 2);
      regex.insert(index - 1, replacement);
    } else {
      int startIndex;
      string replacement;
      for (int i = index - 1; regex[i] != '('; i--) {
        replacement.push_back(regex[i]);
        startIndex = i;
      }
      replacement.push_back('(');
      reverse(replacement.begin(), replacement.end());
      replacement = '(' + replacement + '|' + 'e' + ')';
      regex.erase(startIndex-1, index - startIndex + 2);
      regex.insert(startIndex-1, replacement);
    }
  }
  return regex;
}
