/*
 * SPDX-FileCopyrightText: Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// NvDsMetaSchema

#include "bind_string_property_definitions.h"
#include "bindschema.hpp"

namespace py = pybind11;

namespace pydeepstream {

    void bindschema(py::module &m) {
        /*Start of Bindings for nvdsmeta_schema.h*/
        py::enum_<NvDsEventType>(m, "NvDsEventType",
                                 pydsdoc::metaschema::EventTypeDoc::descr)
                .value("NVDS_EVENT_ENTRY", NVDS_EVENT_ENTRY,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_ENTRY)
                .value("NVDS_EVENT_EXIT", NVDS_EVENT_EXIT,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_EXIT)
                .value("NVDS_EVENT_MOVING", NVDS_EVENT_MOVING,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_MOVING)
                .value("NVDS_EVENT_STOPPED", NVDS_EVENT_STOPPED,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_STOPPED)
                .value("NVDS_EVENT_EMPTY", NVDS_EVENT_EMPTY,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_EMPTY)
                .value("NVDS_EVENT_PARKED", NVDS_EVENT_PARKED,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_PARKED)
                .value("NVDS_EVENT_RESET", NVDS_EVENT_RESET,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_RESET)
                .value("NVDS_EVENT_RESERVED", NVDS_EVENT_RESERVED,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_RESERVED)
                .value("NVDS_EVENT_CUSTOM", NVDS_EVENT_CUSTOM,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_CUSTOM)
                .value("NVDS_EVENT_FORCE32", NVDS_EVENT_FORCE32,
                       pydsdoc::metaschema::EventTypeDoc::NVDS_EVENT_FORCE32)
                .export_values();


        py::enum_<NvDsObjectType>(m, "NvDsObjectType",
                                  pydsdoc::metaschema::ObjectTypeDoc::descr)
                .value("NVDS_OBJECT_TYPE_VEHICLE", NVDS_OBJECT_TYPE_VEHICLE,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_VEHICLE)
                .value("NVDS_OBJECT_TYPE_PERSON", NVDS_OBJECT_TYPE_PERSON,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_PERSON)
                .value("NVDS_OBJECT_TYPE_FACE", NVDS_OBJECT_TYPE_FACE,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_FACE)
                .value("NVDS_OBJECT_TYPE_BAG", NVDS_OBJECT_TYPE_BAG,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_BAG)
                .value("NVDS_OBJECT_TYPE_BICYCLE", NVDS_OBJECT_TYPE_BICYCLE,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_BICYCLE)
                .value("NVDS_OBJECT_TYPE_ROADSIGN", NVDS_OBJECT_TYPE_ROADSIGN,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_ROADSIGN)
                .value("NVDS_OBJECT_TYPE_VEHICLE_EXT",
                       NVDS_OBJECT_TYPE_VEHICLE_EXT,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_VEHICLE_EXT)
                .value("NVDS_OBJECT_TYPE_PERSON_EXT",
                       NVDS_OBJECT_TYPE_PERSON_EXT,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_PERSON_EXT)
                .value("NVDS_OBJECT_TYPE_FACE_EXT", NVDS_OBJECT_TYPE_FACE_EXT,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_FACE_EXT)
                .value("NVDS_OBJECT_TYPE_RESERVED", NVDS_OBJECT_TYPE_RESERVED,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_RESERVED)
                .value("NVDS_OBJECT_TYPE_CUSTOM", NVDS_OBJECT_TYPE_CUSTOM,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_CUSTOM)
                .value("NVDS_OBJECT_TYPE_UNKNOWN", NVDS_OBJECT_TYPE_UNKNOWN,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBJECT_TYPE_UNKNOWN)
                .value("NVDS_OBEJCT_TYPE_FORCE32", NVDS_OBEJCT_TYPE_FORCE32,
                       pydsdoc::metaschema::ObjectTypeDoc::NVDS_OBEJCT_TYPE_FORCE32)
                .export_values();


        py::enum_<NvDsPayloadType>(m, "NvDsPayloadType",
                                   pydsdoc::metaschema::PayloadTypeDoc::descr)
                .value("NVDS_PAYLOAD_DEEPSTREAM", NVDS_PAYLOAD_DEEPSTREAM,
                       pydsdoc::metaschema::PayloadTypeDoc::NVDS_PAYLOAD_DEEPSTREAM)
                .value("NVDS_PAYLOAD_DEEPSTREAM_MINIMAL",
                       NVDS_PAYLOAD_DEEPSTREAM_MINIMAL,
                       pydsdoc::metaschema::PayloadTypeDoc::NVDS_PAYLOAD_DEEPSTREAM_MINIMAL)
                .value("NVDS_PAYLOAD_RESERVED", NVDS_PAYLOAD_RESERVED,
                       pydsdoc::metaschema::PayloadTypeDoc::NVDS_PAYLOAD_RESERVED)
                .value("NVDS_PAYLOAD_CUSTOM", NVDS_PAYLOAD_CUSTOM,
                       pydsdoc::metaschema::PayloadTypeDoc::NVDS_PAYLOAD_CUSTOM)
                .value("NVDS_PAYLOAD_FORCE32", NVDS_PAYLOAD_FORCE32,
                       pydsdoc::metaschema::PayloadTypeDoc::NVDS_PAYLOAD_FORCE32)
                .export_values();


        py::class_<NvDsRect>(m, "NvDsRect", pydsdoc::metaschema::RectDoc::descr)
                .def(py::init<>())
                .def_readwrite("top", &NvDsRect::top)
                .def_readwrite("left", &NvDsRect::left)
                .def_readwrite("width", &NvDsRect::width)
                .def_readwrite("height", &NvDsRect::height)

                .def("cast",
                     [](void *data) {
                         return (NvDsRect *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::RectDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsRect *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::RectDoc::cast);


        py::class_<NvDsGeoLocation>(m, "NvDsGeoLocation",
                                    pydsdoc::metaschema::GeoLocationDoc::descr)
                .def(py::init<>())
                .def_readwrite("lat", &NvDsGeoLocation::lat)
                .def_readwrite("lon", &NvDsGeoLocation::lon)
                .def_readwrite("alt", &NvDsGeoLocation::alt)

                .def("cast",
                     [](void *data) {
                         return (NvDsGeoLocation *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::GeoLocationDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsGeoLocation *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::GeoLocationDoc::cast);


        py::class_<NvDsCoordinate>(m, "NvDsCoordinate",
                                   pydsdoc::metaschema::CoordinateDoc::descr)
                .def(py::init<>())
                .def_readwrite("x", &NvDsCoordinate::x)
                .def_readwrite("y", &NvDsCoordinate::y)
                .def_readwrite("z", &NvDsCoordinate::z)

                .def("cast",
                     [](void *data) {
                         return (NvDsCoordinate *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::CoordinateDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsCoordinate *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::CoordinateDoc::cast);


        py::class_<NvDsObjectSignature>(m, "NvDsObjectSignature",
                                        pydsdoc::metaschema::ObjectSignatureDoc::descr)
                .def(py::init<>())
                .def_readwrite("signature", &NvDsObjectSignature::signature)
                .def_readwrite("size", &NvDsObjectSignature::size)

                .def("cast",
                     [](void *data) {
                         return (NvDsObjectSignature *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::ObjectSignatureDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsObjectSignature *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::ObjectSignatureDoc::cast);


        py::class_<NvDsVehicleObject>(m, "NvDsVehicleObject",
                                      pydsdoc::metaschema::VehicleObjectDoc::descr)
                .def(py::init<>())
                .def_property("type", STRING_PROPERTY(NvDsVehicleObject, type))
                .def_property("make", STRING_PROPERTY(NvDsVehicleObject, make))
                .def_property("model",
                              STRING_PROPERTY(NvDsVehicleObject, model))
                .def_property("color",
                              STRING_PROPERTY(NvDsVehicleObject, color))

                .def("cast",
                     [](void *data) {
                         return (NvDsVehicleObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::VehicleObjectDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsVehicleObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::VehicleObjectDoc::cast)

                .def_property("region",
                              STRING_PROPERTY(NvDsVehicleObject, region))
                .def_property("license",
                              STRING_PROPERTY(NvDsVehicleObject, license));

        m.def("alloc_nvds_vehicle_object",
              []() {
                  auto *object = (NvDsVehicleObject *) g_malloc0(
                          sizeof(NvDsVehicleObject));
                  return object;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_nvds_vehicle_object);


        py::class_<NvDsPersonObject>(m, "NvDsPersonObject",
                                     pydsdoc::metaschema::PersonObjectDoc::descr)
                .def(py::init<>())
                .def_property("gender",
                              STRING_PROPERTY(NvDsPersonObject, gender))
                .def_property("hair", STRING_PROPERTY(NvDsPersonObject, hair))

                .def("cast",
                     [](void *data) {
                         return (NvDsPersonObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::PersonObjectDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsPersonObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::PersonObjectDoc::cast)

                .def_property("cap", STRING_PROPERTY(NvDsPersonObject, cap))
                .def_property("apparel",
                              STRING_PROPERTY(NvDsPersonObject, apparel))
                .def_readwrite("age", &NvDsPersonObject::age);

        m.def("alloc_nvds_person_object", []() {
                  auto *object = (NvDsPersonObject *) g_malloc0(
                          sizeof(NvDsPersonObject));
                  return object;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_nvds_person_object);


        py::class_<NvDsFaceObject>(m, "NvDsFaceObject",
                                   pydsdoc::metaschema::FaceObjectDoc::descr)
                .def(py::init<>())
                .def_property("gender", STRING_PROPERTY(NvDsFaceObject, gender))
                .def_property("hair", STRING_PROPERTY(NvDsFaceObject, hair))
                .def_property("cap", STRING_PROPERTY(NvDsFaceObject, cap))
                .def_property("glasses",
                              STRING_PROPERTY(NvDsFaceObject, glasses))
                .def_property("facialhair",
                              STRING_PROPERTY(NvDsFaceObject, facialhair))
                .def_property("name", STRING_PROPERTY(NvDsFaceObject, name))
                .def_property("eyecolor",
                              STRING_PROPERTY(NvDsFaceObject, eyecolor))
                .def_readwrite("age", &NvDsFaceObject::age)

                .def("cast",
                     [](void *data) {
                         return (NvDsFaceObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::FaceObjectDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsFaceObject *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::FaceObjectDoc::cast);


        py::class_<NvDsVehicleObjectExt>(m, "NvDsVehicleObjectExt",
                                         pydsdoc::metaschema::NvDsVehicleObjectExtDoc::descr)
                .def(py::init<>())
                .def_readwrite("type", &NvDsVehicleObjectExt::type)
                .def_readwrite("make", &NvDsVehicleObjectExt::make)
                .def_readwrite("model", &NvDsVehicleObjectExt::model)
                .def_readwrite("color", &NvDsVehicleObjectExt::color)
                .def_readwrite("region", &NvDsVehicleObjectExt::region)
                .def_readwrite("license", &NvDsVehicleObjectExt::license)
                .def_readwrite("mask", &NvDsVehicleObjectExt::mask)

                .def("cast",
                     [](void *data) {
                         return (NvDsVehicleObjectExt *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::NvDsVehicleObjectExtDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsVehicleObjectExt *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::NvDsVehicleObjectExtDoc::cast);


        py::class_<NvDsPersonObjectExt>(m, "NvDsPersonObjectExt",
                                        pydsdoc::metaschema::NvDsPersonObjectExtDoc::descr)
                .def(py::init<>())
                .def_readwrite("gender", &NvDsPersonObjectExt::gender)
                .def_readwrite("hair", &NvDsPersonObjectExt::hair)
                .def_readwrite("cap", &NvDsPersonObjectExt::cap)
                .def_readwrite("apparel", &NvDsPersonObjectExt::apparel)
                .def_readwrite("age", &NvDsPersonObjectExt::age)
                .def_readwrite("mask", &NvDsPersonObjectExt::mask)

                .def("cast",
                     [](void *data) {
                         return (NvDsPersonObjectExt *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::NvDsPersonObjectExtDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsPersonObjectExt *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::NvDsPersonObjectExtDoc::cast);


        py::class_<NvDsFaceObjectWithExt>(m, "NvDsFaceObjectWithExt",
                                          pydsdoc::metaschema::NvDsFaceObjectWithExtDoc::descr)
                .def(py::init<>())
                .def_readwrite("gender", &NvDsFaceObjectWithExt::gender)
                .def_readwrite("hair", &NvDsFaceObjectWithExt::hair)
                .def_readwrite("cap", &NvDsFaceObjectWithExt::cap)
                .def_readwrite("glasses", &NvDsFaceObjectWithExt::glasses)
                .def_readwrite("facialhair", &NvDsFaceObjectWithExt::facialhair)
                .def_readwrite("name", &NvDsFaceObjectWithExt::name)
                .def_readwrite("eyecolor", &NvDsFaceObjectWithExt::eyecolor)
                .def_readwrite("age", &NvDsFaceObjectWithExt::age)
                .def_readwrite("mask", &NvDsFaceObjectWithExt::mask)

                .def("cast",
                     [](void *data) {
                         return (NvDsFaceObjectWithExt *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::NvDsFaceObjectWithExtDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsFaceObjectWithExt *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::NvDsFaceObjectWithExtDoc::cast);

        m.def("alloc_nvds_face_object",
              []() {
                  auto *object = (NvDsFaceObject *) g_malloc0(
                          sizeof(NvDsFaceObject));
                  return object;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_nvds_face_object);


        py::class_<NvDsEventMsgMeta>(m, "NvDsEventMsgMeta",
                                     pydsdoc::metaschema::EventmsgDoc::descr)
                .def(py::init<>())
                .def_readwrite("type", &NvDsEventMsgMeta::type)
                .def_readwrite("objType", &NvDsEventMsgMeta::objType)
                .def_readwrite("bbox", &NvDsEventMsgMeta::bbox)
                .def_readwrite("location", &NvDsEventMsgMeta::location)
                .def_readwrite("coordinate", &NvDsEventMsgMeta::coordinate)
                .def_readwrite("objSignature", &NvDsEventMsgMeta::objSignature)
                .def_readwrite("objClassId", &NvDsEventMsgMeta::objClassId)
                .def_readwrite("sensorId", &NvDsEventMsgMeta::sensorId)
                .def_readwrite("moduleId", &NvDsEventMsgMeta::moduleId)

                .def("cast",
                     [](void *data) {
                         return (NvDsEventMsgMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::EventmsgDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsEventMsgMeta *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::EventmsgDoc::cast)

                .def_readwrite("placeId", &NvDsEventMsgMeta::placeId)
                .def_readwrite("componentId", &NvDsEventMsgMeta::componentId)
                .def_readwrite("frameId", &NvDsEventMsgMeta::frameId)
                .def_readwrite("confidence", &NvDsEventMsgMeta::confidence)
                .def_readwrite("trackingId", &NvDsEventMsgMeta::trackingId)
                .def_property("ts", BUFFER_PROPERTY(NvDsEventMsgMeta, ts))
                .def_property("objectId",
                              STRING_PROPERTY(NvDsEventMsgMeta, objectId))
                .def_property("sensorStr",
                              STRING_PROPERTY(NvDsEventMsgMeta, sensorStr))
                .def_property("otherAttrs",
                              STRING_PROPERTY(NvDsEventMsgMeta, otherAttrs))
                .def_property("videoPath",
                              STRING_PROPERTY(NvDsEventMsgMeta, videoPath))
                .def_readwrite("extMsg", &NvDsEventMsgMeta::extMsg)
                .def_readwrite("extMsgSize", &NvDsEventMsgMeta::extMsgSize);

        m.def("alloc_nvds_event_msg_meta",
              []() {
                  auto *msg_meta = (NvDsEventMsgMeta *) g_malloc0(
                          sizeof(NvDsEventMsgMeta));
                  return msg_meta;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_nvds_event_msg_meta);


        m.def("generate_ts_rfc3339",
              [](size_t buffer, size_t size) {
                  char *bufptr = (char *) buffer;
                  utils::generate_ts_rfc3339(bufptr, size);
              },
              "buffer"_a, "size"_a,
              pydsdoc::methodsDoc::generate_ts_rfc3339);


        py::class_<NvDsEvent>(m, "NvDsEvent",
                              pydsdoc::metaschema::EventDoc::descr)
                .def(py::init<>())
                .def_readwrite("eventType", &NvDsEvent::eventType)
                .def_readwrite("metadata", &NvDsEvent::metadata)

                .def("cast",
                     [](void *data) {
                         return (NvDsEvent *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::EventDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsEvent *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::EventDoc::cast);

        m.def("alloc_nvds_event",
              []() {
                  auto *mem = (NvDsEvent *) g_malloc0(sizeof(NvDsEvent));
                  return mem;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_nvds_event);


        py::class_<NvDsPayload>(m, "NvDsPayload",
                                pydsdoc::metaschema::PayloadDoc::descr)
                .def(py::init<>())
                .def_readwrite("payload", &NvDsPayload::payload)
                .def_readwrite("payloadSize", &NvDsPayload::payloadSize)
                .def_readwrite("componentId", &NvDsPayload::componentId)

                .def("cast",
                     [](void *data) {
                         return (NvDsPayload *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::PayloadDoc::cast)

                .def("cast",
                     [](size_t data) {
                         return (NvDsPayload *) data;
                     },
                     py::return_value_policy::reference,
                     pydsdoc::metaschema::PayloadDoc::cast);

        m.def("alloc_nvds_payload",
              []() {
                  auto *mem = (NvDsPayload *) g_malloc0(
                          sizeof(NvDsPayload));
                  return mem;
              },
              py::return_value_policy::reference,
              pydsdoc::methodsDoc::alloc_nvds_payload);

    }

}
