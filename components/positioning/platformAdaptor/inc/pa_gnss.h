/**
 * @page c_pa_gnss Platform Adapter Global Navigation Satellite System API
 *
 * @ref pa_gnss.h "API Reference"
 *
 * <HR>
 *
 * Copyright (C) Sierra Wireless Inc.
 */


/** @file pa_gnss.h
 *
 * Legato @ref c_pa_gnss include file.
 *
 * Copyright (C) Sierra Wireless Inc.
 */

#ifndef LEGATO_PA_GNSS_INCLUDE_GUARD
#define LEGATO_PA_GNSS_INCLUDE_GUARD

#include "legato.h"
#include "interfaces.h"

//--------------------------------------------------------------------------------------------------
// Symbol and Enum definitions.
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
/**
 * Type of restart.
 */
//--------------------------------------------------------------------------------------------------
typedef enum {
    PA_GNSS_UNKNOWN_RESTART = 0,    ///< Unknown case.
    PA_GNSS_HOT_RESTART,            ///< Hot restart.
    PA_GNSS_WARM_RESTART,           ///< Warm restart.
    PA_GNSS_COLD_RESTART,           ///< Cold restart.
    PA_GNSS_FACTORY_RESTART         ///< Factory restart.
}pa_gnss_Restart_t;

//--------------------------------------------------------------------------------------------------
/**
 * Time structure.
 */
//--------------------------------------------------------------------------------------------------
typedef struct {
    uint16_t hours;               ///< The Hours.
    uint16_t minutes;             ///< The Minutes.
    uint16_t seconds;             ///< The Seconds.
    uint16_t milliseconds;        ///< The Milliseconds.
}
pa_Gnss_Time_t;

//--------------------------------------------------------------------------------------------------
/**
 * Date structure.
 */
//--------------------------------------------------------------------------------------------------
typedef struct {
    uint16_t year;                ///< The Year.
    uint16_t month;               ///< The Month.
    uint16_t day;                 ///< The Day.
}
pa_Gnss_Date_t;

//--------------------------------------------------------------------------------------------------
/**
 * Satellite Vehicle information.
 */
//--------------------------------------------------------------------------------------------------
typedef struct {
    uint16_t                satId;        ///< Satellite in View ID number.
    le_gnss_Constellation_t satConst;     ///< GNSS constellation type.
    bool                    satUsed;      ///< TRUE if satellite in View is used for fix Navigation.
    bool                    satTracked;   ///< TRUE if satellite in View is tracked for Navigation.
    uint8_t                 satSnr;       ///< Satellite in View Signal To Noise Ratio [dBHz].
    uint16_t                satAzim;      ///< Satellite in View Azimuth [degrees].
                                          ///< Range: 0 to 360
    uint8_t                satElev;       ///< Satellite in View Elevation [degrees].
                                          ///< Range: 0 to 90
}
Pa_Gnss_SvInfo_t;

//--------------------------------------------------------------------------------------------------
/**
 * Satellite Measurement information.
 */
//--------------------------------------------------------------------------------------------------
typedef struct {
    uint16_t satId;          ///< Satellite in View ID number.
    int32_t  satLatency;     ///< Satellite latency measurement (age of measurement)
                             ///< Units: Milliseconds.
}
Pa_Gnss_SvMeasurement_t;

//--------------------------------------------------------------------------------------------------
/**
 * Position structure.
 */
//--------------------------------------------------------------------------------------------------
typedef struct {
    le_gnss_FixState_t fixState;      ///< Position Fix state

    bool               latitudeValid; ///< if true, latitude is set
    int32_t            latitude;  ///< The Latitude in degrees, positive North,
                                  ///  with 6 decimal places (+48858300  = 48.858300 degrees North).

    bool               longitudeValid; ///< if true, longitude is set
    int32_t            longitude; ///< The Longitude in degrees, positive East,
                                  ///  with 6 decimal places.

    bool               altitudeValid; ///< if true, altitude is set
    int32_t            altitude;  ///< The Altitude in meters, above Mean Sea Level,
                                  ///  with 3 decimal places.

    bool               altitudeOnWgs84Valid; ///< if true, altitudeOnWgs84 is set
    int32_t            altitudeOnWgs84;  ///< The altitudeOnWgs84 in meters, between WGS-84 earth
                                         ///  ellipsoid and mean sea level with 3 decimal places.

    bool               hSpeedValid; ///< if true, horizontal speed is set
    uint32_t           hSpeed;    ///< The horizontal Speed in m/sec, with 2 decimal places
                                  ///  (125 = 1.25m/sec).

    bool               vSpeedValid; ///< if true, vertical speed is set
    uint32_t           vSpeed;    ///< The vertical Speed in m/sec, with 2 decimal places
                                  ///  (125 = 1.25m/sec).

    bool               directionValid;  ///< if true, direction is set
    uint32_t           direction;       ///< Direction in degrees, where 0 is True North, with 1
                                        ///  decimal place (308  = 30.8 degrees).

    bool               headingValid; ///< if true, heading is set
    uint32_t           heading;     ///< heading in degrees, where 0 is True North, with 1
                                  ///  decimal place (308  = 30.8 degrees).

    bool               hdopValid; ///< if true, horizontal dilution is set
    uint16_t           hdop;      ///< The horizontal Dilution of Precision (DOP)

    bool               pdopValid; ///< if true, position dilution is set
    uint16_t           pdop;      ///< The Position dilution of precision (DOP)

    bool               vdopValid; ///< if true, vertical dilition is set
    uint16_t           vdop;      ///< The vertical Dilution of Precision (DOP)

    bool               hUncertaintyValid; ///< if true, horizontal uncertainty is set
    uint32_t           hUncertainty;  ///< The horizontal uncertainty in meters,
                                      ///  with 2 decimal places

    bool               vUncertaintyValid; ///< if true, vertical uncertainty is set
    uint32_t           vUncertainty;  ///< The vertical uncertainty in meters,
                                      ///  with 1 decimal place

    bool               hSpeedUncertaintyValid; ///< if true, horizontal speed uncertainty is set
    uint32_t           hSpeedUncertainty;  ///< The horizontal speed uncertainty in m/sec,
                                           ///  with 1 decimal place

    bool               vSpeedUncertaintyValid; ///< if true, vertical speed uncertainty is set
    uint32_t           vSpeedUncertainty;  ///< The vertical speed uncertainty in m/sec,
                                           ///  with 1 decimal place

    bool               magneticDeviationValid; ///< if true, magnetic deviation is set
    int32_t            magneticDeviation;  ///< The magnetic deviation in degrees,
                                           ///  with 1 decimal place

    bool               directionUncertaintyValid;   ///< if true, direction uncertainty is set
    uint32_t           directionUncertainty;        ///< The direction uncertainty in degrees,
                                                    ///  with 1 decimal place
    // UTC time
    bool               timeValid;          ///< if true, time is set
    pa_Gnss_Time_t     time;               ///< The time of the fix
    uint64_t           epochTime;          ///< Epoch time in milliseconds since Jan. 1, 1970
    bool               dateValid;          ///< if true, date is set
    pa_Gnss_Date_t     date;               ///< The date of the fix
    // GPS time
    bool               gpsTimeValid;        ///< if true, GPS time is set
    uint32_t           gpsWeek;             ///< GPS week number from midnight, Jan. 6, 1980.
    uint32_t           gpsTimeOfWeek;       ///< Amount of time in milliseconds into the GPS week.
    // Time accuracy
    bool            timeAccuracyValid;      ///< if true, timeAccuracy is set
    uint32_t        timeAccuracy;           ///< Estimated Accuracy for time in milliseconds

    // Position measurement latency
    bool            positionLatencyValid;   ///< if true, positionLatency is set
    uint32_t        positionLatency;        ///< Position measurement latency in milliseconds

    // Satellite Vehicles information
    bool                satsInViewCountValid;    ///< if true, satsInView is set
    uint8_t             satsInViewCount;         ///< Satellites in View count.
    bool                satsTrackingCountValid;  ///< if true, satsTrackingCount is set
    uint8_t             satsTrackingCount;       ///< Tracking satellites in View.
    bool                satsUsedCountValid;      ///< if true, satsUsedCount is set
    uint8_t             satsUsedCount;           ///< Satellites in View used for Navigation.

    bool                satInfoValid;       ///< if true, satInfo is set
    Pa_Gnss_SvInfo_t    satInfo[LE_GNSS_SV_INFO_MAX_LEN];
                                            ///< Satellite Vehicle information.
    bool                    satMeasValid;   ///< if true, satInfo is set
    Pa_Gnss_SvMeasurement_t satMeas[LE_GNSS_SV_INFO_MAX_LEN];
                                            ///< Satellite measurement information.
}
pa_Gnss_Position_t;

//--------------------------------------------------------------------------------------------------
/**
 * Prototype for handler functions used to get GNSS position data.
 *
 * @param position The new position.
 */
//--------------------------------------------------------------------------------------------------
typedef void(*pa_gnss_PositionDataHandlerFunc_t)(pa_Gnss_Position_t* positionPtr);

//--------------------------------------------------------------------------------------------------
/**
 * Prototype for handler functions used to get NMEA frames.
 *
 * @param position The new position.
 */
//--------------------------------------------------------------------------------------------------
typedef void(*pa_gnss_NmeaHandlerFunc_t)(char* nmeaPtr);

//--------------------------------------------------------------------------------------------------
// APIs.
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to initialize the PA GNSS Module.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_Init
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to release the PA GNSS Module.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_Release
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the GNSS constellation bit mask
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 *  - LE_UNSUPPORTED request not supported
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_SetConstellation
(
    le_gnss_ConstellationBitMask_t constellationMask  ///< [IN] GNSS constellation used in solution.
);


//--------------------------------------------------------------------------------------------------
/**
 * Get the GNSS constellation bit mask
 *
* @return
*  - LE_OK on success
*  - LE_FAULT on failure
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetConstellation
(
    le_gnss_ConstellationBitMask_t *constellationMaskPtr ///< [OUT] GNSS constellation used
                                                         ///< in solution
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to start the GNSS acquisition.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_Start
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to stop the GNSS acquisition.
 *
 * @return LE_FAULT  The function failed.
 * @return LE_OK     The function succeed.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_Stop
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function sets the GNSS device acquisition rate.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 *  - LE_UNSUPPORTED request not supported
 *  - LE_TIMEOUT a time-out occurred
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_SetAcquisitionRate
(
    uint32_t rate     ///< [IN] rate in milliseconds
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to get the rate of GNSS fix reception
 *
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetAcquisitionRate
(
    uint32_t* ratePtr     ///< [IN] rate in milliseconds
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to register an handler for GNSS position data notifications.
 *
 * @return A handler reference, which is only needed for later removal of the handler.
 *
 * @note Doesn't return on failure, so there's no need to check the return value for errors.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_event_HandlerRef_t pa_gnss_AddPositionDataHandler
(
    pa_gnss_PositionDataHandlerFunc_t handler ///< [IN] The handler function.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to remove a handler for GNSS position data notifications.
 *
 * @note Doesn't return on failure, so there's no need to check the return value for errors.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void pa_gnss_RemovePositionDataHandler
(
    le_event_HandlerRef_t    handlerRef ///< [IN] The handler reference.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to register an handler for NMEA frames notifications.
 *
 * @return A handler reference, which is only needed for later removal of the handler.
 *
 * @note Doesn't return on failure, so there's no need to check the return value for errors.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_event_HandlerRef_t pa_gnss_AddNmeaHandler
(
    pa_gnss_NmeaHandlerFunc_t handler ///< [IN] The handler function.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to remove a handler for NMEA frames notifications.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void pa_gnss_RemoveNmeaHandler
(
    le_event_HandlerRef_t    handlerRef ///< [IN] The handler reference.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to load an 'Extended Ephemeris' file into the GNSS device.
 *
 * @return LE_FAULT         The function failed to inject the 'Extended Ephemeris' file.
 * @return LE_TIMEOUT       A time-out occurred.
 * @return LE_FORMAT_ERROR  'Extended Ephemeris' file format error.
 * @return LE_OK            The function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_LoadExtendedEphemerisFile
(
    int32_t       fd      ///< [IN] extended ephemeris file descriptor
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to get the validity of the last injected Extended Ephemeris.
 *
 * @return LE_FAULT         The function failed to get the validity
 * @return LE_OK            The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetExtendedEphemerisValidity
(
    uint64_t *startTimePtr,    ///< [OUT] Start time in seconds (since Jan. 1, 1970)
    uint64_t *stopTimePtr      ///< [OUT] Stop time in seconds (since Jan. 1, 1970)
);

//--------------------------------------------------------------------------------------------------
/**
 * This function enables the use of the 'Extended Ephemeris' file into the GNSS device.
 *
 * @return LE_FAULT         The function failed to enable the 'Extended Ephemeris' file.
 * @return LE_OK            The function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_EnableExtendedEphemerisFile
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function disables the use of the 'Extended Ephemeris' file into the GNSS device.
 *
 * @return LE_FAULT         The function failed to disable the 'Extended Ephemeris' file.
 * @return LE_OK            The function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_DisableExtendedEphemerisFile
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to restart the GNSS device.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_ForceRestart
(
    pa_gnss_Restart_t  restartType ///< [IN] type of restart
);

//--------------------------------------------------------------------------------------------------
/**
 * Get the TTFF in milliseconds.
 *
 * @return LE_BUSY          The position is not fixed and TTFF can't be measured.
 * @return LE_OK            The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetTtff
(
    uint32_t* ttffPtr     ///< [OUT] TTFF in milliseconds
);

//--------------------------------------------------------------------------------------------------
/**
 * This function enables the GNSS device.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_Enable
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function disables the GNSS device.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_Disable
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function sets the SUPL Assisted-GNSS mode.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 *  - LE_UNSUPPORTED request not supported
 *  - LE_TIMEOUT a time-out occurred
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_SetSuplAssistedMode
(
    le_gnss_AssistedMode_t  assistedMode      ///< [IN] Assisted-GNSS mode.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function gets the SUPL Assisted-GNSS mode.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetSuplAssistedMode
(
    le_gnss_AssistedMode_t *assistedModePtr      ///< [OUT] Assisted-GNSS mode.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function sets the SUPL server URL.
 * That server URL is a NULL-terminated string with a maximum string length (including NULL
 * terminator) equal to 256. Optionally the port number is specified after a colon.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 *  - LE_BUSY service is busy
 *  - LE_TIMEOUT a time-out occurred
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_SetSuplServerUrl
(
    const char*  suplServerUrlPtr      ///< [IN] SUPL server URL.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function injects the SUPL certificate to be used in A-GNSS sessions.
 *
 * @return
 *  - LE_OK on success
 *  - LE_BAD_PARAMETER on invalid parameter
 *  - LE_FAULT on failure
 *  - LE_BUSY service is busy
 *  - LE_TIMEOUT a time-out occurred
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_InjectSuplCertificate
(
    uint8_t  suplCertificateId,      ///< [IN] ID of the SUPL certificate.
                                     ///< Certificate ID range is 0 to 9
    uint16_t suplCertificateLen,     ///< [IN] SUPL certificate size in Bytes.
    const char*  suplCertificatePtr  ///< [IN] SUPL certificate contents.
);

//--------------------------------------------------------------------------------------------------
/**
 * This function deletes the SUPL certificate.
 *
 * @return
 *  - LE_OK on success
 *  - LE_BAD_PARAMETER on invalid parameter
 *  - LE_FAULT on failure
 *  - LE_BUSY service is busy
 *  - LE_TIMEOUT a time-out occurred
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_DeleteSuplCertificate
(
    uint8_t  suplCertificateId  ///< [IN]  ID of the SUPL certificate.
                                ///< Certificate ID range is 0 to 9
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the enabled NMEA sentences bit mask
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 *  - LE_UNSUPPORTED request not supported
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_SetNmeaSentences
(
    le_gnss_NmeaBitMask_t nmeaMask ///< [IN] Bit mask for enabled NMEA sentences.
);

//--------------------------------------------------------------------------------------------------
/**
 * Get the enabled NMEA sentences bit mask
 *
* @return
*  - LE_OK on success
*  - LE_FAULT on failure
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetNmeaSentences
(
    le_gnss_NmeaBitMask_t* nmeaMaskPtr ///< [OUT] Bit mask for enabled NMEA sentences.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the GNSS minimum elevation.
 *
 * @return
 *  - LE_OK on success
 *  - LE_FAULT on failure
 *  - LE_UNSUPPORTED request not supported
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_SetMinElevation
(
    uint8_t  minElevation      ///< [IN] Minimum elevation.
);

//--------------------------------------------------------------------------------------------------
/**
 *   Get the GNSS minimum elevation.
 *
* @return
*  - LE_OK on success
*  - LE_BAD_PARAMETER if minElevationPtr is NULL
*  - LE_FAULT on failure
*  - LE_UNSUPPORTED request not supported
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_gnss_GetMinElevation
(
   uint8_t*  minElevationPtr     ///< [OUT] Minimum elevation.
);

#endif // LEGATO_PA_GNSS_INCLUDE_GUARD
