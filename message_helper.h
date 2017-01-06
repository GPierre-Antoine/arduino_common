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

            template <typename T>
            message_helper& operator>>(T & val);

            /**/
        };




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
}

#endif //DEV_UBBO_DOCKSTATION_MESSAGE_HELPER_H
