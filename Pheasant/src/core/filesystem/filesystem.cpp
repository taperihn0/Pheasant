#include "filesystem.h"
#include "logger/log.h"

namespace Phs
{

static constexpr bool PhsFileSUCCESS = 1;
static constexpr bool PhsFileFAILURE = 0;

File::File()
   : _path(_UndefFilePath)
   , _mode(FILE_MODE_UNDEF)
   , _opened(false)
   , _inmode(false)
   , _outmode(false)
   , _byte_size(_UndefSize)
{}

File::File(FilePathString path, FileOpenMode mode)
{
   open(path, mode);
}

File::~File()
{
   close();
}

bool File::open(const FilePathString path, FileOpenMode mode)
{
   PHS_ASSERT_LOG(!_opened, "Opening already opened file");
   PHS_ASSERT_LOG(_mode & FILE_MODE_IN and _mode & FILE_MODE_OUT, "In-Out file handling is not implemented");
   PHS_ASSERT(_inmode ^ _outmode);

   _path = path;
   _mode = mode;
   _inmode = _mode & FILE_MODE_IN;
   _outmode = _mode & FILE_MODE_OUT;

   const char* cpath = _path.c_str();

   if (_inmode)
   {
      _inbuf.open(cpath, _mode);

      if (!_inbuf)
      {
         PHS_CORE_LOG_ERROR("Failed to open a file: {}", _path);
         close();
         return PhsFileFAILURE;
      }

      _byte_size = byteSize();
   }
   if (_outmode)
   {
      _outbuf.open(cpath, _mode);

      if (!_outbuf)
      {
         PHS_CORE_LOG_ERROR("Failed to open a file: {}", _path);
         close();
         return PhsFileFAILURE;
      }
   }

   _opened = true;
   return PhsFileSUCCESS;
}

bool File::reopen(const FilePathString path, FileOpenMode mode)
{
   PHS_ASSERT_LOG(_opened, "Reopening closed file");
   close();
   return open(path, mode);
}

bool File::close()
{
   PHS_ASSERT_LOG(_opened, "Closing already closed file");
   _inbuf.close();
   _outbuf.close();
   _path = _UndefFilePath;
   _mode = FILE_MODE_UNDEF;
   _inmode = false;
   _outmode = false;
   _byte_size = _UndefSize;
   _opened = false;
   return PhsFileSUCCESS;
}

bool File::isOpen() const
{
   return _opened;
}

bool File::isClose() const
{
   return !isOpen();
}

bool File::writeLine(const FileToken* content)
{
   PHS_ASSERT(_outmode);
   return PhsFileFAILURE;
}

bool File::readLine(const FileToken* content)
{
   PHS_ASSERT(_inmode);
   return PhsFileFAILURE;
}

bool File::write(const FileToken* content)
{
   PHS_ASSERT(_outmode);
   return PhsFileFAILURE;
}

bool File::read(std::unique_ptr<FileToken>& out, size_t& size)
{
   PHS_ASSERT(_inmode);
   PHS_ASSERT(_byte_size != _UndefSize);

   byte* buffer = new byte[_byte_size];

   if (!buffer)
      return PhsFileFAILURE;
   if (!_inbuf.read(reinterpret_cast<char*>(buffer), _byte_size))
      return PhsFileFAILURE;

   out.reset(buffer);
   size = _byte_size;
   return PhsFileSUCCESS;
}

PHS_INLINE size_t File::byteSize()
{
   PHS_ASSERT(_inmode);
   PHS_ASSERT(_path != _UndefFilePath);
   
   std::streamsize prev = 0;
   std::streamsize size = 0;

   prev = _inbuf.tellg();
   _inbuf.seekg(0, std::ios_base::end);
   size = _inbuf.tellg();
   _inbuf.seekg(prev);

   return static_cast<size_t>(size);
}

} // namespace Phs
