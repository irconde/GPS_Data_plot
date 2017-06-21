#ifndef GPSDATA_H
#define GPSDATA_H

#include <QtCore/qglobal.h>
#include <QVector>

using namespace std;


class gpsdatahandler{

public:

    const static QVector<float> gpsValues;

    // Attributes

    unsigned int numGPSValues;
    QVector<float> distanceData;
    QVector<float> altitudeData;

    // Methods

    gpsdatahandler(void);
    void computeDistAlt(void);
    QVector<float> getDistanceData(void);
    QVector<float> getAltitudeData(void);

};

#endif // GPSDATA_H
