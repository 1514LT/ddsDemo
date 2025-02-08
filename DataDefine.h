// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file DataDefine.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef _FAST_DDS_GENERATED_DATADEFINE_H_
#define _FAST_DDS_GENERATED_DATADEFINE_H_

#include <array>
#include <bitset>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <fastcdr/cdr/fixed_size_string.hpp>
#include <fastcdr/xcdr/external.hpp>
#include <fastcdr/xcdr/optional.hpp>



#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(DATADEFINE_SOURCE)
#define DATADEFINE_DllAPI __declspec( dllexport )
#else
#define DATADEFINE_DllAPI __declspec( dllimport )
#endif // DATADEFINE_SOURCE
#else
#define DATADEFINE_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define DATADEFINE_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
class CdrSizeCalculator;
} // namespace fastcdr
} // namespace eprosima





/*!
 * @brief This class represents the structure Target defined by the user in the IDL file.
 * @ingroup DataDefine
 */
class Target
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport Target();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~Target();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object Target that will be copied.
     */
    eProsima_user_DllExport Target(
            const Target& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object Target that will be copied.
     */
    eProsima_user_DllExport Target(
            Target&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object Target that will be copied.
     */
    eProsima_user_DllExport Target& operator =(
            const Target& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object Target that will be copied.
     */
    eProsima_user_DllExport Target& operator =(
            Target&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x Target object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const Target& x) const;

    /*!
     * @brief Comparison operator.
     * @param x Target object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const Target& x) const;

    /*!
     * @brief This function sets a value in member targetNumber
     * @param _targetNumber New value for member targetNumber
     */
    eProsima_user_DllExport void targetNumber(
            uint16_t _targetNumber);

    /*!
     * @brief This function returns the value of member targetNumber
     * @return Value of member targetNumber
     */
    eProsima_user_DllExport uint16_t targetNumber() const;

    /*!
     * @brief This function returns a reference to member targetNumber
     * @return Reference to member targetNumber
     */
    eProsima_user_DllExport uint16_t& targetNumber();


    /*!
     * @brief This function copies the value in member time
     * @param _time New value to be copied in member time
     */
    eProsima_user_DllExport void time(
            const std::array<uint8_t, 6>& _time);

    /*!
     * @brief This function moves the value in member time
     * @param _time New value to be moved in member time
     */
    eProsima_user_DllExport void time(
            std::array<uint8_t, 6>&& _time);

    /*!
     * @brief This function returns a constant reference to member time
     * @return Constant reference to member time
     */
    eProsima_user_DllExport const std::array<uint8_t, 6>& time() const;

    /*!
     * @brief This function returns a reference to member time
     * @return Reference to member time
     */
    eProsima_user_DllExport std::array<uint8_t, 6>& time();


    /*!
     * @brief This function sets a value in member longitude
     * @param _longitude New value for member longitude
     */
    eProsima_user_DllExport void longitude(
            int32_t _longitude);

    /*!
     * @brief This function returns the value of member longitude
     * @return Value of member longitude
     */
    eProsima_user_DllExport int32_t longitude() const;

    /*!
     * @brief This function returns a reference to member longitude
     * @return Reference to member longitude
     */
    eProsima_user_DllExport int32_t& longitude();


    /*!
     * @brief This function sets a value in member latitude
     * @param _latitude New value for member latitude
     */
    eProsima_user_DllExport void latitude(
            int32_t _latitude);

    /*!
     * @brief This function returns the value of member latitude
     * @return Value of member latitude
     */
    eProsima_user_DllExport int32_t latitude() const;

    /*!
     * @brief This function returns a reference to member latitude
     * @return Reference to member latitude
     */
    eProsima_user_DllExport int32_t& latitude();


    /*!
     * @brief This function sets a value in member elevation
     * @param _elevation New value for member elevation
     */
    eProsima_user_DllExport void elevation(
            uint16_t _elevation);

    /*!
     * @brief This function returns the value of member elevation
     * @return Value of member elevation
     */
    eProsima_user_DllExport uint16_t elevation() const;

    /*!
     * @brief This function returns a reference to member elevation
     * @return Reference to member elevation
     */
    eProsima_user_DllExport uint16_t& elevation();


    /*!
     * @brief This function sets a value in member Priority
     * @param _Priority New value for member Priority
     */
    eProsima_user_DllExport void Priority(
            uint8_t _Priority);

    /*!
     * @brief This function returns the value of member Priority
     * @return Value of member Priority
     */
    eProsima_user_DllExport uint8_t Priority() const;

    /*!
     * @brief This function returns a reference to member Priority
     * @return Reference to member Priority
     */
    eProsima_user_DllExport uint8_t& Priority();


    /*!
     * @brief This function sets a value in member confidenceDegree
     * @param _confidenceDegree New value for member confidenceDegree
     */
    eProsima_user_DllExport void confidenceDegree(
            uint8_t _confidenceDegree);

    /*!
     * @brief This function returns the value of member confidenceDegree
     * @return Value of member confidenceDegree
     */
    eProsima_user_DllExport uint8_t confidenceDegree() const;

    /*!
     * @brief This function returns a reference to member confidenceDegree
     * @return Reference to member confidenceDegree
     */
    eProsima_user_DllExport uint8_t& confidenceDegree();


    /*!
     * @brief This function sets a value in member informationType
     * @param _informationType New value for member informationType
     */
    eProsima_user_DllExport void informationType(
            uint8_t _informationType);

    /*!
     * @brief This function returns the value of member informationType
     * @return Value of member informationType
     */
    eProsima_user_DllExport uint8_t informationType() const;

    /*!
     * @brief This function returns a reference to member informationType
     * @return Reference to member informationType
     */
    eProsima_user_DllExport uint8_t& informationType();


    /*!
     * @brief This function sets a value in member positionAccuracy
     * @param _positionAccuracy New value for member positionAccuracy
     */
    eProsima_user_DllExport void positionAccuracy(
            uint8_t _positionAccuracy);

    /*!
     * @brief This function returns the value of member positionAccuracy
     * @return Value of member positionAccuracy
     */
    eProsima_user_DllExport uint8_t positionAccuracy() const;

    /*!
     * @brief This function returns a reference to member positionAccuracy
     * @return Reference to member positionAccuracy
     */
    eProsima_user_DllExport uint8_t& positionAccuracy();


    /*!
     * @brief This function sets a value in member imagingMode
     * @param _imagingMode New value for member imagingMode
     */
    eProsima_user_DllExport void imagingMode(
            uint8_t _imagingMode);

    /*!
     * @brief This function returns the value of member imagingMode
     * @return Value of member imagingMode
     */
    eProsima_user_DllExport uint8_t imagingMode() const;

    /*!
     * @brief This function returns a reference to member imagingMode
     * @return Reference to member imagingMode
     */
    eProsima_user_DllExport uint8_t& imagingMode();


    /*!
     * @brief This function sets a value in member desiredTrack
     * @param _desiredTrack New value for member desiredTrack
     */
    eProsima_user_DllExport void desiredTrack(
            uint16_t _desiredTrack);

    /*!
     * @brief This function returns the value of member desiredTrack
     * @return Value of member desiredTrack
     */
    eProsima_user_DllExport uint16_t desiredTrack() const;

    /*!
     * @brief This function returns a reference to member desiredTrack
     * @return Reference to member desiredTrack
     */
    eProsima_user_DllExport uint16_t& desiredTrack();


    /*!
     * @brief This function sets a value in member shipSpeed
     * @param _shipSpeed New value for member shipSpeed
     */
    eProsima_user_DllExport void shipSpeed(
            uint16_t _shipSpeed);

    /*!
     * @brief This function returns the value of member shipSpeed
     * @return Value of member shipSpeed
     */
    eProsima_user_DllExport uint16_t shipSpeed() const;

    /*!
     * @brief This function returns a reference to member shipSpeed
     * @return Reference to member shipSpeed
     */
    eProsima_user_DllExport uint16_t& shipSpeed();


    /*!
     * @brief This function copies the value in member back
     * @param _back New value to be copied in member back
     */
    eProsima_user_DllExport void back(
            const std::array<uint8_t, 5>& _back);

    /*!
     * @brief This function moves the value in member back
     * @param _back New value to be moved in member back
     */
    eProsima_user_DllExport void back(
            std::array<uint8_t, 5>&& _back);

    /*!
     * @brief This function returns a constant reference to member back
     * @return Constant reference to member back
     */
    eProsima_user_DllExport const std::array<uint8_t, 5>& back() const;

    /*!
     * @brief This function returns a reference to member back
     * @return Reference to member back
     */
    eProsima_user_DllExport std::array<uint8_t, 5>& back();

private:

    uint16_t m_targetNumber{0};
    std::array<uint8_t, 6> m_time{0};
    int32_t m_longitude{0};
    int32_t m_latitude{0};
    uint16_t m_elevation{0};
    uint8_t m_Priority{0};
    uint8_t m_confidenceDegree{0};
    uint8_t m_informationType{0};
    uint8_t m_positionAccuracy{0};
    uint8_t m_imagingMode{0};
    uint16_t m_desiredTrack{0};
    uint16_t m_shipSpeed{0};
    std::array<uint8_t, 5> m_back{0};

};


/*!
 * @brief This class represents the structure GuidanceInfo defined by the user in the IDL file.
 * @ingroup DataDefine
 */
class GuidanceInfo
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport GuidanceInfo();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~GuidanceInfo();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object GuidanceInfo that will be copied.
     */
    eProsima_user_DllExport GuidanceInfo(
            const GuidanceInfo& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object GuidanceInfo that will be copied.
     */
    eProsima_user_DllExport GuidanceInfo(
            GuidanceInfo&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object GuidanceInfo that will be copied.
     */
    eProsima_user_DllExport GuidanceInfo& operator =(
            const GuidanceInfo& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object GuidanceInfo that will be copied.
     */
    eProsima_user_DllExport GuidanceInfo& operator =(
            GuidanceInfo&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x GuidanceInfo object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const GuidanceInfo& x) const;

    /*!
     * @brief Comparison operator.
     * @param x GuidanceInfo object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const GuidanceInfo& x) const;

    /*!
     * @brief This function sets a value in member beatCount
     * @param _beatCount New value for member beatCount
     */
    eProsima_user_DllExport void beatCount(
            uint16_t _beatCount);

    /*!
     * @brief This function returns the value of member beatCount
     * @return Value of member beatCount
     */
    eProsima_user_DllExport uint16_t beatCount() const;

    /*!
     * @brief This function returns a reference to member beatCount
     * @return Reference to member beatCount
     */
    eProsima_user_DllExport uint16_t& beatCount();


    /*!
     * @brief This function sets a value in member targetCount
     * @param _targetCount New value for member targetCount
     */
    eProsima_user_DllExport void targetCount(
            uint8_t _targetCount);

    /*!
     * @brief This function returns the value of member targetCount
     * @return Value of member targetCount
     */
    eProsima_user_DllExport uint8_t targetCount() const;

    /*!
     * @brief This function returns a reference to member targetCount
     * @return Reference to member targetCount
     */
    eProsima_user_DllExport uint8_t& targetCount();


    /*!
     * @brief This function sets a value in member node
     * @param _node New value for member node
     */
    eProsima_user_DllExport void node(
            uint16_t _node);

    /*!
     * @brief This function returns the value of member node
     * @return Value of member node
     */
    eProsima_user_DllExport uint16_t node() const;

    /*!
     * @brief This function returns a reference to member node
     * @return Reference to member node
     */
    eProsima_user_DllExport uint16_t& node();


    /*!
     * @brief This function sets a value in member targetType
     * @param _targetType New value for member targetType
     */
    eProsima_user_DllExport void targetType(
            uint8_t _targetType);

    /*!
     * @brief This function returns the value of member targetType
     * @return Value of member targetType
     */
    eProsima_user_DllExport uint8_t targetType() const;

    /*!
     * @brief This function returns a reference to member targetType
     * @return Reference to member targetType
     */
    eProsima_user_DllExport uint8_t& targetType();


    /*!
     * @brief This function copies the value in member First
     * @param _First New value to be copied in member First
     */
    eProsima_user_DllExport void First(
            const Target& _First);

    /*!
     * @brief This function moves the value in member First
     * @param _First New value to be moved in member First
     */
    eProsima_user_DllExport void First(
            Target&& _First);

    /*!
     * @brief This function returns a constant reference to member First
     * @return Constant reference to member First
     */
    eProsima_user_DllExport const Target& First() const;

    /*!
     * @brief This function returns a reference to member First
     * @return Reference to member First
     */
    eProsima_user_DllExport Target& First();


    /*!
     * @brief This function copies the value in member Second
     * @param _Second New value to be copied in member Second
     */
    eProsima_user_DllExport void Second(
            const Target& _Second);

    /*!
     * @brief This function moves the value in member Second
     * @param _Second New value to be moved in member Second
     */
    eProsima_user_DllExport void Second(
            Target&& _Second);

    /*!
     * @brief This function returns a constant reference to member Second
     * @return Constant reference to member Second
     */
    eProsima_user_DllExport const Target& Second() const;

    /*!
     * @brief This function returns a reference to member Second
     * @return Reference to member Second
     */
    eProsima_user_DllExport Target& Second();


    /*!
     * @brief This function copies the value in member Third
     * @param _Third New value to be copied in member Third
     */
    eProsima_user_DllExport void Third(
            const Target& _Third);

    /*!
     * @brief This function moves the value in member Third
     * @param _Third New value to be moved in member Third
     */
    eProsima_user_DllExport void Third(
            Target&& _Third);

    /*!
     * @brief This function returns a constant reference to member Third
     * @return Constant reference to member Third
     */
    eProsima_user_DllExport const Target& Third() const;

    /*!
     * @brief This function returns a reference to member Third
     * @return Reference to member Third
     */
    eProsima_user_DllExport Target& Third();


    /*!
     * @brief This function copies the value in member Fourth
     * @param _Fourth New value to be copied in member Fourth
     */
    eProsima_user_DllExport void Fourth(
            const Target& _Fourth);

    /*!
     * @brief This function moves the value in member Fourth
     * @param _Fourth New value to be moved in member Fourth
     */
    eProsima_user_DllExport void Fourth(
            Target&& _Fourth);

    /*!
     * @brief This function returns a constant reference to member Fourth
     * @return Constant reference to member Fourth
     */
    eProsima_user_DllExport const Target& Fourth() const;

    /*!
     * @brief This function returns a reference to member Fourth
     * @return Reference to member Fourth
     */
    eProsima_user_DllExport Target& Fourth();


    /*!
     * @brief This function copies the value in member Fifth
     * @param _Fifth New value to be copied in member Fifth
     */
    eProsima_user_DllExport void Fifth(
            const Target& _Fifth);

    /*!
     * @brief This function moves the value in member Fifth
     * @param _Fifth New value to be moved in member Fifth
     */
    eProsima_user_DllExport void Fifth(
            Target&& _Fifth);

    /*!
     * @brief This function returns a constant reference to member Fifth
     * @return Constant reference to member Fifth
     */
    eProsima_user_DllExport const Target& Fifth() const;

    /*!
     * @brief This function returns a reference to member Fifth
     * @return Reference to member Fifth
     */
    eProsima_user_DllExport Target& Fifth();

private:

    uint16_t m_beatCount{0};
    uint8_t m_targetCount{0};
    uint16_t m_node{0};
    uint8_t m_targetType{0};
    Target m_First;
    Target m_Second;
    Target m_Third;
    Target m_Fourth;
    Target m_Fifth;

};


/*!
 * @brief This class represents the structure ReplyInfo defined by the user in the IDL file.
 * @ingroup DataDefine
 */
class ReplyInfo
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport ReplyInfo();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~ReplyInfo();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object ReplyInfo that will be copied.
     */
    eProsima_user_DllExport ReplyInfo(
            const ReplyInfo& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object ReplyInfo that will be copied.
     */
    eProsima_user_DllExport ReplyInfo(
            ReplyInfo&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object ReplyInfo that will be copied.
     */
    eProsima_user_DllExport ReplyInfo& operator =(
            const ReplyInfo& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object ReplyInfo that will be copied.
     */
    eProsima_user_DllExport ReplyInfo& operator =(
            ReplyInfo&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x ReplyInfo object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const ReplyInfo& x) const;

    /*!
     * @brief Comparison operator.
     * @param x ReplyInfo object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const ReplyInfo& x) const;

    /*!
     * @brief This function sets a value in member targetNumber
     * @param _targetNumber New value for member targetNumber
     */
    eProsima_user_DllExport void targetNumber(
            uint16_t _targetNumber);

    /*!
     * @brief This function returns the value of member targetNumber
     * @return Value of member targetNumber
     */
    eProsima_user_DllExport uint16_t targetNumber() const;

    /*!
     * @brief This function returns a reference to member targetNumber
     * @return Reference to member targetNumber
     */
    eProsima_user_DllExport uint16_t& targetNumber();


    /*!
     * @brief This function sets a value in member handleNumber
     * @param _handleNumber New value for member handleNumber
     */
    eProsima_user_DllExport void handleNumber(
            uint16_t _handleNumber);

    /*!
     * @brief This function returns the value of member handleNumber
     * @return Value of member handleNumber
     */
    eProsima_user_DllExport uint16_t handleNumber() const;

    /*!
     * @brief This function returns a reference to member handleNumber
     * @return Reference to member handleNumber
     */
    eProsima_user_DllExport uint16_t& handleNumber();


    /*!
     * @brief This function sets a value in member sucessNumber
     * @param _sucessNumber New value for member sucessNumber
     */
    eProsima_user_DllExport void sucessNumber(
            uint16_t _sucessNumber);

    /*!
     * @brief This function returns the value of member sucessNumber
     * @return Value of member sucessNumber
     */
    eProsima_user_DllExport uint16_t sucessNumber() const;

    /*!
     * @brief This function returns a reference to member sucessNumber
     * @return Reference to member sucessNumber
     */
    eProsima_user_DllExport uint16_t& sucessNumber();


    /*!
     * @brief This function sets a value in member executionNumber
     * @param _executionNumber New value for member executionNumber
     */
    eProsima_user_DllExport void executionNumber(
            uint16_t _executionNumber);

    /*!
     * @brief This function returns the value of member executionNumber
     * @return Value of member executionNumber
     */
    eProsima_user_DllExport uint16_t executionNumber() const;

    /*!
     * @brief This function returns a reference to member executionNumber
     * @return Reference to member executionNumber
     */
    eProsima_user_DllExport uint16_t& executionNumber();


    /*!
     * @brief This function sets a value in member ownTargetNumber
     * @param _ownTargetNumber New value for member ownTargetNumber
     */
    eProsima_user_DllExport void ownTargetNumber(
            uint16_t _ownTargetNumber);

    /*!
     * @brief This function returns the value of member ownTargetNumber
     * @return Value of member ownTargetNumber
     */
    eProsima_user_DllExport uint16_t ownTargetNumber() const;

    /*!
     * @brief This function returns a reference to member ownTargetNumber
     * @return Reference to member ownTargetNumber
     */
    eProsima_user_DllExport uint16_t& ownTargetNumber();


    /*!
     * @brief This function sets a value in member number1
     * @param _number1 New value for member number1
     */
    eProsima_user_DllExport void number1(
            uint16_t _number1);

    /*!
     * @brief This function returns the value of member number1
     * @return Value of member number1
     */
    eProsima_user_DllExport uint16_t number1() const;

    /*!
     * @brief This function returns a reference to member number1
     * @return Reference to member number1
     */
    eProsima_user_DllExport uint16_t& number1();


    /*!
     * @brief This function sets a value in member resultNumer1
     * @param _resultNumer1 New value for member resultNumer1
     */
    eProsima_user_DllExport void resultNumer1(
            uint16_t _resultNumer1);

    /*!
     * @brief This function returns the value of member resultNumer1
     * @return Value of member resultNumer1
     */
    eProsima_user_DllExport uint16_t resultNumer1() const;

    /*!
     * @brief This function returns a reference to member resultNumer1
     * @return Reference to member resultNumer1
     */
    eProsima_user_DllExport uint16_t& resultNumer1();


    /*!
     * @brief This function sets a value in member number2
     * @param _number2 New value for member number2
     */
    eProsima_user_DllExport void number2(
            uint16_t _number2);

    /*!
     * @brief This function returns the value of member number2
     * @return Value of member number2
     */
    eProsima_user_DllExport uint16_t number2() const;

    /*!
     * @brief This function returns a reference to member number2
     * @return Reference to member number2
     */
    eProsima_user_DllExport uint16_t& number2();


    /*!
     * @brief This function sets a value in member resultNumer2
     * @param _resultNumer2 New value for member resultNumer2
     */
    eProsima_user_DllExport void resultNumer2(
            uint16_t _resultNumer2);

    /*!
     * @brief This function returns the value of member resultNumer2
     * @return Value of member resultNumer2
     */
    eProsima_user_DllExport uint16_t resultNumer2() const;

    /*!
     * @brief This function returns a reference to member resultNumer2
     * @return Reference to member resultNumer2
     */
    eProsima_user_DllExport uint16_t& resultNumer2();


    /*!
     * @brief This function sets a value in member number3
     * @param _number3 New value for member number3
     */
    eProsima_user_DllExport void number3(
            uint16_t _number3);

    /*!
     * @brief This function returns the value of member number3
     * @return Value of member number3
     */
    eProsima_user_DllExport uint16_t number3() const;

    /*!
     * @brief This function returns a reference to member number3
     * @return Reference to member number3
     */
    eProsima_user_DllExport uint16_t& number3();


    /*!
     * @brief This function sets a value in member resultNumer3
     * @param _resultNumer3 New value for member resultNumer3
     */
    eProsima_user_DllExport void resultNumer3(
            uint16_t _resultNumer3);

    /*!
     * @brief This function returns the value of member resultNumer3
     * @return Value of member resultNumer3
     */
    eProsima_user_DllExport uint16_t resultNumer3() const;

    /*!
     * @brief This function returns a reference to member resultNumer3
     * @return Reference to member resultNumer3
     */
    eProsima_user_DllExport uint16_t& resultNumer3();


    /*!
     * @brief This function sets a value in member number4
     * @param _number4 New value for member number4
     */
    eProsima_user_DllExport void number4(
            uint16_t _number4);

    /*!
     * @brief This function returns the value of member number4
     * @return Value of member number4
     */
    eProsima_user_DllExport uint16_t number4() const;

    /*!
     * @brief This function returns a reference to member number4
     * @return Reference to member number4
     */
    eProsima_user_DllExport uint16_t& number4();


    /*!
     * @brief This function sets a value in member resultNumer4
     * @param _resultNumer4 New value for member resultNumer4
     */
    eProsima_user_DllExport void resultNumer4(
            uint16_t _resultNumer4);

    /*!
     * @brief This function returns the value of member resultNumer4
     * @return Value of member resultNumer4
     */
    eProsima_user_DllExport uint16_t resultNumer4() const;

    /*!
     * @brief This function returns a reference to member resultNumer4
     * @return Reference to member resultNumer4
     */
    eProsima_user_DllExport uint16_t& resultNumer4();


    /*!
     * @brief This function sets a value in member number5
     * @param _number5 New value for member number5
     */
    eProsima_user_DllExport void number5(
            uint16_t _number5);

    /*!
     * @brief This function returns the value of member number5
     * @return Value of member number5
     */
    eProsima_user_DllExport uint16_t number5() const;

    /*!
     * @brief This function returns a reference to member number5
     * @return Reference to member number5
     */
    eProsima_user_DllExport uint16_t& number5();


    /*!
     * @brief This function sets a value in member resultNumer5
     * @param _resultNumer5 New value for member resultNumer5
     */
    eProsima_user_DllExport void resultNumer5(
            uint16_t _resultNumer5);

    /*!
     * @brief This function returns the value of member resultNumer5
     * @return Value of member resultNumer5
     */
    eProsima_user_DllExport uint16_t resultNumer5() const;

    /*!
     * @brief This function returns a reference to member resultNumer5
     * @return Reference to member resultNumer5
     */
    eProsima_user_DllExport uint16_t& resultNumer5();


    /*!
     * @brief This function sets a value in member number6
     * @param _number6 New value for member number6
     */
    eProsima_user_DllExport void number6(
            uint16_t _number6);

    /*!
     * @brief This function returns the value of member number6
     * @return Value of member number6
     */
    eProsima_user_DllExport uint16_t number6() const;

    /*!
     * @brief This function returns a reference to member number6
     * @return Reference to member number6
     */
    eProsima_user_DllExport uint16_t& number6();


    /*!
     * @brief This function sets a value in member resultNumer6
     * @param _resultNumer6 New value for member resultNumer6
     */
    eProsima_user_DllExport void resultNumer6(
            uint16_t _resultNumer6);

    /*!
     * @brief This function returns the value of member resultNumer6
     * @return Value of member resultNumer6
     */
    eProsima_user_DllExport uint16_t resultNumer6() const;

    /*!
     * @brief This function returns a reference to member resultNumer6
     * @return Reference to member resultNumer6
     */
    eProsima_user_DllExport uint16_t& resultNumer6();


    /*!
     * @brief This function sets a value in member number7
     * @param _number7 New value for member number7
     */
    eProsima_user_DllExport void number7(
            uint16_t _number7);

    /*!
     * @brief This function returns the value of member number7
     * @return Value of member number7
     */
    eProsima_user_DllExport uint16_t number7() const;

    /*!
     * @brief This function returns a reference to member number7
     * @return Reference to member number7
     */
    eProsima_user_DllExport uint16_t& number7();


    /*!
     * @brief This function sets a value in member resultNumer7
     * @param _resultNumer7 New value for member resultNumer7
     */
    eProsima_user_DllExport void resultNumer7(
            uint16_t _resultNumer7);

    /*!
     * @brief This function returns the value of member resultNumer7
     * @return Value of member resultNumer7
     */
    eProsima_user_DllExport uint16_t resultNumer7() const;

    /*!
     * @brief This function returns a reference to member resultNumer7
     * @return Reference to member resultNumer7
     */
    eProsima_user_DllExport uint16_t& resultNumer7();


    /*!
     * @brief This function sets a value in member number8
     * @param _number8 New value for member number8
     */
    eProsima_user_DllExport void number8(
            uint16_t _number8);

    /*!
     * @brief This function returns the value of member number8
     * @return Value of member number8
     */
    eProsima_user_DllExport uint16_t number8() const;

    /*!
     * @brief This function returns a reference to member number8
     * @return Reference to member number8
     */
    eProsima_user_DllExport uint16_t& number8();


    /*!
     * @brief This function sets a value in member resultNumer8
     * @param _resultNumer8 New value for member resultNumer8
     */
    eProsima_user_DllExport void resultNumer8(
            uint16_t _resultNumer8);

    /*!
     * @brief This function returns the value of member resultNumer8
     * @return Value of member resultNumer8
     */
    eProsima_user_DllExport uint16_t resultNumer8() const;

    /*!
     * @brief This function returns a reference to member resultNumer8
     * @return Reference to member resultNumer8
     */
    eProsima_user_DllExport uint16_t& resultNumer8();


    /*!
     * @brief This function sets a value in member number9
     * @param _number9 New value for member number9
     */
    eProsima_user_DllExport void number9(
            uint16_t _number9);

    /*!
     * @brief This function returns the value of member number9
     * @return Value of member number9
     */
    eProsima_user_DllExport uint16_t number9() const;

    /*!
     * @brief This function returns a reference to member number9
     * @return Reference to member number9
     */
    eProsima_user_DllExport uint16_t& number9();


    /*!
     * @brief This function sets a value in member resultNumer9
     * @param _resultNumer9 New value for member resultNumer9
     */
    eProsima_user_DllExport void resultNumer9(
            uint16_t _resultNumer9);

    /*!
     * @brief This function returns the value of member resultNumer9
     * @return Value of member resultNumer9
     */
    eProsima_user_DllExport uint16_t resultNumer9() const;

    /*!
     * @brief This function returns a reference to member resultNumer9
     * @return Reference to member resultNumer9
     */
    eProsima_user_DllExport uint16_t& resultNumer9();


    /*!
     * @brief This function sets a value in member number10
     * @param _number10 New value for member number10
     */
    eProsima_user_DllExport void number10(
            uint16_t _number10);

    /*!
     * @brief This function returns the value of member number10
     * @return Value of member number10
     */
    eProsima_user_DllExport uint16_t number10() const;

    /*!
     * @brief This function returns a reference to member number10
     * @return Reference to member number10
     */
    eProsima_user_DllExport uint16_t& number10();


    /*!
     * @brief This function sets a value in member resultNumer10
     * @param _resultNumer10 New value for member resultNumer10
     */
    eProsima_user_DllExport void resultNumer10(
            uint16_t _resultNumer10);

    /*!
     * @brief This function returns the value of member resultNumer10
     * @return Value of member resultNumer10
     */
    eProsima_user_DllExport uint16_t resultNumer10() const;

    /*!
     * @brief This function returns a reference to member resultNumer10
     * @return Reference to member resultNumer10
     */
    eProsima_user_DllExport uint16_t& resultNumer10();

private:

    uint16_t m_targetNumber{0};
    uint16_t m_handleNumber{0};
    uint16_t m_sucessNumber{0};
    uint16_t m_executionNumber{0};
    uint16_t m_ownTargetNumber{0};
    uint16_t m_number1{0};
    uint16_t m_resultNumer1{0};
    uint16_t m_number2{0};
    uint16_t m_resultNumer2{0};
    uint16_t m_number3{0};
    uint16_t m_resultNumer3{0};
    uint16_t m_number4{0};
    uint16_t m_resultNumer4{0};
    uint16_t m_number5{0};
    uint16_t m_resultNumer5{0};
    uint16_t m_number6{0};
    uint16_t m_resultNumer6{0};
    uint16_t m_number7{0};
    uint16_t m_resultNumer7{0};
    uint16_t m_number8{0};
    uint16_t m_resultNumer8{0};
    uint16_t m_number9{0};
    uint16_t m_resultNumer9{0};
    uint16_t m_number10{0};
    uint16_t m_resultNumer10{0};

};

#endif // _FAST_DDS_GENERATED_DATADEFINE_H_



