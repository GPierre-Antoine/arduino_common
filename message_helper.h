//
// Created by Pierre-Antoine on 21/12/2016.
//

#ifndef DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H
#define DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H

//#include <Arduino.h>

namespace pag
{
    namespace message
    {

        template <unsigned base>
        struct numeral_base
        {
            int val;
            numeral_base (int val);
        };


        template <typename iter_t>
        class bridge;

        enum input_management
        {
            mode_blocking = true,
            mode_unblocking = false
        };

        class message_helper
        {
        private:
            Stream * stream;
            bool blocking_mode;
        public:

            void set_input_mode(input_management val);

            message_helper (Stream &s);


            template <typename T>
            message_helper& operator<<(const T & val);
            message_helper& operator<< (message_helper&(*function)(message_helper&));
            template <unsigned base>
            message_helper& operator<<(const pag::message::numeral_base<base> &structure);

            template <typename T>
            message_helper& operator>>(T & val);

            template <typename iter_t>
            message_helper& operator<<(const pag::message::editable &array);

            /**/
        };

        class editable
        {
        public:
            message_helper& run(message_helper&);
        };

        message_helper& editable::edit(message_helper & os)
        {
            return os;
        }


        template <typename iter_t>
        class bridge : public editable
        {
        public:
            iter_t * begin;
            iter_t * end;
            message_helper& (*f)(iter_t,iter_t,message_helper&);
            bridge(iter_t *begin, iter_t *end, message_helper& (*val)(iter_t,iter_t,message_helper&));
            message_helper& edit (message_helper&);

        };

        template <typename iter_t>
        message_helper& bridge<iter_t>::edit(message_helper & str)
        {
            return str << f(begin,end,str);
        }

        template <typename iter_t>
        bridge<iter_t>::bridge(iter_t *begin, iter_t *end, message_helper &(*val)(iter_t,iter_t,message_helper&)) :
                begin (begin), end (end), f (val)
        {}

        template <typename iter_t>
        message_helper& message_helper::operator<<(const pag::message::editable<iter_t> &obj)
        {
            return *this << array.edit(*this);
        }


        template <unsigned base>
        message_helper &message_helper::operator<<(const pag::message::numeral_base<base> &stru)
        {
            stream->print(stru.val,base);
            return *this;
        }

        template <unsigned base>
        pag::message::numeral_base<base>::numeral_base(int val) : val(val)
        {}


        template <typename T>
        pag::message::message_helper& pag::message::message_helper::operator<<(const T &val)
        {
            stream->print(val);
            return *this;
        }

        template <typename T>
        pag::message::message_helper& pag::message::message_helper::operator>>(T & val)
        {
            if (blocking_mode)
                while(!stream->available());
            val = stream->read();
            return *this;
        }


        pag::message::message_helper& endl(pag::message::message_helper &os);

        //todo collection bridge
    }

    static message::message_helper cios(Serial);
    using message::endl;
    template <unsigned num_base>
    using base = struct message::numeral_base<num_base>;
    template <typename iter_t>
    using bridge =  message::bridge<iter_t>;
}

#endif //DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H
