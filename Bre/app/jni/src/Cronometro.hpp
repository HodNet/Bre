//
// Created by jonat on 13/10/2020.
//

#ifndef BRE_CRONOMETRO_HPP
#define BRE_CRONOMETRO_HPP
#include <chrono>
#include <vector>

struct tempino
{
    std::chrono::steady_clock::time_point inizio;
    std::chrono::steady_clock::time_point fine;
};

class Cronometro{
    private:
        unsigned int ritardo = 0;
        std::vector<tempino> coppia;
        bool cronometraggio=false;

    public:
        Cronometro() {}

        void start(unsigned int ritardo_in_milli = 0)
        {
            ritardo = ritardo_in_milli;
            coppia.clear();
            cronometraggio = true;
            coppia.push_back({});
            coppia.back().inizio = std::chrono::high_resolution_clock::now();
        }
        void stop()
        {
            if(cronometraggio)
            {
                cronometraggio=false;
                if (coppia.size() != 0) coppia.back().fine = std::chrono::high_resolution_clock::now();
            }
        }
        void riprendi()
        {
            cronometraggio = true;
            coppia.push_back({});
            coppia.back().inizio = std::chrono::high_resolution_clock::now();
        }
        unsigned long long int now(char micro_milli_sec)
        {
            unsigned long long int tempo = 0;
            switch (micro_milli_sec)
            {
                case 's':
                    if (cronometraggio && coppia.size() != 0)
                        coppia.back().fine = std::chrono::high_resolution_clock::now();
                    for (tempino const &x : coppia)
                        tempo += std::chrono::duration_cast<std::chrono::seconds>(x.fine - x.inizio).count();
                    return tempo + ritardo / 1000;
                    break;

                case 'm':
                    if (cronometraggio && coppia.size() != 0)
                        coppia.back().fine = std::chrono::high_resolution_clock::now();
                    for (tempino const &x : coppia)
                        tempo += std::chrono::duration_cast<std::chrono::milliseconds>(x.fine - x.inizio).count();
                    return tempo + ritardo;
                    break;

                case 'u':
                    if (cronometraggio && coppia.size() != 0)
                        coppia.back().fine = std::chrono::high_resolution_clock::now();
                    for (tempino const &x : coppia)
                        tempo += std::chrono::duration_cast<std::chrono::microseconds>(x.fine - x.inizio).count();
                    return tempo + ritardo * 1000;
                    break;

                default:
                    break;
            }
        }
};


#endif //BRE_CRONOMETRO_HPP
