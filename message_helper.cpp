//
// Created by Pierre-Antoine on 21/12/2016.
//

#include "message_helper.h"

using namespace pag::message;

message_helper::message_helper(Stream & s) : stream (&s), blocking_mode(true)
{}

message_helper& message_helper::operator<<(message_helper&(*function)(message_helper&))
{
    return function(*this);
}

pag::message::message_helper& pag::message::endl(pag::message::message_helper &os)
{
    os << '\n';
    return os;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(long & val)
{
    if (blocking_mode)
        while(!stream->available());
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseInt();
    return *this;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(int &val)
{
    if (blocking_mode)
        while(!stream->available());
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseInt();
    return *this;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(unsigned & val)
{
    if (blocking_mode)
        while(!stream->available());
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseInt();
    return *this;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(float & val)
{
    if (blocking_mode)
        while(!stream->available());
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseFloat();
    return *this;
}

void pag::message::message_helper::set_input_mode(input_management val)
{
    this->blocking_mode = val;
}
