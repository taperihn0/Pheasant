#include "filepath.h"

namespace Phs 
{

#ifdef PHEASANT_PLATFORM_WINDOWS
#  define PHS_SYSTEM_PATH_SEPARATOR '\\'
#else
#  define PHS_SYSTEM_PATH_SEPARATOR '/'
#endif

bool        FilePath::_cached_flag = false;
std::string FilePath::_cached_dir;

FilePath::FilePath()
   : _path_str("")
{}

FilePath::FilePath(const std::string& s)
   : _path_str(s)
{}

FilePath::FilePath(const char* s)
   : _path_str(s)
{}

FilePath::FilePath(const FilePath& fp)
   : _path_str(fp._path_str)
{}

FilePath::FilePath(FilePath&& fp)
   : _path_str(std::move(fp._path_str))
{}

FilePath& FilePath::operator=(const FilePath& fp)
{
   _path_str = fp._path_str;
   return *this;
}

FilePath& FilePath::operator=(FilePath&& fp)
{
   _path_str = std::move(fp._path_str);
   return *this;
}

bool FilePath::operator==(const FilePath& fp) const
{
   return _path_str == fp._path_str;
}

bool FilePath::operator!=(const FilePath& fp) const
{
   return !(*this == fp);
}

std::string& FilePath::toStr()
{
   return _path_str;
}

const std::string& FilePath::toStr() const
{
   return _path_str;
}

const char* FilePath::toCStr() const
{
   return _path_str.c_str();
}

FilePath FilePath::stepInto(const std::string& s) const
{
   FilePath res(_path_str);
   res.toStr().append(1, PHS_SYSTEM_PATH_SEPARATOR);
   res.toStr().append(s);
   return res;
}

FilePath FilePath::stepInto(const char* s) const
{
   const std::string tmp = s;
   return stepInto(tmp);
}

FilePath FilePath::operator/(const FilePath& fp) const {
   return this->stepInto(fp.toStr());
}

FilePath FilePath::getCurrentDirectory()
{
   if (!_cached_flag)
   {
      _cached_dir = std::filesystem::current_path().string();
      _cached_flag = true;
   }

   return static_cast<FilePath>(_cached_dir);
}

void FilePath::setCurrentDirectory(const FilePath& dir)
{
   PHS_ASSERT(!dir.toStr().empty());
   PHS_ASSERT(dir != UndefFilePath);

   std::filesystem::current_path(dir.toStr());

   _cached_dir = dir.toStr();
   _cached_flag = true;
}

bool FilePath::isValid() const 
{
   return _path_str != UndefFilePath._path_str;
}

std::ostream& operator<<(std::ostream& out, const FilePath& fp)
{
   return out << fp._path_str;
}

} // namespace Phs