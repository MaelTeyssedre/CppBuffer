/*
** EPITECH PROJECT, 2022
** CPPLIB-Buffer [WSL: Ubuntu]
** File description:
** Buffer
*/

#include "Buffer.hpp"


explicit MTLib::Buffer::Buffer(size_t size)
    : data(size), reader(0), writter(0) {}

auto MTLib::Buffer::getData() const -> std::vector<int8_t>
{
    return data;
}