#pragma once

#include "common.h"
#include "precompile.h"
#include "filepath.h"
#include <fstream>

namespace Phs
{

enum FileOpenMode
{
   FILE_MODE_UNDEF    = 0,
   FILE_MODE_NONE     = 0,
   FILE_MODE_APPEND   = std::ios::app,
   FILE_MODE_BINARY   = std::ios::binary,
   FILE_MODE_IN       = std::ios::in,
   FILE_MODE_OUT      = std::ios::out,
   FILE_MODE_TRUNC    = std::ios::trunc,
   FILE_MODE_SEEK_END = std::ios::ate,
};

constexpr PHS_INLINE FileOpenMode operator|(FileOpenMode mode0, FileOpenMode mode1) PHS_NOEXCEPT
{ 
   return static_cast<FileOpenMode>(static_cast<int>(mode0) | static_cast<int>(mode1));
}

constexpr PHS_INLINE FileOpenMode& operator|=(FileOpenMode& mode0, FileOpenMode mode1) PHS_NOEXCEPT
{
   mode0 = mode0 | mode1;
   return mode0;
}

enum StreamDirection
{
   STREAM_IN     = 1,
   STREAM_OUT    = 2,
   STREAM_IN_OUT = STREAM_IN | STREAM_OUT,
};

/* __Stream struct template specifies a type of a standard stream.
*  Can be:
*  - std::ofstream while Mode template parameter is STREAM_IN
*  - std::ifstream while Mode is STREAM_OUT
*  - std::fstream while Mode is STREAM_IN_OUT
*/

template <StreamDirection Mode>
struct __FileStream;

/* STREAM_IN template parameter means output file
*/
template <>
struct __FileStream<STREAM_IN>
{
   using type = std::ofstream;
};

/* STREAM_OUT template parameter means input file
*/
template <>
struct __FileStream<STREAM_OUT>
{
   using type = std::ifstream;
};

/* STREAM_IN_OUT combines STREAM_IN and STREAM_OUT
*/
template <>
struct __FileStream<STREAM_IN_OUT>
{
   using type = std::fstream;
};

using FileToken = byte;

/* Main file representation class.
*  File can be readable, writable or both.
*/
template <StreamDirection StreamDirection>
class File
{
public:
   File();
   File(const FilePath& path, FileOpenMode mode = FILE_MODE_NONE);
   ~File();

   bool              open(const FilePath& path, FileOpenMode mode = FILE_MODE_NONE);
   bool              reopen(const FilePath& path, FileOpenMode mode = FILE_MODE_NONE);
   bool              close();

   PHS_INLINE bool   isOpen() const;

   bool              write(const FileToken* content, size_t size);
   bool              read(std::unique_ptr<FileToken>& out, size_t& size);
private:
   PHS_INLINE size_t byteSize();

   using _Stream = typename __FileStream<StreamDirection>::type;

   static constexpr size_t           _UndefSize = 0;
   FilePath                          _path;
   FileOpenMode                      _mode;
   bool                              _opened;
   _Stream                           _stream;
   size_t                            _byte_size;
};

/* Handy aliases masking implementation details of File class.
*/
using File_Write     = File<STREAM_IN>;
using File_Read      = File<STREAM_OUT>;
using File_WriteRead = File<STREAM_IN_OUT>;

} // namespace Phs

#include "filesystem.inl"
