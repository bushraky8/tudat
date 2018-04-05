/*    Copyright (c) 2010-2018, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 *
 *    References
 *      The Unified State Model: Derivation and Applications in Astrodynamics and Navigation,
 *          Vivek Vittaldevs; M.Sc. Thesis TU Delft (2010). Available on repository.tudelft.nl
 *
 */

#ifndef TUDAT_UNIFIED_STATE_MODEL_ELEMENT_CONVERSIONS_H
#define TUDAT_UNIFIED_STATE_MODEL_ELEMENT_CONVERSIONS_H

#include "Tudat/Basics/basicTypedefs.h"

namespace tudat
{

namespace orbital_element_conversions
{

//! Convert Keplerian to Unified State Model elements with Quaternions.
/*!
 * Converts Keplerian to Unified State Model elements with Quaternions.
 * \param keplerianElements Vector containing Keplerian elements. Order of elements is important!
 *         keplerianElements( 0 ) = semi-major axis,                                            [m]
 *         keplerianElements( 1 ) = eccentricity,                                               [-]
 *         keplerianElements( 2 ) = inclination (in range [0,PI]),                            [rad]
 *         keplerianElements( 3 ) = argument of periapsis,                                    [rad]
 *         keplerianElements( 4 ) = longitude of ascending node,                              [rad]
 *         keplerianElements( 5 ) = true anomaly.                                             [rad]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \return convertedUnifiedStateModelElements Converted state in Unified State Model elements with Quaternions.
 *         The order of elements is fixed
 *         convertedUnifiedStateModelElements( 0 ) = C hodograph element,                     [m/s]
 *         convertedUnifiedStateModelElements( 1 ) = Rf1 hodograph element,                   [m/s]
 *         convertedUnifiedStateModelElements( 2 ) = Rf1 hodograph element,                   [m/s]
 *         convertedUnifiedStateModelElements( 3 ) = epsilon1 quaternion element,               [-]
 *         convertedUnifiedStateModelElements( 4 ) = epsilon2 quaternion element,               [-]
 *         convertedUnifiedStateModelElements( 5 ) = epsilon3 quaternion element,               [-]
 *         convertedUnifiedStateModelElements( 6 ) = eta quaternion element.                    [-]
 */
Eigen::Matrix< double, 7, 1 > convertKeplerianToUnifiedStateModelWithQuaternionsElements(
        const Eigen::Matrix< double, 6, 1 >& keplerianElements,
        const double centralBodyGravitationalParameter );

//! Convert Unified State Model elements with Quaternions to Keplerian elements.
/*!
 * Converts Unified State Model elements with Quaternions to Keplerian elements.
 * \param unifiedStateModelElements Vector containing Unified State Model elements with Quaternions.
 *         Order of elements is important!
 *         unifiedStateModelElements( 0 ) = C hodograph element,                              [m/s]
 *         unifiedStateModelElements( 1 ) = Rf1 hodograph element,                            [m/s]
 *         unifiedStateModelElements( 2 ) = Rf1 hodograph element,                            [m/s]
 *         unifiedStateModelElements( 3 ) = epsilon1 quaternion element,                        [-]
 *         unifiedStateModelElements( 4 ) = epsilon2 quaternion element,                        [-]
 *         unifiedStateModelElements( 5 ) = epsilon3 quaternion element,                        [-]
 *         unifiedStateModelElements( 6 ) = eta quaternion element.                             [-]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \return convertedKeplerianElements Converted state in Keplerian elements. The order of elements is fixed!
 *         convertedKeplerianElements( 0 ) = semi-major axis,                                   [m]
 *         convertedKeplerianElements( 1 ) = eccentricity,                                      [-]
 *         convertedKeplerianElements( 2 ) = inclination (in range [0,PI]),                   [rad]
 *         convertedKeplerianElements( 3 ) = argument of periapsis,                           [rad]
 *         convertedKeplerianElements( 4 ) = longitude of ascending node,                     [rad]
 *         convertedKeplerianElements( 5 ) = true anomaly.                                    [rad]
 */
Eigen::Matrix< double, 6, 1 > convertUnifiedStateModelWithQuaternionsToKeplerianElements(
        const Eigen::Matrix< double, 7, 1 >& unifiedStateModelElements,
        const double centralBodyGravitationalParameter );

//! Convert Cartesian elements to Unified State Model elements with Quaternions.
/*!
 * Converts Cartesian to Unified State Model elements with Quaternions.
 * \param cartesianElements Converted state in Cartesian elements. The order of elements is fixed!
 *         cartesianElements( 0 ) = x-position coordinate,                                      [m]
 *         cartesianElements( 1 ) = y-position coordinate,                                      [m]
 *         cartesianElements( 2 ) = z-position coordinate,                                      [m]
 *         cartesianElements( 3 ) = x-velocity coordinate,                                    [m/s]
 *         cartesianElements( 4 ) = y-velocity coordinate,                                    [m/s]
 *         cartesianElements( 5 ) = z-velocity coordinate.                                    [m/s]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \return convertedUnifiedStateModelElements Converted state in Unified State Model elements with Quaternions.
 *         The order of elements is fixed
 *         convertedUnifiedStateModelElements( 0 ) = C hodograph element,                     [m/s]
 *         convertedUnifiedStateModelElements( 1 ) = Rf1 hodograph element,                   [m/s]
 *         convertedUnifiedStateModelElements( 2 ) = Rf1 hodograph element,                   [m/s]
 *         convertedUnifiedStateModelElements( 3 ) = epsilon1 quaternion element,               [-]
 *         convertedUnifiedStateModelElements( 4 ) = epsilon2 quaternion element,               [-]
 *         convertedUnifiedStateModelElements( 5 ) = epsilon3 quaternion element,               [-]
 *         convertedUnifiedStateModelElements( 6 ) = eta quaternion element.                    [-]
 */
template< typename ScalarType = double >
Eigen::Matrix< ScalarType, 7, 1 > convertCartesianToUnifiedStateModelWithQuaternionsElements(
        const Eigen::Matrix< ScalarType, 6, 1 >& cartesianElements,
        const ScalarType centralBodyGravitationalParameter )
{
    // Convert Cartesian to Keplerian elements.
    Eigen::Matrix< ScalarType, 6, 1 >  convertedKeplerianElements = convertCartesianToKeplerianElements< ScalarType >(
                cartesianElements, centralBodyGravitationalParameter );

    // Convert Keplerian elements to Unified State Model elements with Quaternions.
    return convertKeplerianToUnifiedStateModelWithQuaternionsElements(
                convertedKeplerianElements.template cast< double >( ), centralBodyGravitationalParameter ).
            template cast< ScalarType >( );
}

//! Convert Unified State Model elements with Quaternions to Cartesian elements.
/*!
* Converts Unified State Model elements with Quaternions to Cartesian elements.
* \param unifiedStateModelElements Vector containing Unified State Model elements with Quaternions.
*        Order of elements is important!
*         unifiedStateModelElements( 0 ) = C hodograph element,                              [m/s]
*         unifiedStateModelElements( 1 ) = Rf1 hodograph element,                            [m/s]
*         unifiedStateModelElements( 2 ) = Rf1 hodograph element,                            [m/s]
*         unifiedStateModelElements( 3 ) = epsilon1 quaternion element,                        [-]
*         unifiedStateModelElements( 4 ) = epsilon2 quaternion element,                        [-]
*         unifiedStateModelElements( 5 ) = epsilon3 quaternion element,                        [-]
*         unifiedStateModelElements( 6 ) = eta quaternion element.                             [-]
* \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
* \return convertedCartesianElements Converted state in Cartesian elements. The order of elements is fixed!
 *         convertedCartesianElements( 0 ) = x-position coordinate,                            [m]
 *         convertedCartesianElements( 1 ) = y-position coordinate,                            [m]
 *         convertedCartesianElements( 2 ) = z-position coordinate,                            [m]
 *         convertedCartesianElements( 3 ) = x-velocity coordinate,                          [m/s]
 *         convertedCartesianElements( 4 ) = y-velocity coordinate,                          [m/s]
 *         convertedCartesianElements( 5 ) = z-velocity coordinate.                          [m/s]
*/
template< typename ScalarType = double >
Eigen::Matrix< ScalarType, 6, 1 > convertUnifiedStateModelWithQuaternionsToCartesianElements(
        const Eigen::Matrix< ScalarType, 7, 1 >& unifiedStateModelElements,
        const ScalarType centralBodyGravitationalParameter )
{
    // Declaring eventual output vector.
    Eigen::Matrix< ScalarType, 6, 1 > convertedCartesianElements = Eigen::Matrix< ScalarType, 6, 1 >::Zero( );

    // Convert Unified State Model with Quaternions to Keplerian elements.
    Eigen::Matrix< ScalarType, 6, 1 > convertedKeplerianElements =
            convertUnifiedStateModelWithQuaternionsToKeplerianElements(
                unifiedStateModelElements.template cast< double >( ), centralBodyGravitationalParameter ).template cast< ScalarType >( );

    // Convert Keplerian elements to Cartesian elements.
    return convertedCartesianElements = convertKeplerianToCartesianElements(
                convertedKeplerianElements, centralBodyGravitationalParameter );
}

} // namespace orbital_element_conversions

} // close tudat

#endif // TUDAT_UNIFIED_STATE_MODEL_ELEMENT_CONVERSIONS_H
