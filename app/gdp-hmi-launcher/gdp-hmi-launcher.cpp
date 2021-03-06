/**
 * SPDX license identifier: MPL-2.0
 *
 * Copyright (C) 2015, GENIVI Alliance
 *
 * This file is part of GENIVI Demo Platform HMI.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License (MPL), v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For further information see http://www.genivi.org/.
 *
 * List of changes:
 * 09.Feb.2014, Holger Behrens, written
 */

/*! \file gdp-hmi-launcher.cpp
 *  \brief HMI launcher class for the GENIVI Demo Platform
 *   
 *  This component implements the HMI launcher class of the
 *  GENIVI Demo Platform.
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <systemd/sd-journal.h>

#include "gdp-hmi-launcher.h"

static const char *GDP_HMI_PID_FILENAME  = "/var/run/gdp-hmi-controller.pid";
static const char *GDP_DBUS_SERVICE_NAME = "org.genivi.gdp.hmi.controller";
static const char *GDP_DBUS_SERVICE_PATH = "/org/genivi/gdp/hmi/controller";

GDPLauncherClass::GDPLauncherClass()
: m_hmiControllerPid(-1)
{
    sd_journal_print(LOG_DEBUG, "Debug: GDPLauncherClass - dbus session.\n");
	m_controller = new org::genivi::gdp::HMI_Controller(GDP_DBUS_SERVICE_NAME,
		GDP_DBUS_SERVICE_PATH, QDBusConnection::sessionBus(), this);
    m_timerId = startTimer(5000); // 5 second timer
}

GDPLauncherClass::~GDPLauncherClass()
{
}

void GDPLauncherClass::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if ( !(m_controller->isValid()) ) {
        sd_journal_print(LOG_INFO, "Info: HMI Controller - disconnected.\n");
    }
}
