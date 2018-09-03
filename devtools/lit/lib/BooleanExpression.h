// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2018 polarphp software foundation
// Copyright (c) 2017 - 2018 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://polarphp.org/LICENSE.txt for license information
// See http://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2018/09/03.

#ifndef POLAR_DEVLTOOLS_LIT_BOOLEAN_EXPRESSION_H
#define POLAR_DEVLTOOLS_LIT_BOOLEAN_EXPRESSION_H

#include <set>
#include <string>
#include <regex>
#include <list>
#include <optional>

namespace polar {
namespace lit {

// A simple evaluator of boolean expressions.
//
// Grammar:
//   expr       :: or_expr
//   or_expr    :: and_expr ('||' and_expr)*
//   and_expr   :: not_expr ('&&' not_expr)*
//   not_expr   :: '!' not_expr
//                 '(' or_expr ')'
//                 identifier
//   identifier :: [-+=._a-zA-Z0-9]+

// Evaluates `string` as a boolean expression.
// Returns True or False. Throws a ValueError on syntax error.
//
// Variables in `variables` are true.
// Substrings of `triple` are true.
// 'true' is true.
// All other identifiers are false.

class BooleanExpression
{
public:
   BooleanExpression(const std::string &str, const std::set<std::list> &variables,
                     const std::string &triple = "")
      : m_variables(variables),
        m_triple (triple),
        m_token(std::nullopt),
        m_value(std::nullopt)
   {
      m_tokens = tokenize(str);
      m_variables.insert("true");
   }

   std::string &quote(std::string &token);
   bool accept(const std::string &token);
   void expect(const std::string &token);
   bool isIdentifier(const std::string &token);
   BooleanExpression &parseNOT(const std::string &token);
   BooleanExpression &parseAND(const std::string &token);
   BooleanExpression &parseOR(const std::string &token);
   std::optional<bool> parseAll();
public:
   static void evaluate(const std::set<std::string> variables, const std::string &triple = "");
   static std::list<std::string> tokenize(const std::string &str);

protected:
   static std::regex sm_pattern;
   std::list<std::string> m_tokens;
   std::set<std::string> m_variables;
   std::string m_triple;
   std::optional<std::string> m_token;
   std::optional<std::string> m_value;
};

} // lit
} // polar

#endif // POLAR_DEVLTOOLS_LIT_BOOLEAN_EXPRESSION_H
