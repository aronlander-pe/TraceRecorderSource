/*
 * Trace Recorder for Tracealyzer v4.6.6
 * Copyright 2021 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * An example of a Tracealyzer extension for tracing API calls, in this case
 * for tracing selected functions in Amazon FreeRTOS/aws_wifi.
 * See trcExtensions.h for information on how to use this.
 *
 * To create your own extension, first make sure to read the documentation
 * in trcExtensions.h. Then, to create an extension header file like this
 * one, you need to provide:
 *
 *  - Extension Definitions - name and event codes of the extensions.
 *
 *  - Trace Wrappers - calls the original function and traces the event.
 *
 *  - Function Redefinitions - changes the function calls to the trace wrappers.
 *
 * See the below comments for details about these definitions. Note that you
 * also need a matching .xml file for Tracealyzer to understand the data.
 * See trcExtensions.h for further information.
 */

#ifndef _AWS_WIFI_TZEXT_H
#define _AWS_WIFI_TZEXT_H

/***** Extension Definitions (must use the same prefix!) *****/

/******************************************************************************
 * <EXTENSIONPREFIX>_NAME
 * The name of the extension as a string constant. This name is used by the
 * Tracealyzer host application to find the right XML file for interpreting
 * the events. Assuming the extension name is "aws_secure_sockets", Tracealyzer
 * will look for an XML file named "aws_secure_sockets-<VERSION>.xml", first in
 * the folder of the current trace file, next in the Tracealyzer 4/cfg folder.
 * For the VERSION part, see the TRC_EXT_<ExtName>_VERSION macros below.
 *
 * Note: The extension name displayed in Tracealyzer is defined in the XML file
 * in the EventGroup element (e.g. <EventGroup name="SOCKETS">)
 *
 *****************************************************************************/
#define TRC_EXT_WIFI_NAME "aws_wifi"

/******************************************************************************
 * <EXTENSIONPREFIX>_VERSION_MAJOR
 * <EXTENSIONPREFIX>_VERSION_MINOR
 * <EXTENSIONPREFIX>_VERSION_PATCH
 *
 * The version code of the extension (MAJOR.MINOR.PATCH)
 *
 * If you increment the version code when modifying an extension, you can still
 * show old traces recorded using an earlier version of the extension.
 *
 * Assuming the extension name is "aws_secure_sockets", and the below version
 * codes are 1 (MAJOR), 2 (MINOR), 3 (PATCH), Tracealyzer will assume the
 * corresponding XML file is named "aws_secure_sockets-v1.2.3.xml". So if then
 * view a trace recorded with extension version 1.2.2, those traces will look
 * for "aws_secure_sockets-v1.2.2.xml" instead.
 *
 * Note that major and minor are stored as 8 bit values, while patch is stored
 * using 16 bits. They are treated as unsigned integers, so the maximum values
 * are 256, 256 and 65535.
 *****************************************************************************/
#define TRC_EXT_WIFI_VERSION_MAJOR 1

#define TRC_EXT_WIFI_VERSION_MINOR 0

#define TRC_EXT_WIFI_VERSION_PATCH 0

/******************************************************************************
 * <EXTENSIONPREFIX>_<EVENTCODE>
 * The event codes used in the trace wrapper functions. Important that these
 * are relative to <PREFIX>_FIRST.
 *****************************************************************************/
#define EVENTCODE_WIFI_On (TRC_EXT_BASECODE + 0)

#define EVENTCODE_WIFI_Off (TRC_EXT_BASECODE + 1)

#define EVENTCODE_WIFI_ConnectAP (TRC_EXT_BASECODE + 2)

/******************************************************************************
 * <EXTENSIONPREFIX>_COUNT
 * The number of event codes used by this extension. Should be at least 1.
 * Tracealyzer allows for events codes up to 4095.
 *****************************************************************************/
#define TRC_EXT_WIFI_COUNT 3


/***** Trace Wrappers *****/

#include <aws_wifi.h> /* Including the original header file, so that custom data types are understood. */

static inline WIFIReturnCode_t WIFI_On__trace( void )
{
	 WIFIReturnCode_t ret = WIFI_On();

	// Note: The host-side xml file assumes that ret == 0 means OK, otherwise timeout/error.
	prvTraceStoreEvent1(EVENTCODE_WIFI_On, (uint32_t)ret);

	return ret;
}

 static inline WIFIReturnCode_t WIFI_Off__trace( void )
 {
 	 WIFIReturnCode_t ret = WIFI_Off();

 	// Note: The host-side xml file assumes that ret == 0 means OK, otherwise timeout/error.
 	prvTraceStoreEvent1(EVENTCODE_WIFI_Off, (uint32_t)ret);

 	return ret;
 }

 static inline WIFIReturnCode_t WIFI_ConnectAP__trace( const WIFINetworkParams_t * const pxNetworkParams )
 {
	 WIFIReturnCode_t ret = WIFI_ConnectAP(pxNetworkParams);

	 // Note: The host-side xml file assumes that ret == 0 means OK, otherwise timeout/error.

	 prvTraceStoreStringEvent(2, EVENTCODE_WIFI_ConnectAP, pxNetworkParams->pcSSID, pxNetworkParams->xSecurity, ret);

	 return ret;
 }

/***** Function Redefinitions *****/

#define WIFI_On WIFI_On__trace

#define WIFI_Off WIFI_Off__trace

#define WIFI_ConnectAP WIFI_ConnectAP__trace

#endif /* _AWS_SECURE_SOCKETS2_TZEXT_H */
