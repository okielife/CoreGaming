#pragma once

struct AxisRepeater
{
    float initialDelay = 0.25f;
    float repeatRate   = 0.10f;

    float timer = 0.f;
    int direction = 0;  // -1, 0, +1

    bool update(float dt, int newDirection)
    {
        if (newDirection == 0)
        {
            direction = 0;
            timer = 0.f;
            return false;
        }

        if (newDirection != direction)
        {
            direction = newDirection;
            timer = 0.f;
            return true; // immediate first step
        }

        timer += dt;

        if (timer >= initialDelay)
        {
            if (timer >= initialDelay + repeatRate)
            {
                timer = initialDelay;
                return true;
            }
        }

        return false;
    }
};