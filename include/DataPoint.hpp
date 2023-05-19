#ifndef GROUPMPROJECT_DATAPOINT_HPP
#define GROUPMPROJECT_DATAPOINT_HPP

#pragma pack(1)
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
 * But with the #pragma pack(1) directive we can go down to 104 byte
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
};
#endif //GROUPMPROJECT_DATAPOINT_HPP
