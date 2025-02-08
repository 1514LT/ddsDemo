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
 * @file DataDefineCdrAux.ipp
 * This source file contains some declarations of CDR related functions.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef _FAST_DDS_GENERATED_DATADEFINECDRAUX_IPP_
#define _FAST_DDS_GENERATED_DATADEFINECDRAUX_IPP_

#include "DataDefineCdrAux.hpp"

#include <fastcdr/Cdr.h>
#include <fastcdr/CdrSizeCalculator.hpp>


#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

namespace eprosima {
namespace fastcdr {



template<>
eProsima_user_DllExport size_t calculate_serialized_size(
        eprosima::fastcdr::CdrSizeCalculator& calculator,
        const Target& data,
        size_t& current_alignment)
{
    static_cast<void>(data);

    eprosima::fastcdr::EncodingAlgorithmFlag previous_encoding = calculator.get_encoding();
    size_t calculated_size {calculator.begin_calculate_type_serialized_size(
                                eprosima::fastcdr::CdrVersion::XCDRv2 == calculator.get_cdr_version() ?
                                eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
                                eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
                                current_alignment)};


        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(0),
                data.targetNumber(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(1),
                data.time(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(2),
                data.longitude(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(3),
                data.latitude(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(4),
                data.elevation(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(5),
                data.Priority(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(6),
                data.confidenceDegree(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(7),
                data.informationType(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(8),
                data.positionAccuracy(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(9),
                data.imagingMode(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(10),
                data.desiredTrack(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(11),
                data.shipSpeed(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(12),
                data.back(), current_alignment);


    calculated_size += calculator.end_calculate_type_serialized_size(previous_encoding, current_alignment);

    return calculated_size;
}

template<>
eProsima_user_DllExport void serialize(
        eprosima::fastcdr::Cdr& scdr,
        const Target& data)
{
    eprosima::fastcdr::Cdr::state current_state(scdr);
    scdr.begin_serialize_type(current_state,
            eprosima::fastcdr::CdrVersion::XCDRv2 == scdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);

    scdr
        << eprosima::fastcdr::MemberId(0) << data.targetNumber()
        << eprosima::fastcdr::MemberId(1) << data.time()
        << eprosima::fastcdr::MemberId(2) << data.longitude()
        << eprosima::fastcdr::MemberId(3) << data.latitude()
        << eprosima::fastcdr::MemberId(4) << data.elevation()
        << eprosima::fastcdr::MemberId(5) << data.Priority()
        << eprosima::fastcdr::MemberId(6) << data.confidenceDegree()
        << eprosima::fastcdr::MemberId(7) << data.informationType()
        << eprosima::fastcdr::MemberId(8) << data.positionAccuracy()
        << eprosima::fastcdr::MemberId(9) << data.imagingMode()
        << eprosima::fastcdr::MemberId(10) << data.desiredTrack()
        << eprosima::fastcdr::MemberId(11) << data.shipSpeed()
        << eprosima::fastcdr::MemberId(12) << data.back()
;
    scdr.end_serialize_type(current_state);
}

template<>
eProsima_user_DllExport void deserialize(
        eprosima::fastcdr::Cdr& cdr,
        Target& data)
{
    cdr.deserialize_type(eprosima::fastcdr::CdrVersion::XCDRv2 == cdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
            [&data](eprosima::fastcdr::Cdr& dcdr, const eprosima::fastcdr::MemberId& mid) -> bool
            {
                bool ret_value = true;
                switch (mid.id)
                {
                                        case 0:
                                                dcdr >> data.targetNumber();
                                            break;

                                        case 1:
                                                dcdr >> data.time();
                                            break;

                                        case 2:
                                                dcdr >> data.longitude();
                                            break;

                                        case 3:
                                                dcdr >> data.latitude();
                                            break;

                                        case 4:
                                                dcdr >> data.elevation();
                                            break;

                                        case 5:
                                                dcdr >> data.Priority();
                                            break;

                                        case 6:
                                                dcdr >> data.confidenceDegree();
                                            break;

                                        case 7:
                                                dcdr >> data.informationType();
                                            break;

                                        case 8:
                                                dcdr >> data.positionAccuracy();
                                            break;

                                        case 9:
                                                dcdr >> data.imagingMode();
                                            break;

                                        case 10:
                                                dcdr >> data.desiredTrack();
                                            break;

                                        case 11:
                                                dcdr >> data.shipSpeed();
                                            break;

                                        case 12:
                                                dcdr >> data.back();
                                            break;

                    default:
                        ret_value = false;
                        break;
                }
                return ret_value;
            });
}

void serialize_key(
        eprosima::fastcdr::Cdr& scdr,
        const Target& data)
{
    static_cast<void>(scdr);
    static_cast<void>(data);
}




template<>
eProsima_user_DllExport size_t calculate_serialized_size(
        eprosima::fastcdr::CdrSizeCalculator& calculator,
        const GuidanceInfo& data,
        size_t& current_alignment)
{
    static_cast<void>(data);

    eprosima::fastcdr::EncodingAlgorithmFlag previous_encoding = calculator.get_encoding();
    size_t calculated_size {calculator.begin_calculate_type_serialized_size(
                                eprosima::fastcdr::CdrVersion::XCDRv2 == calculator.get_cdr_version() ?
                                eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
                                eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
                                current_alignment)};


        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(0),
                data.beatCount(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(1),
                data.targetCount(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(2),
                data.node(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(3),
                data.targetType(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(4),
                data.First(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(5),
                data.Second(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(6),
                data.Third(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(7),
                data.Fourth(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(8),
                data.Fifth(), current_alignment);


    calculated_size += calculator.end_calculate_type_serialized_size(previous_encoding, current_alignment);

    return calculated_size;
}

template<>
eProsima_user_DllExport void serialize(
        eprosima::fastcdr::Cdr& scdr,
        const GuidanceInfo& data)
{
    eprosima::fastcdr::Cdr::state current_state(scdr);
    scdr.begin_serialize_type(current_state,
            eprosima::fastcdr::CdrVersion::XCDRv2 == scdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);

    scdr
        << eprosima::fastcdr::MemberId(0) << data.beatCount()
        << eprosima::fastcdr::MemberId(1) << data.targetCount()
        << eprosima::fastcdr::MemberId(2) << data.node()
        << eprosima::fastcdr::MemberId(3) << data.targetType()
        << eprosima::fastcdr::MemberId(4) << data.First()
        << eprosima::fastcdr::MemberId(5) << data.Second()
        << eprosima::fastcdr::MemberId(6) << data.Third()
        << eprosima::fastcdr::MemberId(7) << data.Fourth()
        << eprosima::fastcdr::MemberId(8) << data.Fifth()
;
    scdr.end_serialize_type(current_state);
}

template<>
eProsima_user_DllExport void deserialize(
        eprosima::fastcdr::Cdr& cdr,
        GuidanceInfo& data)
{
    cdr.deserialize_type(eprosima::fastcdr::CdrVersion::XCDRv2 == cdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
            [&data](eprosima::fastcdr::Cdr& dcdr, const eprosima::fastcdr::MemberId& mid) -> bool
            {
                bool ret_value = true;
                switch (mid.id)
                {
                                        case 0:
                                                dcdr >> data.beatCount();
                                            break;

                                        case 1:
                                                dcdr >> data.targetCount();
                                            break;

                                        case 2:
                                                dcdr >> data.node();
                                            break;

                                        case 3:
                                                dcdr >> data.targetType();
                                            break;

                                        case 4:
                                                dcdr >> data.First();
                                            break;

                                        case 5:
                                                dcdr >> data.Second();
                                            break;

                                        case 6:
                                                dcdr >> data.Third();
                                            break;

                                        case 7:
                                                dcdr >> data.Fourth();
                                            break;

                                        case 8:
                                                dcdr >> data.Fifth();
                                            break;

                    default:
                        ret_value = false;
                        break;
                }
                return ret_value;
            });
}

void serialize_key(
        eprosima::fastcdr::Cdr& scdr,
        const GuidanceInfo& data)
{
    static_cast<void>(scdr);
    static_cast<void>(data);
}




template<>
eProsima_user_DllExport size_t calculate_serialized_size(
        eprosima::fastcdr::CdrSizeCalculator& calculator,
        const ReplyInfo& data,
        size_t& current_alignment)
{
    static_cast<void>(data);

    eprosima::fastcdr::EncodingAlgorithmFlag previous_encoding = calculator.get_encoding();
    size_t calculated_size {calculator.begin_calculate_type_serialized_size(
                                eprosima::fastcdr::CdrVersion::XCDRv2 == calculator.get_cdr_version() ?
                                eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
                                eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
                                current_alignment)};


        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(0),
                data.targetNumber(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(1),
                data.handleNumber(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(2),
                data.sucessNumber(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(3),
                data.executionNumber(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(4),
                data.ownTargetNumber(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(5),
                data.number1(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(6),
                data.resultNumer1(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(7),
                data.number2(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(8),
                data.resultNumer2(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(9),
                data.number3(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(10),
                data.resultNumer3(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(11),
                data.number4(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(12),
                data.resultNumer4(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(13),
                data.number5(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(14),
                data.resultNumer5(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(15),
                data.number6(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(16),
                data.resultNumer6(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(17),
                data.number7(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(18),
                data.resultNumer7(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(19),
                data.number8(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(20),
                data.resultNumer8(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(21),
                data.number9(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(22),
                data.resultNumer9(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(23),
                data.number10(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(24),
                data.resultNumer10(), current_alignment);


    calculated_size += calculator.end_calculate_type_serialized_size(previous_encoding, current_alignment);

    return calculated_size;
}

template<>
eProsima_user_DllExport void serialize(
        eprosima::fastcdr::Cdr& scdr,
        const ReplyInfo& data)
{
    eprosima::fastcdr::Cdr::state current_state(scdr);
    scdr.begin_serialize_type(current_state,
            eprosima::fastcdr::CdrVersion::XCDRv2 == scdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);

    scdr
        << eprosima::fastcdr::MemberId(0) << data.targetNumber()
        << eprosima::fastcdr::MemberId(1) << data.handleNumber()
        << eprosima::fastcdr::MemberId(2) << data.sucessNumber()
        << eprosima::fastcdr::MemberId(3) << data.executionNumber()
        << eprosima::fastcdr::MemberId(4) << data.ownTargetNumber()
        << eprosima::fastcdr::MemberId(5) << data.number1()
        << eprosima::fastcdr::MemberId(6) << data.resultNumer1()
        << eprosima::fastcdr::MemberId(7) << data.number2()
        << eprosima::fastcdr::MemberId(8) << data.resultNumer2()
        << eprosima::fastcdr::MemberId(9) << data.number3()
        << eprosima::fastcdr::MemberId(10) << data.resultNumer3()
        << eprosima::fastcdr::MemberId(11) << data.number4()
        << eprosima::fastcdr::MemberId(12) << data.resultNumer4()
        << eprosima::fastcdr::MemberId(13) << data.number5()
        << eprosima::fastcdr::MemberId(14) << data.resultNumer5()
        << eprosima::fastcdr::MemberId(15) << data.number6()
        << eprosima::fastcdr::MemberId(16) << data.resultNumer6()
        << eprosima::fastcdr::MemberId(17) << data.number7()
        << eprosima::fastcdr::MemberId(18) << data.resultNumer7()
        << eprosima::fastcdr::MemberId(19) << data.number8()
        << eprosima::fastcdr::MemberId(20) << data.resultNumer8()
        << eprosima::fastcdr::MemberId(21) << data.number9()
        << eprosima::fastcdr::MemberId(22) << data.resultNumer9()
        << eprosima::fastcdr::MemberId(23) << data.number10()
        << eprosima::fastcdr::MemberId(24) << data.resultNumer10()
;
    scdr.end_serialize_type(current_state);
}

template<>
eProsima_user_DllExport void deserialize(
        eprosima::fastcdr::Cdr& cdr,
        ReplyInfo& data)
{
    cdr.deserialize_type(eprosima::fastcdr::CdrVersion::XCDRv2 == cdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
            [&data](eprosima::fastcdr::Cdr& dcdr, const eprosima::fastcdr::MemberId& mid) -> bool
            {
                bool ret_value = true;
                switch (mid.id)
                {
                                        case 0:
                                                dcdr >> data.targetNumber();
                                            break;

                                        case 1:
                                                dcdr >> data.handleNumber();
                                            break;

                                        case 2:
                                                dcdr >> data.sucessNumber();
                                            break;

                                        case 3:
                                                dcdr >> data.executionNumber();
                                            break;

                                        case 4:
                                                dcdr >> data.ownTargetNumber();
                                            break;

                                        case 5:
                                                dcdr >> data.number1();
                                            break;

                                        case 6:
                                                dcdr >> data.resultNumer1();
                                            break;

                                        case 7:
                                                dcdr >> data.number2();
                                            break;

                                        case 8:
                                                dcdr >> data.resultNumer2();
                                            break;

                                        case 9:
                                                dcdr >> data.number3();
                                            break;

                                        case 10:
                                                dcdr >> data.resultNumer3();
                                            break;

                                        case 11:
                                                dcdr >> data.number4();
                                            break;

                                        case 12:
                                                dcdr >> data.resultNumer4();
                                            break;

                                        case 13:
                                                dcdr >> data.number5();
                                            break;

                                        case 14:
                                                dcdr >> data.resultNumer5();
                                            break;

                                        case 15:
                                                dcdr >> data.number6();
                                            break;

                                        case 16:
                                                dcdr >> data.resultNumer6();
                                            break;

                                        case 17:
                                                dcdr >> data.number7();
                                            break;

                                        case 18:
                                                dcdr >> data.resultNumer7();
                                            break;

                                        case 19:
                                                dcdr >> data.number8();
                                            break;

                                        case 20:
                                                dcdr >> data.resultNumer8();
                                            break;

                                        case 21:
                                                dcdr >> data.number9();
                                            break;

                                        case 22:
                                                dcdr >> data.resultNumer9();
                                            break;

                                        case 23:
                                                dcdr >> data.number10();
                                            break;

                                        case 24:
                                                dcdr >> data.resultNumer10();
                                            break;

                    default:
                        ret_value = false;
                        break;
                }
                return ret_value;
            });
}

void serialize_key(
        eprosima::fastcdr::Cdr& scdr,
        const ReplyInfo& data)
{
    static_cast<void>(scdr);
    static_cast<void>(data);
}



} // namespace fastcdr
} // namespace eprosima

#endif // _FAST_DDS_GENERATED_DATADEFINECDRAUX_IPP_

