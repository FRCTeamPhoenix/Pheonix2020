#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "PIDTuner.h"
#include "frc/smartdashboard/SmartDashboard.h"

using namespace std;
using namespace nlohmann;

class PIDTuner {
    private:
        double P, I, D, e, s, r, t, i, l;

    public:
        PIDTuner() {
            e = 0.0, s = 0.0, r = 0.0, l = 0.0, i = 0.0;
            t = 0.02;
            load();
            send();
            function<void()> f = [this]() { this->recv(); };
            frc::SmartDashboard::PostListenerTask(f);
        }

        void set_pos(double se) {
            s = se;
        }

        double get_pos() {
            return s;
        }

        void calc() {
            double p = s - get_pos();
            i += p * t;
            double d = (p - l) / t;
            r = P * p + I * i + D * d;
            l = p;
        }

        void tune() {

        }

        void send() {
            frc::SmartDashboard::PutNumber("PID_P", P);
            frc::SmartDashboard::PutNumber("PID_I", I);
            frc::SmartDashboard::PutNumber("PID_D", D);
            frc::SmartDashboard::UpdateValues();
        }

        void recv() {
            P = frc::SmartDashboard::GetNumber("PID_P", P);
            I = frc::SmartDashboard::GetNumber("PID_I", I);
            D = frc::SmartDashboard::GetNumber("PID_D", D);
            dump(P, I, D);
        }

        void load() {
            json j;
            string l, t;
            ifstream f;
            f.open("cfg.json");
            while (getline(f, l)) {
                t += l + " ";
            }
            j = json::parse(t);
            P = j["P"];
            I = j["I"];
            D = j["D"];
        }

        void dump(double a, double b, double c) {
            json j = {
                {"P", a},
                {"I", b},
                {"D", c}
            };
            ofstream f;
            f.open("cfg.json");
            f << j.dump(2);
            f.close();
        }

        void exec() {
            calc(); 
        }
};