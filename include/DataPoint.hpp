#ifndef GROUPMPROJECT_DATAPOINT_HPP
#define GROUPMPROJECT_DATAPOINT_HPP

#include <Body.hpp>

#include <iostream>

/**
 * @brief stripped-down version of Body object to save data on disc efficiently
 *
 *
 * Of course, we could store the body objects directly on the disc.
 * But then we would also store all the methods of the body object, like the getNorm() function etc there - we don't need that
 *
 * Instead I thought we could use this Data point struct, which is basically a stripped-down version of the Body object, to save some memory
 *
 * A body object is 128 byte large - but only 80 byte are made up by numerical data.
 * Sadly, we can not go down to 80 byte with the DataPoint struct, because the compiler adds a lot of padding to satisfy alignment constraints.
 * But with the #pragma pack(1) directive we can go down to 104 byte -> removed that again, because it led to a stack smashing error when included.
 * 
 * Nico: Why do we even want to save our Bodies in a custom file format? I thought we concluded
 * on using some existing file format for numeric data? Shouldn't this be more efficient?
 */
struct DataPoint{
    int weight;
    int size;
    long double x;
    long double y;
    long double vx;
    long double vy;
    long double ax;
    long double ay;


    DataPoint(Body body) 
    {
        size = body.getSize();
        weight = body.getWeight();
        x = body.getPos().x;
        y = body.getPos().y;
        vx = body.getVel().x;
        vy = body.getVel().y;
        ax = body.getAcc().x;
        ay = body.getAcc().y;
    }

    DataPoint() {}

    DataPoint(
        int in_weight,
        int in_size,
        long double in_x,
        long double in_y,
        long double in_vx,
        long double in_vy,
        long double in_ax,
        long double in_ay
    )
    : weight(in_weight), size(in_size), x(in_x), y(in_y), vx(in_vx), vy(in_vy), ax(in_ax), ay(in_ay) {}

    void print() {
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << vy << std::endl;
        std::cout << vy << std::endl;
        std::cout << ay << std::endl;
        std::cout << ay << std::endl;
        std::cout << weight << std::endl;
        std::cout << size << std::endl;
    }
    
};

#endif //GROUPMPROJECT_DATAPOINT_HPP
