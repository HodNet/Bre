//
// Created by jonat on 24/12/2020.
//

#ifndef BRE_FPS_H
#define BRE_FPS_H

struct Fps
{
    unsigned short int frame = 0;
    unsigned short int fps = 0;
    Cronometro t;

    void update()
    {
        if(t.now('u') >= 5000000)
        {
            t.start(200);
            frame = fps * t.now('u') / 1000000;
        }
        if(frame==0) t.start();
        frame++;
        if(frame%50 == 0) fps =  frame * 1000000 / t.now('u');
    }
};

#endif //BRE_FPS_H
