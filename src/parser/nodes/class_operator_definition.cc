#include "../../../vendor/gc/include/gc.h"
#include "../../../vendor/gc/include/gc_cpp.h"
#include "../../../vendor/gc/include/gc_allocator.h"

#include "class_operator_definition.h"
#include "../../bootstrap/core_classes.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      ClassOperatorDefExpr::ClassOperatorDefExpr(Identifier* class_name, Identifier* op_name, Method* method) :
        _class_name(class_name),
        _op_name(op_name),
        _method(method)
      {
      }

      FancyObject* ClassOperatorDefExpr::eval(Scope *scope)
      {
        _class_name->eval(scope)->def_singleton_method(_op_name->name(), _method);
        return _method;
      }


      /**
       * PrivateClassOperatorDefExpr
       */

      PrivateClassOperatorDefExpr::PrivateClassOperatorDefExpr(Identifier* class_name, Identifier* op_name, Method* method) :
        ClassOperatorDefExpr(class_name, op_name, method)
      {
      }

      FancyObject* PrivateClassOperatorDefExpr::eval(Scope *scope)
      {
        _class_name->eval(scope)->def_private_singleton_method(_op_name->name(), _method);
        return _method;
      }


      /**
       * ProtectedClassOperatorDefExpr
       */

      ProtectedClassOperatorDefExpr::ProtectedClassOperatorDefExpr(Identifier* class_name, Identifier* op_name, Method* method) :
        ClassOperatorDefExpr(class_name, op_name, method)
      {
      }

      FancyObject* ProtectedClassOperatorDefExpr::eval(Scope *scope)
      {
        _class_name->eval(scope)->def_protected_singleton_method(_op_name->name(), _method);
        return _method;
      }

    }
  }
}
