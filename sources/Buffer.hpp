/*
** EPITECH PROJECT, 2022
** CPPLIB-Buffer [WSL: Ubuntu]
** File description:
** Buffer
*/

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>
#include <string>

namespace MTLib {
    class Buffer {
        public:
            explicit Buffer(size_t size = 1024);
            virtual ~Buffer() = default;

            auto getData() const -> std::vector<int8_t>;

        private:
            std::vector<int8_t> data;
            size_t writter;
            size_t reader; 
    };
}

#endif /* !BUFFER_HPP_ */
