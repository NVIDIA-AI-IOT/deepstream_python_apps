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
 
#pragma once

namespace pydsdoc
{
    namespace metaschema
    {
        namespace EventTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Event type flags.)pyds";
            constexpr const char* NVDS_EVENT_ENTRY=R"pyds(NVDS_EVENT_ENTRY)pyds";
            constexpr const char* NVDS_EVENT_EXIT=R"pyds(NVDS_EVENT_EXIT)pyds";
            constexpr const char* NVDS_EVENT_MOVING=R"pyds(NVDS_EVENT_MOVING)pyds";
            constexpr const char* NVDS_EVENT_STOPPED=R"pyds(NVDS_EVENT_STOPPED)pyds";
            constexpr const char* NVDS_EVENT_EMPTY=R"pyds(NVDS_EVENT_EMPTY)pyds";
            constexpr const char* NVDS_EVENT_PARKED=R"pyds(NVDS_EVENT_PARKED)pyds";
            constexpr const char* NVDS_EVENT_RESET=R"pyds(NVDS_EVENT_RESET)pyds";
            constexpr const char* NVDS_EVENT_RESERVED=R"pyds(Reserved for future use. Use value greater than this for custom events.)pyds";
            constexpr const char* NVDS_EVENT_CUSTOM=R"pyds(Specifies a custom event.)pyds";
            constexpr const char* NVDS_EVENT_FORCE32=R"pyds(NVDS_EVENT_FORCE32)pyds";
        }        

        namespace ObjectTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Object type flags.)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_VEHICLE=R"pyds(NVDS_OBJECT_TYPE_VEHICLE)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_PERSON=R"pyds(NVDS_OBJECT_TYPE_PERSON)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_FACE=R"pyds(NVDS_OBJECT_TYPE_FACE)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_BAG=R"pyds(NVDS_OBJECT_TYPE_BAG)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_BICYCLE=R"pyds(NVDS_OBJECT_TYPE_BICYCLE)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_ROADSIGN=R"pyds(NVDS_OBJECT_TYPE_ROADSIGN)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_RESERVED=R"pyds(Reserved for future use. Use value greater than this for custom objects.)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_CUSTOM=R"pyds(To support custom object.)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_VEHICLE_EXT=R"pyds(NVDS_OBJECT_TYPE_VEHICLE_EXT)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_PERSON_EXT=R"pyds(NVDS_OBJECT_TYPE_PERSON_EXT)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_FACE_EXT=R"pyds(NVDS_OBJECT_TYPE_FACE_EXT)pyds";
            constexpr const char* NVDS_OBJECT_TYPE_UNKNOWN=R"pyds("object" key will be missing in the schema)pyds";
            constexpr const char* NVDS_OBEJCT_TYPE_FORCE32=R"pyds(NVDS_OBEJCT_TYPE_FORCE32)pyds";
        }

        namespace PayloadTypeDoc
        {
            constexpr const char* descr = R"pyds(*Enumerator*. Payload type flags.)pyds";
            constexpr const char* NVDS_PAYLOAD_DEEPSTREAM=R"pyds(NVDS_PAYLOAD_DEEPSTREAM)pyds";
            constexpr const char* NVDS_PAYLOAD_DEEPSTREAM_MINIMAL=R"pyds(NVDS_PAYLOAD_DEEPSTREAM_MINIMAL)pyds";
            constexpr const char* NVDS_PAYLOAD_RESERVED=R"pyds(Reserved for future use. Use value greater than this for custom payloads.)pyds";
            constexpr const char* NVDS_PAYLOAD_CUSTOM=R"pyds(To support custom payload. User need to implement nvds_msg2p_* interface)pyds";
            constexpr const char* NVDS_PAYLOAD_FORCE32=R"pyds(NVDS_PAYLOAD_FORCE32)pyds";
        }

        namespace RectDoc   
        {
            constexpr const char* descr = R"pyds(
                Holds a rectangle's position and size.
                
                :ivar top: *float*, Holds the position of rectangle's top in pixels.
                :ivar left: *float*, Holds the position of rectangle's left side in pixels.
                :ivar width: *float*, Holds the rectangle's width in pixels.
                :ivar height: *float*, Holds the rectangle's height in pixels.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsRect`, call pyds.NvDsRect.cast(data))pyds";
        }

        namespace GeoLocationDoc
        {
            constexpr const char* descr = R"pyds(
                Holds Geo-location parameters.

                :ivar lat: *float*, Holds the location's latitude.
                :ivar lon: *float*, Holds the location's longitude.
                :ivar alt: *float*, Holds the location's altitude.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsGeoLocation`, call pyds.NvDsGeoLocation.cast(data))pyds";
        }

        namespace CoordinateDoc
        {
            constexpr const char* descr = R"pyds(
                Hold coordinate parameters.
                
                :ivar x: *float*, Holds the coordinate's X position.
                :ivar y: *float*, Holds the coordinate's Y position.
                :ivar z: *float*, Holds the coordinate's Z position.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsCoordinate`, call pyds.NvDsCoordinate.cast(data))pyds";
        }

        namespace ObjectSignatureDoc
        {
            constexpr const char* descr = R"pyds(
                Holds object signature.
                
                :ivar signature: *list of float*, Holds signature values.
                :ivar size: *int*, Holds the number of signature values in signature.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsObjectSignature`, call pyds.NvDsObjectSignature.cast(data))pyds";
        }

        namespace VehicleObjectDoc
        {
            constexpr const char* descr = R"pyds(
                Holds vehicle object parameters.

                :ivar type: *str*, Type of the vehicle.
                :ivar make: *str*, Make of the vehicle.
                :ivar model: *str*, Model of the vehicle.
                :ivar color: *str*, Color of the vehicle.
                :ivar region: *str*, Region of the vehicle.
                :ivar license: *str*, License number of the vehicle.

                Example usage:
                ::

                    data = pyds.alloc_nvds_vehicle_object() #Allocate NvDsVehicleObject
                    obj = pyds.NvDsVehicleObject.cast(data);
                    #Set attributes
                    obj.type ="sedan"
                    obj.color="blue"
                    obj.make ="Bugatti"
                    obj.model = "M"
                    obj.license ="XX1234"
                    obj.region ="CA")pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsVehicleObject` object, call pyds.NvDsVehicleObject(data))pyds";
        }

        namespace PersonObjectDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a person object's parameters.

                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar apparel: *str*, Description of the person's apparel.
                :ivar age: *int*, Person's age.

                Example usage:
                ::

                    data = pyds.alloc_nvds_person_object() #Allocate NvDsPersonObject
                    obj = pyds.NvDsPersonObject.cast(data)
                    #Set attributes
                    obj.age = 45
                    obj.cap = "none"
                    obj.hair = "black"
                    obj.gender = "male"
                    obj.apparel= "formal")pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsPersonObject` object, call pyds.NvDsPersonObject(data))pyds";
        }

        namespace FaceObjectDoc
        {
            constexpr const char* descr = R"pyds(
                Holds face parameters.

                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar glasses: *str*, Type of glasses the person is wearing, if any.
                :ivar facialhair: *str*, Person's facial hair color.
                :ivar name: *str*, Person's name.
                :ivar eyecolor: *str*, Person's eye color.
                :ivar age: *int*, Person's age.)pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsFaceObject` object, call pyds.NvDsFaceObject(data))pyds";
        }

        namespace NvDsVehicleObjectExtDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a vehicle object's parameters.

                :ivar type: *str*, Type of the vehicle.
                :ivar make: *str*, Make of the vehicle.
                :ivar model: *str*, Model of the vehicle.
                :ivar color: *str*, Color of the vehicle.
                :ivar region: *str*, Region of the vehicle.
                :ivar license: *str*, License number of the vehicle.
                :ivar mask: *Glist* of polygons for vehicle mask.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsVehicleObjectExt`, call pyds.NvDsVehicleObjectExt.cast(data))pyds";
        }

        namespace NvDsPersonObjectExtDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a vehicle object's parameters.

                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar apparel: *str*, Description of the person's apparel.
                :ivar age: *int*, Person's age.
                :ivar mask: *Glist* of polygons for person mask.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPersonObjectExt`, call pyds.NvDsPersonObjectExt.cast(data))pyds";
        }

        namespace NvDsFaceObjectWithExtDoc
        {
            constexpr const char* descr = R"pyds(
                Holds a vehicle object's parameters.
                
                :ivar gender: *str*, Person's gender.
                :ivar hair: *str*, Person's hair color.
                :ivar cap: *str*, Type of cap the person is wearing, if any.
                :ivar glasses: *str*, Type of glasses the person is wearing, if any.W
                :ivar facialhair: *str*, Person's facial hair color.Ws
                :ivar name: *str*, Person's name.
                :ivar eyecolor: *str*, Person's eye color.
                :ivar age: *int*, Person's age.
                :ivar mask: *Glist* of polygons for face mask.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsFaceObjectWithExt`, call pyds.NvDsFaceObjectWithExt.cast(data))pyds";
        }

        namespace EventmsgDoc
        {
            constexpr const char* descr = R"pyds(
                Holds event message meta data. You can attach various types of objects (vehicle, person, face, etc.) to an event by setting a pointer to the object in :py:attr:`extMsg`. 
                Similarly, you can attach a custom object to an event by setting a pointer to the object in :py:attr:`extMsg`.
                A custom object must be handled by the metadata parsing module accordingly.

                :ivar type: :class:`NvDsEventType`, Type of event.
                :ivar objType: :class:`NvDsObjectType`, Type of object.
                :ivar bbox: :class:`NvDsRect`, Bounding box of object.
                :ivar location: :class:`NvDsGeoLocation`, Geo-location of object.
                :ivar coordinate: :class:`NvDsCoordinate`, Coordinate of object.
                :ivar objSignature: :class:`NvDsObjectSignature`, Signature of object.
                :ivar objClassId: *int*, Class id of object.
                :ivar sensorId: *int*, ID of sensor that generated the event.
                :ivar moduleId: *int*, ID of analytics module that generated the event.
                :ivar placeId: *int*, ID of place related to the object.
                :ivar componentId: *int*, ID of component that generated this event.
                :ivar frameId: *int*, Video frame ID of this event.
                :ivar confidence: *int*, Confidence level of the inference.
                :ivar trackingId: *int*, Tracking ID of object.
                :ivar ts: *str*, Time stamp of generated event.
                :ivar objectId: *str*, ID of detected / inferred object.
                :ivar sensorStr: *str*, Identity string of sensor.
                :ivar otherAttrs: *str*, Other attributes associated with the object.
                :ivar videoPath: *str*, Name of video file.
                :ivar extMsg: Object to extend the event message meta data. This can be used for custom values that can't be accommodated in the existing fields 
                    OR if object(vehicle, person, face etc.) Specific values must be attached.
                :ivar extMsgSize: *int*, Size of the custom object at extMsg.

                Example usage:
                ::

                    def generate_event_msg_meta(data, class_id):
                        meta =pyds.NvDsEventMsgMeta.cast(data)
                        meta.sensorId = 0
                        meta.placeId = 0
                        meta.moduleId = 0
                        meta.sensorStr = "sensor-0"
                        meta.ts = pyds.alloc_buffer(MAX_TIME_STAMP_LEN + 1)
                        pyds.generate_ts_rfc3339(meta.ts, MAX_TIME_STAMP_LEN) #Generate timestamp

                        # This demonstrates how to attach custom objects.
                        # Any custom object as per requirement can be generated and attached
                        # like NvDsVehicleObject / NvDsPersonObject. Then that object should
                        # be handled in payload generator library (nvmsgconv.cpp) accordingly.
                        if(class_id==PGIE_CLASS_ID_VEHICLE):
                            meta.type = pyds.NvDsEventType.NVDS_EVENT_MOVING
                            meta.objType = pyds.NvDsObjectType.NVDS_OBJECT_TYPE_VEHICLE
                            meta.objClassId = PGIE_CLASS_ID_VEHICLE
                            obj = pyds.alloc_nvds_vehicle_object()
                            obj = generate_vehicle_meta(obj) #See NvDsVehicleObject example code
                            meta.extMsg = obj
                            meta.extMsgSize = sys.getsizeof(pyds.NvDsVehicleObject);
                        if(class_id == PGIE_CLASS_ID_PERSON):
                            meta.type =pyds.NvDsEventType.NVDS_EVENT_ENTRY
                            meta.objType = pyds.NvDsObjectType.NVDS_OBJECT_TYPE_PERSON;
                            meta.objClassId = PGIE_CLASS_ID_PERSON
                            obj = pyds.alloc_nvds_person_object()
                            obj=generate_person_meta(obj)
                            meta.extMsg = obj
                            meta.extMsgSize = sys.getsizeof(pyds.NvDsPersonObject)
                        return meta

                    ...

                    # Allocating an NvDsEventMsgMeta instance and getting reference
                    # to it. The underlying memory is not manged by Python so that
                    # downstream plugins can access it. Otherwise the garbage collector
                    # will free it when this probe exits.
                    msg_meta=pyds.alloc_nvds_event_msg_meta()
                    msg_meta.bbox.top =  obj_meta.rect_params.top
                    msg_meta.bbox.left =  obj_meta.rect_params.left
                    msg_meta.bbox.width = obj_meta.rect_params.width
                    msg_meta.bbox.height = obj_meta.rect_params.height
                    msg_meta.frameId = frame_number
                    msg_meta.trackingId = long_to_uint64(obj_meta.object_id)
                    msg_meta.confidence = obj_meta.confidence
                    msg_meta = generate_event_msg_meta(msg_meta, obj_meta.class_id)
                    user_event_meta = pyds.nvds_acquire_user_meta_from_pool(batch_meta)
                    if(user_event_meta):
                        user_event_meta.user_meta_data = msg_meta;
                        user_event_meta.base_meta.meta_type = pyds.NvDsMetaType.NVDS_EVENT_MSG_META
                        # Setting callbacks in the event msg meta. The bindings layer
                        # will wrap these callables in C functions. Currently only one
                        # set of callbacks is supported.
                        pyds.user_copyfunc(user_event_meta, meta_copy_func)
                        pyds.user_releasefunc(user_event_meta, meta_free_func)
                        pyds.nvds_add_user_meta_to_frame(frame_meta, user_event_meta)
                    else:
                        print("Error in attaching event meta to buffer\n"))pyds";

            constexpr const char* cast=R"pyds(casts to :class:`NvDsEventMsgMeta` object, call pyds.NvDsEventMsgMeta(data))pyds";
        }

        namespace EventDoc
        {
            constexpr const char* descr = R"pyds(
                Holds event information.

                :ivar eventType: :class:`NvDsEventType`, Type of event.
                :ivar metadata: :class:`NvDsEventMsgMeta`, object of event meta data.)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsEvent`, call pyds.NvDsEvent.cast(data))pyds";
        }

        namespace PayloadDoc
        {
            constexpr const char* descr = R"pyds(
                Holds payload meta data.

                :ivar payload: Payload object.
                :ivar payloadSize: *int*, Size of payload.
                :ivar componentId: *int*, ID of component who attached the payload (Optional).)pyds";

            constexpr const char* cast=R"pyds(cast given object/data to :class:`NvDsPayload`, call pyds.NvDsPayload.cast(data))pyds";
        }
    }
}