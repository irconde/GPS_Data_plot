#ifndef GPSDATA_H
#define GPSDATA_H

#include <QtCore/qglobal.h>
#include <QVector>

using namespace std;


struct point{

    float p1;
    float p2;
    float p3;
};

class gpsdatahandler{

public:

    const static QVector<float> Trackpoints;

    // Attributes

    unsigned int numGPSValues;
    QVector<float> distanceData;
    QVector<float> altitudeData;

    // Methods

    gpsdatahandler(void);
    void computeDistAlt(void);

    inline QVector<float> *getDistanceData(void){ return &this->distanceData;};
    inline QVector<float> *getAltitudeData(void){ return &this->altitudeData;};

private:

    float computeDistance(point start, point end);
    void polarToCartesian(point polar, point &cartesian);
    void printData();

};

#endif // GPSDATA_H
