#ifndef LAB_1_STREAMLIB_H
#define LAB_1_STREAMLIB_H

#include "main/stream-dir/core/ReadStreamBuffer.h"
#include "main/stream-dir/core/WriteStreamBuffer.h"
#include "main/stream-dir/core/ReadWriteStreamBuffer.h"
#include "main/stream-dir/core/TextFileReader.h"
#include "main/stream-dir/core/TextFileWriter.h"
#include "main/stream-dir/core/TextFileReaderWriter.h"

#include "main/stream-dir/streams/ReadOnlyStream.h"
#include "main/stream-dir/streams/WriteOnlyStream.h"
#include "main/stream-dir/streams/ReadWriteStream.h"

#include "main/stream-dir/io/file/FileReadStreamBuffer.h"
#include "main/stream-dir/io/file/FileWriteStreamBuffer.h"
#include "main/stream-dir/io/file/FileReadWriteStreamBuffer.h"
#include "main/stream-dir/io/sequence/SequenceReadStreamBuffer.h"
#include "main/stream-dir/io/sequence/SequenceWriteStreamBuffer.h"

#include "main/stream-dir/io/serializers/ByteSerializers.h"

#include "main/spellchecker/RadixTree.h"
#include "main/spellchecker/Trie.h"
#include "main/spellchecker/SpellChecker.h"
#include "main/spellchecker/SpellHelper.h"

#endif // LAB_1_STREAMLIB_H
