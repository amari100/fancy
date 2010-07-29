#include "../vendor/gc/include/gc.h"
#include "../vendor/gc/include/gc_cpp.h"
#include "../vendor/gc/include/gc_allocator.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

#include<sys/stat.h>
#include<sys/types.h>

#include "array.h"
#include "string.h"
#include "fancy_exception.h"
#include "number.h"
#include "errors.h"
#include "utils.h"
#include "parser/parser.h"
#include "bootstrap/includes.h"
#include "bootstrap/core_classes.h"

using namespace std;
using namespace fancy;

extern int yyparse();
extern void yyrestart(FILE*);

string get_load_path(int argc, char **argv)
{
  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-I") == 0) {
      return string(argv[i+1]);
    }
  }
  return "."; // current dir
}

void prepare_argv(int argc, char **argv)
{
  // set command line arguments in global ARGV variable as Array
  Array* args_arr = new Array();
  for(int i = 1; i < argc; i++) {
    string arg(argv[i]);
    // skip -I + root loadpath arg
    if(arg == "-I") {
      i++;
      continue;
    }
    args_arr->insert(FancyString::from_value(arg));
  }
  global_scope->define("ARGV", args_arr);
}

vector<string> filenames(int argc, char **argv)
{
  vector<string> filenames;
  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      i++;
      continue;
    }
    filenames.push_back(string(argv[i]));
  }
  return filenames;
}

int main(int argc, char **argv)
{
  GC_INIT();

  fancy::parser::load_path.push_back(get_load_path(argc, argv));
  fancy::bootstrap::init_core_classes();
  fancy::bootstrap::init_global_objects();
  fancy::bootstrap::init_global_scope();
  fancy::Number::init_cache();

  string boot_file = "boot.fnc";
  string stdlib_path = get_load_path(argc, argv) + "/lib";
  fancy::parser::load_path.push_back(stdlib_path);

  prepare_argv(argc, argv);
  // now, load boot.fnc
  fancy::parser::parse_file(boot_file);

  try {
    vector<string> files = filenames(argc, argv);
    if(files.size() > 0) {
      for(unsigned int i = 0; i < files.size(); i++) {
        fancy::parser::parse_file(files[i]);
      }
    } else {
      parser::parse_stdin();
    }
  } catch(UnknownIdentifierError &ex) {
    cout << "Error:" << endl;
  }

  // cout << "heap size: " << GC_get_bytes_since_gc() << endl;
  // GC_gcollect();
  // cout << "heap size after collect: " << GC_get_bytes_since_gc() << endl;
  // cout << "Completed " << GC_gc_no << " collections" <<endl;
  // cout << "Heap size is " << GC_get_heap_size() << endl;

  return 0;
}

