
#pragma once

#include "MoveStrategy.h"


namespace corsim
{
    class RegularMovement: public MovementStrategy
    {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
    };

    class LockdownMovement: public MovementStrategy
    {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
        private:
        bool run;
    };

     class SocialMovement: public MovementStrategy
    {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
        private:
        bool run;
        
    };
}