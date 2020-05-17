#include "Strategy.h"

namespace corsim
{
    int RegularMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        int numberInfected = 0;
        for(Subject& s : subjects)
        {
            s.set_x(s.x() + s.dx() * dt);
            s.set_y(s.y() + s.dy() * dt);
            if(s.infected())
            {
                numberInfected++;
            }
        }
        return numberInfected;
    }

    int LockdownMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        if (run == NULL)
        {
            int num = subjects.size()/4*3;

            for (int i = 0; i < num; i++)
            {
                subjects.at(i).setLocked(true);
            }
            
            run = true;
        }

        int numberInfected = 0;

        for (Subject& s : subjects)
        {
            if (s.getLocked() != true)
            {
                s.set_x(s.x() + s.dx() * dt);
                s.set_y(s.y() + s.dy() * dt);
            }
            if(s.infected())
            {
                numberInfected++;
            }
        }
        
        return numberInfected;
    }
    int SocialMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        // Determine half of the subjects
        int halfSub = subjects.size() * 0.5;
        // Determine 75% of the subjects
        int slowSub = subjects.size() * 0.75;
        // Set the speed of the subjects should move. Lowest than 1/3 of the normal speed will stop the subject from moving
        int dtSlow = dt * 1/3;

        int numberInfected = 0;

        for (int i = 0; i < slowSub; i++)
        {
            subjects.at(i).setSlow(true);
        }

        for(Subject& s : subjects)
            {
                if(s.infected())
                {
                    numberInfected++;
                }
                // If less than half, move at normal speed
                if (numberInfected < halfSub)
                {
                    s.set_x(s.x() + s.dx() * dt);
                    s.set_y(s.y() + s.dy() * dt);
                    
                }
                // If less than half, change speeds
                else if (numberInfected > halfSub)
                {
                    // If the subjects are in the 75% group that will be slowed
                    if (s.slow() == true)
                    {
                        s.set_x(s.x() + s.dx() * dtSlow);
                        s.set_y(s.y() + s.dy() * dtSlow);
                    }
                    // If the subjects are in the 25% group that move at normal speed
                    else 
                    {
                        s.set_x(s.x() + s.dx() * dt);
                        s.set_y(s.y() + s.dy() * dt);
                    }
                }
            }
        return numberInfected;
    }
}