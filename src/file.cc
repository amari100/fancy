#include "includes.h"

namespace fancy {

  File::File(const string &filename, Array_p modes) :
    FancyObject(FileClass),
    _filename(filename),
    _modes(modes)
  {
    init_openmode(modes);
  }

  File::~File()
  {
  }

  FancyObject_p File::equal(const FancyObject_p other) const
  {
    if(IS_FILE(other)) {
      File_p other_file = dynamic_cast<File_p>(other);
      if(_filename == other_file->_filename
         && _openmode == other_file->_openmode)
        return t;
    }
    return nil;
  }

  EXP_TYPE File::type() const
  {
    return EXP_FILE;
  }

  string File::to_s() const
  {
    return "<File:" + _filename + ">";; // + " [" + _mode + "]>";
  }

  string File::filename() const
  {
    return _filename;
  }

  Array_p File::modes() const
  {
    return _modes;
  }

  ios_base::openmode File::openmode() const
  {
    return _openmode;
  }

  fstream& File::file()
  {
    return _file;
  }

  void File::open()
  {
    _file.open(_filename.c_str(), _openmode);
  }

  bool File::is_open()
  {
    return _file.is_open();
  }

  bool File::eof()
  {
    return _file.eof();
  }

  void File::close()
  {
    _file.close();
  }

  bool File::good() const
  {
    return _file.good();
  }

  void File::init_openmode(Array_p modes)
  {
    for(unsigned int i = 0; i < modes->size(); i++) {
      if(IS_SYMBOL(modes->at(i))) {
        Symbol_p sym = dynamic_cast<Symbol_p>(modes->at(i));
        // check different cases
        if(sym == Symbol::from_string(":append")) {
          _openmode = _openmode | fstream::app;
        }
        if(sym == Symbol::from_string(":read")) {
          _openmode = _openmode | fstream::in;
        }
        if(sym == Symbol::from_string(":write")) {
          _openmode = _openmode | fstream::out;
        }
        if(sym == Symbol::from_string(":binary")) {
          _openmode = _openmode | fstream::binary;
        }
        if(sym == Symbol::from_string(":at_end")) {
          _openmode = _openmode | fstream::ate;
        }
        if(sym == Symbol::from_string(":truncate")) {
          _openmode = _openmode | fstream::trunc;
        }
      }
    }
  }

}
