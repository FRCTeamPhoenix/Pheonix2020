#ifndef PIDTUNER_H
#define PIDTUNER_H

class PID {
    float P, I, D, e, s, r, i;
    public:
        PID();
        void set();
        void calc();
        void exec();
        void send();
        void recv();
        void load();
        void get();
};

#endif 