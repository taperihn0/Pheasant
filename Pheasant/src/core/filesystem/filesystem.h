#pragma once

#include "common.h"
#include "precompile.h"
#include <fstream>

namespace Phs
{

enum FileOpenMode
{
   FILE_MODE_UNDEF    = 0,
   FILE_MODE_APPEND   = std::ios::app,
   FILE_MODE_BINARY   = std::ios::binary,
   FILE_MODE_IN       = std::ios::in,
   FILE_MODE_OUT      = std::ios::out,
   FILE_MODE_TRUNC    = std::ios::trunc,
   FILE_MODE_SEEK_END = std::ios::ate,
};

using FileToken = byte;
using FilePathString = std::string_view;

class File
{
public:
   File();
   File(FilePathString path, FileOpenMode mode);
   ~File();

   bool open(const FilePathString path, FileOpenMode mode);
   bool reopen(const FilePathString paht, FileOpenMode mode);
   bool close();

   bool isOpen() const;
   bool isClose() const;

   bool writeLine(const FileToken* content);
   bool readLine(const FileToken* content);

   bool write(const FileToken* content);
   bool read(std::unique_ptr<FileToken>& out, size_t& size);
private:
   PHS_INLINE size_t byteSize();

   using _OwnFilePathString = std::string;

   static constexpr FilePathString _UndefFilePath = "";
   static constexpr size_t         _UndefSize = 0;

   _OwnFilePathString              _path;
   FileOpenMode                    _mode;
   bool                            _opened;

   std::ifstream                   _inbuf;
   std::ofstream                   _outbuf;
   bool                            _inmode;
   bool                            _outmode;
   size_t                          _byte_size;
};

} // namespace Phs
