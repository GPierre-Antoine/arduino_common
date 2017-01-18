//
// Created by Pierre-Antoine on 21/12/2016.
//

#include "message_helper.h"

using namespace pag::message;

message_helper::message_helper(Stream & s) : stream (&s)
{}

void message_helper::set_input_mode(input_management val)
{
    blocking_mode = val;
}

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
pag::message::message_helper& pag::message::message_helper::operator>>(int & val)
{
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseInt();
    return *this;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(long & val)
{
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseInt();
    return *this;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(unsigned & val)
{
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseInt();
    return *this;
}

template <>
pag::message::message_helper& pag::message::message_helper::operator>>(float & val)
{
    const int number = stream->peek();
    if (number >= '0' && number <= '9')
        val = stream->parseFloat();
    return *this;
}


