#include "filesystem.h"
#include "logger/log.h"

namespace Phs
{

static constexpr bool PhsFileSUCCESS = 1;
static constexpr bool PhsFileFAILURE = 0;

template <StreamDirection StreamDirection>
File<StreamDirection>::File()
   : _path(UndefFilePath)
   , _mode(FILE_MODE_UNDEF)
   , _opened(false)
   , _inmode(false)
   , _outmode(false)
   , _byte_size(_UndefSize)
{}

template <StreamDirection StreamDirection>
File<StreamDirection>::File(std::string_view path, FileOpenMode mode)
{
   open(path, mode);
}

template <StreamDirection StreamDirection>
File<StreamDirection>::~File()
{
   close();
}

template <StreamDirection StreamDirection>
bool File<StreamDirection>::open(const std::string_view path, FileOpenMode mode)
{
   PHS_ASSERT_LOG(!_opened, "Opening already opened file");

   if ((StreamDirection == STREAM_IN and mode & FILE_MODE_OUT) or
       (StreamDirection == STREAM_OUT and mode & FILE_MODE_IN))
   {
      PHS_CORE_LOG_ERROR("Invalid mode mask");
      return PhsFileFAILURE;
   }

   // automatically adds missing states
   if constexpr (StreamDirection == STREAM_IN)
      mode |= FILE_MODE_IN;
   if constexpr (StreamDirection == STREAM_OUT)
      mode |= FILE_MODE_OUT;

   _path = path;
   _mode = mode;

   const char* cpath = _path.c_str();

   _stream.open(cpath, _mode);

   if (!_stream)
   {
      PHS_CORE_LOG_ERROR("Failed to open a file: {}", _path);
      close();
      return PhsFileFAILURE;
   }

   _byte_size = byteSize();
   _opened = true;
   return PhsFileSUCCESS;
}

template <StreamDirection StreamDirection>
bool File<StreamDirection>::reopen(const std::string_view path, FileOpenMode mode)
{
   PHS_ASSERT_LOG(_opened, "Reopening closed file");
   close();
   return open(path, mode);
}

template <StreamDirection StreamDirection>
bool File<StreamDirection>::close()
{
   PHS_ASSERT_LOG(_opened, "Closing already closed file");
   _stream.close();
   _path = UndefFilePath;
   _mode = FILE_MODE_UNDEF;
   _byte_size = _UndefSize;
   _opened = false;
   return PhsFileSUCCESS;
}

template <StreamDirection StreamDirection>
PHS_INLINE bool File<StreamDirection>::isOpen() const
{
   return _opened;
}

template <StreamDirection StreamDirection>
bool File<StreamDirection>::write(const FileToken* content, size_t size)
{
   PHS_STATIC_ASSERT(StreamDirection != STREAM_OUT);

   if (!_stream.write(reinterpret_cast<char*>(content), size))
      return PhsFileFAILURE;

   return PhsFileSUCCESS;
}

template <StreamDirection StreamDirection>
bool File<StreamDirection>::read(std::unique_ptr<FileToken>& out, size_t& size)
{
   PHS_STATIC_ASSERT(StreamDirection != STREAM_IN);
   PHS_ASSERT(_byte_size != _UndefSize);

   byte* buffer = reinterpret_cast<byte*>(std::malloc(_byte_size));

   if (!buffer)
      return PhsFileFAILURE;

   if (!_stream.read(reinterpret_cast<char*>(buffer), _byte_size))
   {
      std::free(buffer);
      return PhsFileFAILURE;
   }

   out.reset(buffer);
   size = _byte_size;

   return PhsFileSUCCESS;
}

template <StreamDirection StreamDirection>
PHS_INLINE size_t File<StreamDirection>::byteSize()
{
   PHS_ASSERT(_path != UndefFilePath);

   std::streamsize prev = _stream.tellg();
   _stream.clear();

   _stream.seekg(0, std::ios_base::end);
   std::streamsize size = _stream.tellg();

   _stream.seekg(prev);
   return static_cast<size_t>(size);
}

} // namespace Phs
