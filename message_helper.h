//
// Created by Pierre-Antoine on 21/12/2016.
//

#ifndef DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H
#define DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H

#include <Arduino.h>

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


        enum input_management
        {
            mode_blocking = true,
            mode_unblocking = false
        };

        template <typename iter_t>
        struct collection_helper;

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
            message_helper& operator<<(const pag::message::collection_helper<iter_t> &array);

            /**/
        };


        template <typename iter_t>
        struct collection_helper
        {
            typedef iter_t (*functor)(iter_t);
            iter_t * begin;
            iter_t * end;
            functor f;


            collection_helper(iter_t *begin, iter_t *end, functor val);

        };



        template <typename iter_t>
        collection_helper<iter_t>::collection_helper(iter_t *begin, iter_t *end, functor val) : begin(begin), end (end), f (val)
        {}

        template<typename iter_t>
        message_helper &message_helper::operator<<(const pag::message::collection_helper<iter_t> &array)
        {
            *this << '[';
            for (iter_t* i = array.begin;i<array.end-1;++i)
            {
                *this << array.f(*i) << ',' << ' ';
            }
            *this << array.f (*(array.end-1)) << ']';
            return *this;
        }


        template <unsigned base>
        message_helper &message_helper::operator<<(const pag::message::numeral_base<base> &stru)
        {
            stream->print(stru.val,base);
            return *this;
        }

        template <unsigned base>
        pag::message::numeral_base<base>::numeral_base(int val) : val(val)
        {

        }


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
    using collection = struct message::collection_helper<iter_t>;
}

#endif //DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H
