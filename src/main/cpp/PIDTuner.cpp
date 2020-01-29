#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "PIDTuner.h"
#include <frc/smartdashboard/SmartDashboard.h>

using namespace std;
using namespace nlohmann;

PIDTuner::PIDTuner() {
    s = 0.0, r = 0.0, l = 0.0, i = 0.0, t = 0.02;
}

void PIDTuner::init() {
    load();
    send();
    function<void()> f = [this]() { this->recv(); };
    frc::SmartDashboard::PostListenerTask(f);
}

void PIDTuner::set_pos(double se) {
    s = se;
}

double PIDTuner::get_pos() {
    return s;
}

void PIDTuner::calc() {
    double p = s - get_pos();
    i += p * t;
    double d = (p - l) / t;
    r = P * p + I * i + D * d;
    l = p;
}

void PIDTuner::send() {
    frc::SmartDashboard::PutNumber("PID_P", P);
    frc::SmartDashboard::PutNumber("PID_I", I);
    frc::SmartDashboard::PutNumber("PID_D", D);
    frc::SmartDashboard::UpdateValues();
}

void PIDTuner::recv() {
    P = frc::SmartDashboard::GetNumber("PID_P", P);
    I = frc::SmartDashboard::GetNumber("PID_I", I);
    D = frc::SmartDashboard::GetNumber("PID_D", D);
    dump(P, I, D);
}

void PIDTuner::dump(double a, double b, double c) {
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

void PIDTuner::load() {
    json j;
    string q, y = "";
    ifstream f;
    f.open("cfg.json");
    while (getline(f, q)) {
        y += q + " ";
    }
    j = json::parse(y);
    P = j["P"];
    I = j["I"];
    D = j["D"];
}