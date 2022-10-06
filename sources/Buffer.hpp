#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>
#include <string>
#include <any>

namespace MTLib {
    class Buffer {
        public:
            enum BufferMode {CIRCLE, FIXED, EXTENSIBLE};

            explicit Buffer(size_t size = 1024, BufferMode mode = EXTENSIBLE);
            Buffer(const Buffer &other);
            Buffer &operator=(const Buffer &rhs);
            virtual ~Buffer() = default;

            void write(std::any &data, size_t size);
            void write(const void *data, size_t size);
            void write(const char *c_str, size_t size);
            void write(std::string &str);

            void read(std::any &data, size_t size);
            void read(void *dest, size_t size);
            void read(char *dest, const char *delim);
            void read(char *dest, std::string &delim);
            void read(std::string &dest, const char *delim);
            void read(std::string &dest, std::string &delim);
            uint8_t readByte();

            void unreadBytes(size_t size);
            void unwriteBytes(size_t size);

            BufferMode const getMode() const;
            void setMode(BufferMode const mode);

            std::vector<int8_t> getData() const;
            void swap(Buffer & const rhs);
            void skipBytes(size_t size);

            bool isFull() const ;
            bool isEmpty() const;
            
            size_t getSize() const;
            size_t getUsedSize() const;
            size_t getFreeSize() const;
            size_t getReadableSize() const;

        private:
            std::vector<int8_t> _data;
            size_t _size;
            size_t _bufferedBytes;
            size_t _writter;
            size_t _reader;
            BufferMode _mode;
    };
}

#endif
