#include "includes.h"

namespace fancy {

  Symbol::Symbol(const string &name) :
    FancyObject(SymbolClass), _name(name)
  {
  }

  Symbol::~Symbol()
  {
  }

  FancyObject_p Symbol::equal(const FancyObject_p other) const
  {
    if(!IS_SYMBOL(other)) {
      return nil;
    }
  
    Symbol_p other_sym = dynamic_cast<Symbol_p>(other);
    if(other_sym) {
      if(_name == other_sym->_name) {
        return t;
      }
    }
    return nil;
  }

  EXP_TYPE Symbol::type() const
  {
    return EXP_SYMBOL;
  }

  string Symbol::to_s() const
  {
    return _name.substr(1, _name.size() - 1);
  }

  string Symbol::inspect() const
  {
    return _name;
  }

  string Symbol::name() const
  {
    return _name;
  }

  map<string, Symbol_p> Symbol::sym_cache;
  Symbol_p Symbol::from_string(const string &name)
  {
    if(sym_cache.find(name) != sym_cache.end()) {
      return sym_cache[name];
    } else {
      // insert new name into sym_cache & return new number name
      Symbol_p new_sym = new Symbol(name);
      sym_cache[name] = new_sym;
      return new_sym;
    }
  }

}
