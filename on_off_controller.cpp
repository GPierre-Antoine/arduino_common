//
// Created by Pierre-Antoine on 22/11/2016.
//

#include <Arduino.h>//digitalread, high, low, input, input_pullup

#include "on_off_controller.h"


pag::on_off_controller::on_off_controller(unsigned short int pin) :
        pin(pin)
{
    set_mode(input_mode());
}

void pag::on_off_controller::set_mode(const serial_mode &mode)
{
    mode.set(pin);
    working_mode=mode.get_working_mode();
}

const bool pag::on_off_controller::is_on() const
{
    return digitalRead(pin) == working_mode;
}

pag::on_off_controller::operator bool() const
{
    return is_on();
}

const bool pag::on_off_controller::is_off() const
{
    return !is_on();
}

void pag::input_mode::set(const int pin) const
{
    pinMode(pin,INPUT);
}

void pag::input_pullup_mode::set(const int pin) const
{
    pinMode(pin,INPUT_PULLUP);
}

int pag::input_pullup_mode::get_working_mode() const
{
    return LOW;
}
int pag::input_mode::get_working_mode() const
{
    return HIGH;
}

void pag::serial_mode::set(const int pin) const
{}
int pag::serial_mode::get_working_mode() const
{
    return -1;
}
