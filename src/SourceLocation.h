#ifndef SOURCELOCATION_H_
#define SOURCELOCATION_H_
#include <clang-c/Index.h>
#include <string>

namespace clangmm {
  class Offset {
  public:
    bool operator==(const Offset &o) const {return line==o.line && index==o.index;}
    bool operator!=(const Offset &o) const {return !(*this==o);}
    bool operator<(const Offset &o) const {return line<o.line || (line==o.line && index<o.index);}
    unsigned line;
    unsigned index; //byte index in line (not char number)
  };
  
  class SourceLocation {
    friend class TranslationUnit;
    SourceLocation(CXTranslationUnit &tu, const std::string &filepath, unsigned offset);
    SourceLocation(CXTranslationUnit &tu, const std::string &filepath, unsigned line, unsigned column);
  public:
    SourceLocation(const CXSourceLocation& cx_location) : cx_location(cx_location) {}

  public:
    std::string get_path();
    clangmm::Offset get_offset();

    CXSourceLocation cx_location;
    
  private:
    void get_data(std::string *path, unsigned *line, unsigned *column, unsigned *offset);
  };

}  // namespace clangmm
#endif  // SOURCELOCATION_H_
