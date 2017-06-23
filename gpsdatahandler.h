#ifndef GPSDATA_H
#define GPSDATA_H

#include <QtCore/qglobal.h>
#include <QVector>
#include <math.h>

using namespace std;


struct point{

    double latitude;
    double longitude;

};

class gpsdatahandler{

public:

    const static QVector<float> Trackpoints;

    // Attributes

    unsigned int numGPSValues;
    QVector<double> distanceData;
    QVector<double> altitudeData;

    // Methods

    gpsdatahandler(void);
    void computeDistAlt(void);
    inline QVector<double> *getDistanceData(void){ return &this->distanceData;};
    inline QVector<double> *getAltitudeData(void){ return &this->altitudeData;};

private:

    const static int earthRadius = 6378000; // Unit: mtrs

    double computeDistance(point dStart, point dEnd);
    inline double degToRad(double degAngle){ return ((degAngle * M_PI) / 180.0); };
    point degPointToRad(point dPoint);

    void printData();

};

#endif // GPSDATA_H
