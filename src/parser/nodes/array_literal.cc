#include "includes.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      ArrayLiteral::ArrayLiteral(expression_node *expr_list)
      {
        for(expression_node *tmp = expr_list; tmp != NULL; tmp = tmp->next) {
          _expressions.push_back(tmp->expression);
        }
      }

      ArrayLiteral::~ArrayLiteral()
      {
      }

      FancyObject_p ArrayLiteral::eval(Scope *scope)
      {
        vector<FancyObject_p> values;
        for(list<Expression_p>::iterator it = _expressions.begin();
            it != _expressions.end();
            it++) {
          values.push_back((*it)->eval(scope));
        }
        return new Array(values);
      }

      EXP_TYPE ArrayLiteral::type() const
      {
        return EXP_ARRAYLITERAL;
      }

    }
  }
}
