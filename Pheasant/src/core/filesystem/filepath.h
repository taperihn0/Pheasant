#pragma once

#include "common.h"
#include <filesystem>

namespace Phs
{

/* FilePath class wraps std::string and implement 
*  some additional methods that are helpful 
*  while manipulating OS paths and directories.
*/
class FilePath
{
public:
   friend std::ostream& operator<<(std::ostream&, const FilePath&);

   FilePath();
   FilePath(const std::string& s);
   FilePath(const char* s);

   FilePath(const FilePath& fp);
   FilePath(FilePath&& fp);

   FilePath&          operator=(const FilePath& fp);
   FilePath&          operator=(FilePath&& fp);

   bool               operator==(const FilePath& fp) const;
   bool               operator!=(const FilePath& fp) const;

   std::string&       toStr();
   const std::string& toStr() const;

   const char*        toCStr() const;

   FilePath           stepInto(const std::string& s) const;
   FilePath           stepInto(const char* s) const;

   // TODO: implement optionally stepBack functionality

   static FilePath    getCurrentDirectory();
   static void        setCurrentDirectory(const FilePath& dir);
private:
   std::string        _path_str;

   static bool        _cached_flag;
   static std::string _cached_dir;
};

std::ostream& operator<<(std::ostream& out, const FilePath& fp);

extern FilePath UndefFilePath;

} // namespace Phs
