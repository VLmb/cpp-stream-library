cmake_minimum_required(VERSION 4.0)
project(lab_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_1 main.cpp
        src/main/stream-dir/utils/FileBuffer.cpp
        src/main/stream-dir/utils/FileBuffer.h
        src/main/stream-dir/core/ReadStreamBuffer.h
        src/main/stream-dir/io/file/FileReadStreamBuffer.h
        src/main/stream-dir/core/WriteStreamBuffer.h
        src/main/stream-dir/core/ReadWriteStreamBuffer.h
        src/main/stream-dir/io/file/FileWriteStreamBuffer.h
        src/main/stream-dir/io/file/FileReadWriteStreamBuffer.h
        src/main/stream-dir/io/serializers/ByteSerializers.h
        src/main/stream-dir/io/sequence/SequenceReadStreamBuffer.h
        src/main/stream-dir/io/sequence/SequenceWriteStreamBuffer.h
        src/main/stream-dir/streams/ReadOnlyStream.h
        src/main/stream-dir/streams/WriteOnlyStream.h
        src/main/stream-dir/streams/ReadWriteStream.h
        src/test/main/TestHelper.h
        src/test/main/ReadOnlyStreamTest.h
        src/test/main/WriteOnlyStreamTest.h
        src/test/main/TmpFile.cpp
        src/test/main/TmpFile.h
        src/main/stream-dir/core/TextFileReader.h
        src/main/stream-dir/core/TextFileReaderWriter.h
        src/main/stream-dir/core/TextFileWriter.h
        src/main/spellchecker/RadixTree.h
        src/main/spellchecker/SpellChecker.h
        src/StreamLib.h
        src/main/spellchecker/SpellHelper.h
        src/main/spellchecker/Trie.h
)
