/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "pfdqmlgadgetconfiguration.h"
#include "utils/pathutils.h"

/**
 * Loads a saved configuration or defaults if non exist.
 *
 */
PfdQmlGadgetConfiguration::PfdQmlGadgetConfiguration(QString classId, QSettings *qSettings, QObject *parent) :
    IUAVGadgetConfiguration(classId, parent),
    m_qmlFile("Unknown"),
    m_actualPositionUsed(false),
    m_latitude(0),
    m_longitude(0),
    m_altitude(0)
{
    //if a saved configuration exists load it
    if(qSettings != 0) {
        m_qmlFile = qSettings->value("qmlFile").toString();
        m_qmlFile=Utils::PathUtils().InsertDataPath(m_qmlFile);

        m_actualPositionUsed = qSettings->value("actualPositionUsed").toBool();
        m_latitude = qSettings->value("latitude").toDouble();
        m_longitude = qSettings->value("longitude").toDouble();
        m_altitude = qSettings->value("altitude").toDouble();

        foreach (const QString &key, qSettings->childKeys()) {
            m_settings.insert(key, qSettings->value(key));
        }
    }
}

/**
 * Clones a configuration.
 *
 */
IUAVGadgetConfiguration *PfdQmlGadgetConfiguration::clone()
{
    PfdQmlGadgetConfiguration *m = new PfdQmlGadgetConfiguration(this->classId());
    m->m_qmlFile = m_qmlFile;
    m->m_actualPositionUsed = m_actualPositionUsed;
    m->m_latitude = m_latitude;
    m->m_longitude = m_longitude;
    m->m_altitude = m_altitude;
    m->m_settings = m_settings;

    return m;
}

/**
 * Saves a configuration.
 *
 */
void PfdQmlGadgetConfiguration::saveConfig(QSettings* qSettings) const {
    QString qmlFile = Utils::PathUtils().RemoveDataPath(m_qmlFile);
    qSettings->setValue("qmlFile", qmlFile);

    qSettings->setValue("actualPositionUsed", m_actualPositionUsed);
    qSettings->setValue("latitude", m_latitude);
    qSettings->setValue("longitude", m_longitude);
    qSettings->setValue("altitude", m_altitude);
}
