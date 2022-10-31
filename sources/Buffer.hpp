#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>
#include <string>
#include <any>
#include <array>
#include <algorithm>

namespace buf
{
    template <typename T>
    class Buffer
    {
    public:
        explicit Buffer(size_t size = 1024)
            : _data(std::vector<T>(size)), _size(size), _buffered(0), _writter(0), _reader(0) {}
        Buffer(const Buffer<T> &other)
        {
            this(other._size);
            _data = other._data;
            _buffered = other._buffered;
            _writter = other._writter;
            _reader = other._reader;
        }
        Buffer &operator=(const Buffer<T> &other)
        {
            this(other._size);
            _data = other._data;
            _buffered = other._buffered;
            _writter = other._writter;
            _reader = other._reader;
            return *this;
        }
        virtual ~Buffer() = default;

        size_t write(T &toWrite)
        {
            if (_buffered == _size)
                return 0;
            if (_data.size() != _size)
            {
                _data.push_back(T(toWrite));
                _writter++;
                _buffered++;
            }
            else if (_writter == _data.size() - 1)
            {
                _writter = 0;
                _data[0] = T(toWrite);
                _buffered++;
            }
            else
            {
                _writter++;
                _buffered++;
                _data[_writter] = T(toWrite);
            }
            return 1;
        }

        size_t write(std::vector<T> &toWrite)
        {
            size_t count{0};

            for (auto it : toWrite)
                if (write(it))
                    count++;
                else
                    break;
            return count;
        }

        size_t writeStr(std::string &str)
        {
            size_t i{0};
            size_t strlen{str.size()};

            if (sizeof(T) != sizeof(char))
                return 0;
            for (; i < strlen && _buffered != _size - 1; i++)
                write(static_cast<T>(str[i]));
            write(static_cast<T>('0'));
            return i;
        }

        size_t writeC_str(char *str, size_t size)
        {
            size_t i{0};

            if (sizeof(T) != sizeof(char))
                return 0;
            for (; i < size && write(str[i]); i++)
                ;
            return i;
        }

        size_t read(T &dest)
        {
            if (!_buffered)
                return 0;
            if (_reader == _data.size() - 1)
                _reader = 0;
            else
                _reader++;
            dest = _data[_reader];
            _buffered--;
            return 1;
        }

        size_t read(std::vector<T> &dest, size_t size)
        {
            size_t i{0};
            T tmp;

            for (; i < dest.size() && i < size && read(tmp); i++)
                dest.push_back(tmp);
            return i;
        }

        size_t read(std::vector<T> &dest, T separator)
        {
            size_t i{0};
            T tmp;

            while (tmp != separator)
            {
                if (!read(tmp))
                    return i;
                dest.push_back(tmp);
                i++;
            }
            return i;
        }
        size_t readStr(std::string &dest)
        {
            char chr{0};
            size_t i{0};

            if (sizeof(T) != sizeof(char))
                return 0;
            do
            {
                if (!read(static_cast<T>(chr)))
                    break;
                dest.push_back(chr);
                i++;
            } while (chr);
            return i;
        }

        size_t readC_Str(char *str, size_t size)
        {
            size_t i{0};

            if (sizeof(T) != sizeof(char))
                return 0;
            for (; i < size && read(str[i]) && str[i] != '0'; i++)
                ;
            return i;
        }

        size_t readStrToDelim(std::string &str, std::string &delim)
        {
            char chr{0};
            size_t i{0};

            if (sizeof(T) != sizeof(char))
                return 0;
            do
            {
                if (!read(static_cast<T>(chr)))
                    break;
                str.push_back(chr);
                i++;
            } while (chr && str.find(delim, 0) != std::string::npos);
            return i;
        }

        std::vector<T> getData() const
        {
            return _data;
        }

        size_t skipBytes(size_t size)
        {
            T tmp;
            size_t i{0};

            for (; i < size && read(tmp); i++)
                ;
            return i;
        }
        void swap(Buffer<T> &other)
        {
            std::swap(_data, other._data);
            std::swap(_size, other._size);
            std::swap(_buffered, other._buffered);
            std::swap(_writter, other._writter);
            std::swap(_reader, other._reader);
        }

        void wipe()
        {
            _data.clear();
            _buffered = 0;
            _writter = 0;
            _reader = 0;
        }

        bool isFull() const
        {
            return _buffered == _size;
        }
        bool isEmpty() const
        {
            return !_buffered;
        }

        size_t getSize() const
        {
            return _size;
        }

        size_t getFreeSize() const
        {
            return _size - _buffered;
        }

        size_t getReadableSize() const
        {
            return _buffered;
        }

        void forEach(std::function<void(T &)> fun)
        {
            for (size_t i{_reader}, count{0}; count < _buffered; i++, count++)
                fun(_data[i]);
        }

    private:
        std::vector<T> _data;
        size_t _size;
        size_t _buffered;
        size_t _writter;
        size_t _reader;
    };
}

#endif
