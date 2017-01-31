//
// Created by Pierre-Antoine on 22/11/2016.
//

#ifndef PAG_ON_OFF_CONTROLLER_H
#define PAG_ON_OFF_CONTROLLER_H

#include <Arduino.h>

namespace pag
{
    class serial_mode
    {
    public:
        virtual void set(const int pin) const;
        virtual int get_working_mode() const;
        virtual ~serial_mode(){}
    };

    class input_mode : public serial_mode
    {
    public:
        input_mode(){}
        virtual void set(const int pin) const;
        virtual int get_working_mode() const;
    };
    class  input_pullup_mode : public serial_mode
    {
    public:
        input_pullup_mode(){}
        virtual void set(const int pin) const;
        virtual int get_working_mode() const;
    };


    class on_off_controller
    {
        const unsigned short int pin;
        int working_mode;
    public:
        on_off_controller (unsigned short int pin);
        void set_mode(const serial_mode & mode);
        const bool is_on() const;
        const bool is_off() const;
        operator bool () const;

    };
}


#endif //PAG_ON_OFF_CONTROLLER_H
