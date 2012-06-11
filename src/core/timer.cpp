#include "core/timer.h"

namespace meh {

Timer::Timer(int delay) {
    aTimer = al_create_timer(static_cast<double>(delay)/1000);
    reset();
}

Timer::~Timer() {
    if (aTimer) {
        al_destroy_timer(aTimer);
    }
}

void Timer::start() {
    al_start_timer(aTimer);
}

void Timer::stop() {
    al_stop_timer(aTimer);
}

void Timer::reset() {
    if (aTimer) {
        al_set_timer_count(aTimer,0);
    }
}

int Timer::count() {
    if (aTimer) {
        return al_get_timer_count(aTimer);
    }
    return 0;
}

void Timer::setCount(int count) {
    if (aTimer) {
        al_set_timer_count(aTimer,count);
    }
}

double Timer::delay() {
    return al_get_timer_speed(aTimer);
}

void Timer::setDelay(int delay) {
    if (aTimer) {
        al_set_timer_speed(aTimer,static_cast<double>(delay)/1000);
    }
}

}
