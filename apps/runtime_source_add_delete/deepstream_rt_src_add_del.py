#!/usr/bin/env python3

################################################################################
# SPDX-FileCopyrightText: Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

import sys
sys.path.append('../')
import gi
import configparser
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GLib
from gi.repository import GLib
from ctypes import *
import time
import sys
import math
import random
import platform
from common.is_aarch_64 import is_aarch64

import pyds

MAX_DISPLAY_LEN=64
PGIE_CLASS_ID_VEHICLE = 0
PGIE_CLASS_ID_BICYCLE = 1
PGIE_CLASS_ID_PERSON = 2
PGIE_CLASS_ID_ROADSIGN = 3
MUXER_OUTPUT_WIDTH=1920
MUXER_OUTPUT_HEIGHT=1080
MUXER_BATCH_TIMEOUT_USEC=4000000
TILED_OUTPUT_WIDTH=1280
TILED_OUTPUT_HEIGHT=720
GPU_ID = 0
MAX_NUM_SOURCES = 4
SINK_ELEMENT = "nveglglessink"
PGIE_CONFIG_FILE = "dstest_pgie_config.txt"
TRACKER_CONFIG_FILE = "dstest_tracker_config.txt"

SGIE1_CONFIG_FILE = "dstest_sgie1_config.txt"
SGIE2_CONFIG_FILE = "dstest_sgie2_config.txt"
SGIE3_CONFIG_FILE = "dstest_sgie3_config.txt"

CONFIG_GPU_ID = "gpu-id"
CONFIG_GROUP_TRACKER = "tracker"
CONFIG_GROUP_TRACKER_WIDTH = "tracker-width"
CONFIG_GROUP_TRACKER_HEIGHT = "tracker-height"
CONFIG_GROUP_TRACKER_LL_CONFIG_FILE = "ll-config-file"
CONFIG_GROUP_TRACKER_LL_LIB_FILE = "ll-lib-file"
CONFIG_GROUP_TRACKER_ENABLE_BATCH_PROCESS = "enable-batch-process"

g_num_sources = 0
g_source_id_list = [0] * MAX_NUM_SOURCES
g_eos_list = [False] * MAX_NUM_SOURCES
g_source_enabled = [False] * MAX_NUM_SOURCES
g_source_bin_list = [None] * MAX_NUM_SOURCES

pgie_classes_str= ["Vehicle", "TwoWheeler", "Person","RoadSign"]

uri = ""

loop = None
pipeline = None
streammux = None
sink = None
pgie = None
sgie1 = None
sgie2 = None
sgie3 = None
nvvideoconvert = None
nvosd = None
tiler = None
tracker = None

def decodebin_child_added(child_proxy,Object,name,user_data):
    print("Decodebin child added:", name, "\n")
    if(name.find("decodebin") != -1):
        Object.connect("child-added",decodebin_child_added,user_data)   
    if(name.find("nvv4l2decoder") != -1):
        if (is_aarch64()):
            Object.set_property("enable-max-performance", True)
            Object.set_property("drop-frame-interval", 0)
            Object.set_property("num-extra-surfaces", 0)
        else:
            Object.set_property("gpu_id", GPU_ID)


def cb_newpad(decodebin,pad,data):
    global streammux
    print("In cb_newpad\n")
    caps=pad.get_current_caps()
    gststruct=caps.get_structure(0)
    gstname=gststruct.get_name()

    # Need to check if the pad created by the decodebin is for video and not
    # audio.
    print("gstname=",gstname)
    if(gstname.find("video")!=-1):
        source_id = data
        pad_name = "sink_%u" % source_id
        print(pad_name)
        #Get a sink pad from the streammux, link to decodebin
        sinkpad = streammux.get_request_pad(pad_name)
        if pad.link(sinkpad) == Gst.PadLinkReturn.OK:
            print("Decodebin linked to pipeline")
        else:
            sys.stderr.write("Failed to link decodebin to pipeline\n")


def create_uridecode_bin(index,filename):
    global g_source_id_list
    print("Creating uridecodebin for [%s]" % filename)

    # Create a source GstBin to abstract this bin's content from the rest of the
    # pipeline
    g_source_id_list[index] = index
    bin_name="source-bin-%02d" % index
    print(bin_name)

    # Source element for reading from the uri.
    # We will use decodebin and let it figure out the container format of the
    # stream and the codec and plug the appropriate demux and decode plugins.
    bin=Gst.ElementFactory.make("uridecodebin", bin_name)
    if not bin:
        sys.stderr.write(" Unable to create uri decode bin \n")
    # We set the input uri to the source element
    bin.set_property("uri",filename)
    # Connect to the "pad-added" signal of the decodebin which generates a
    # callback once a new pad for raw data has been created by the decodebin
    bin.connect("pad-added",cb_newpad,g_source_id_list[index])
    bin.connect("child-added",decodebin_child_added,g_source_id_list[index])

    #Set status of the source to enabled
    g_source_enabled[index] = True

    return bin


def stop_release_source(source_id):
    global g_num_sources
    global g_source_bin_list
    global streammux
    global pipeline

    #Attempt to change status of source to be released 
    state_return = g_source_bin_list[source_id].set_state(Gst.State.NULL)

    if state_return == Gst.StateChangeReturn.SUCCESS:
        print("STATE CHANGE SUCCESS\n")
        pad_name = "sink_%u" % source_id
        print(pad_name)
        #Retrieve sink pad to be released
        sinkpad = streammux.get_static_pad(pad_name)
        #Send flush stop event to the sink pad, then release from the streammux
        sinkpad.send_event(Gst.Event.new_flush_stop(False))
        streammux.release_request_pad(sinkpad)
        print("STATE CHANGE SUCCESS\n")
        #Remove the source bin from the pipeline
        pipeline.remove(g_source_bin_list[source_id])
        source_id -= 1
        g_num_sources -= 1

    elif state_return == Gst.StateChangeReturn.FAILURE:
        print("STATE CHANGE FAILURE\n")
    
    elif state_return == Gst.StateChangeReturn.ASYNC:
        state_return = g_source_bin_list[source_id].get_state(Gst.CLOCK_TIME_NONE)
        pad_name = "sink_%u" % source_id
        print(pad_name)
        sinkpad = streammux.get_static_pad(pad_name)
        sinkpad.send_event(Gst.Event.new_flush_stop(False))
        streammux.release_request_pad(sinkpad)
        print("STATE CHANGE ASYNC\n")
        pipeline.remove(g_source_bin_list[source_id])
        source_id -= 1
        g_num_sources -= 1


def delete_sources(data):
    global loop
    global g_num_sources
    global g_eos_list
    global g_source_enabled

    #First delete sources that have reached end of stream
    for source_id in range(MAX_NUM_SOURCES):
        if (g_eos_list[source_id] and g_source_enabled[source_id]):
            g_source_enabled[source_id] = False
            stop_release_source(source_id)

    #Quit if no sources remaining
    if (g_num_sources == 0):
        loop.quit()
        print("All sources stopped quitting")
        return False

    #Randomly choose an enabled source to delete
    source_id = random.randrange(0, MAX_NUM_SOURCES)
    while (not g_source_enabled[source_id]):
        source_id = random.randrange(0, MAX_NUM_SOURCES)
    #Disable the source
    g_source_enabled[source_id] = False
    #Release the source
    print("Calling Stop %d " % source_id)
    stop_release_source(source_id)

    #Quit if no sources remaining
    if (g_num_sources == 0):
        loop.quit()
        print("All sources stopped quitting")
        return False

    return True


def add_sources(data):
    global g_num_sources
    global g_source_enabled
    global g_source_bin_list

    source_id = g_num_sources

    #Randomly select an un-enabled source to add
    source_id = random.randrange(0, MAX_NUM_SOURCES)
    while (g_source_enabled[source_id]):
        source_id = random.randrange(0, MAX_NUM_SOURCES)

    #Enable the source
    g_source_enabled[source_id] = True

    print("Calling Start %d " % source_id)

    #Create a uridecode bin with the chosen source id
    source_bin = create_uridecode_bin(source_id, uri)

    if (not source_bin):
        sys.stderr.write("Failed to create source bin. Exiting.")
        exit(1)
    
    #Add source bin to our list and to pipeline
    g_source_bin_list[source_id] = source_bin
    pipeline.add(source_bin)

    #Set state of source bin to playing
    state_return = g_source_bin_list[source_id].set_state(Gst.State.PLAYING)

    if state_return == Gst.StateChangeReturn.SUCCESS:
        print("STATE CHANGE SUCCESS\n")
        source_id += 1

    elif state_return == Gst.StateChangeReturn.FAILURE:
        print("STATE CHANGE FAILURE\n")
    
    elif state_return == Gst.StateChangeReturn.ASYNC:
        state_return = g_source_bin_list[source_id].get_state(Gst.CLOCK_TIME_NONE)
        source_id += 1

    elif state_return == Gst.StateChangeReturn.NO_PREROLL:
        print("STATE CHANGE NO PREROLL\n")

    g_num_sources += 1

    #If reached the maximum number of sources, delete sources every 10 seconds
    if (g_num_sources == MAX_NUM_SOURCES):
        GLib.timeout_add_seconds(10, delete_sources, g_source_bin_list)
        return False
    
    return True

def bus_call(bus, message, loop):
    global g_eos_list
    t = message.type
    if t == Gst.MessageType.EOS:
        sys.stdout.write("End-of-stream\n")
        loop.quit()
    elif t==Gst.MessageType.WARNING:
        err, debug = message.parse_warning()
        sys.stderr.write("Warning: %s: %s\n" % (err, debug))
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        sys.stderr.write("Error: %s: %s\n" % (err, debug))
        loop.quit()
    elif t == Gst.MessageType.ELEMENT:
        struct = message.get_structure()
        #Check for stream-eos message
        if struct is not None and struct.has_name("stream-eos"):
            parsed, stream_id = struct.get_uint("stream-id")
            if parsed:
                #Set eos status of stream to True, to be deleted in delete-sources
                print("Got EOS from stream %d" % stream_id)
                g_eos_list[stream_id] = True
    return True

def main(args):
    global g_num_sources
    global g_source_bin_list
    global uri

    global loop
    global pipeline
    global streammux
    global sink
    global pgie
    global sgie1
    global sgie2
    global sgie3
    global nvvideoconvert
    global nvosd
    global tiler
    global tracker
     # Check input arguments
    if len(args) != 2:
        sys.stderr.write("usage: %s <uri1> \n" % args[0])
        sys.exit(1)

    num_sources=len(args)-1

    # Standard GStreamer initialization
    Gst.init(None)

    # Create gstreamer elements */
    # Create Pipeline element that will form a connection of other elements
    print("Creating Pipeline \n ")
    pipeline = Gst.Pipeline()
    is_live = False

    if not pipeline:
        sys.stderr.write(" Unable to create Pipeline \n")
    print("Creating streammux \n ")

    # Create nvstreammux instance to form batches from one or more sources.
    streammux = Gst.ElementFactory.make("nvstreammux", "Stream-muxer")
    if not streammux:
        sys.stderr.write(" Unable to create NvStreamMux \n")

    streammux.set_property("batched-push-timeout", 25000)
    streammux.set_property("batch-size", 30)
    streammux.set_property("gpu_id", GPU_ID)

    pipeline.add(streammux)
    streammux.set_property("live-source", 1)
    uri = args[1]
    for i in range(num_sources):
        print("Creating source_bin ",i," \n ")
        uri_name=args[i+1]
        if uri_name.find("rtsp://") == 0 :
            is_live = True
        #Create first source bin and add to pipeline
        source_bin=create_uridecode_bin(i, uri_name)
        if not source_bin:
            sys.stderr.write("Failed to create source bin. Exiting. \n")
            sys.exit(1)
        g_source_bin_list[i] = source_bin
        pipeline.add(source_bin)

    g_num_sources = num_sources

    print("Creating Pgie \n ")
    pgie = Gst.ElementFactory.make("nvinfer", "primary-inference")
    if not pgie:
        sys.stderr.write(" Unable to create pgie \n")

    print("Creating nvtracker \n ")
    tracker = Gst.ElementFactory.make("nvtracker", "tracker")
    if not tracker:
        sys.stderr.write(" Unable to create tracker \n")

    print("Creating tiler \n ")
    tiler=Gst.ElementFactory.make("nvmultistreamtiler", "nvtiler")
    if not tiler:
        sys.stderr.write(" Unable to create tiler \n")

    print("Creating nvvidconv \n ")
    nvvideoconvert = Gst.ElementFactory.make("nvvideoconvert", "convertor")
    if not nvvideoconvert:
        sys.stderr.write(" Unable to create nvvidconv \n")

    print("Creating nvosd \n ")
    nvosd = Gst.ElementFactory.make("nvdsosd", "onscreendisplay")
    if not nvosd:
        sys.stderr.write(" Unable to create nvosd \n")

    if(is_aarch64()):
        print("Creating transform \n ")
        transform=Gst.ElementFactory.make("nvegltransform", "nvegl-transform")
        if not transform:
            sys.stderr.write(" Unable to create transform \n")

    sgie1 = Gst.ElementFactory.make("nvinfer", "secondary1-nvinference-engine")
    if not sgie1:
        sys.stderr.write(" Unable to make sgie1 \n")

    sgie2 = Gst.ElementFactory.make("nvinfer", "secondary2-nvinference-engine")
    if not sgie1:
        sys.stderr.write(" Unable to make sgie2 \n")

    sgie3 = Gst.ElementFactory.make("nvinfer", "secondary3-nvinference-engine")
    if not sgie3:
        sys.stderr.write(" Unable to make sgie3 \n")


    print("Creating EGLSink \n")
    sink = Gst.ElementFactory.make(SINK_ELEMENT, "nvvideo-renderer")
    if not sink:
        sys.stderr.write(" Unable to create egl sink \n")

    if is_live:
        print("Atleast one of the sources is live")
        streammux.set_property('live-source', 1)

    #Set streammux width and height
    streammux.set_property('width', MUXER_OUTPUT_WIDTH)
    streammux.set_property('height', MUXER_OUTPUT_HEIGHT)
    #Set pgie, sgie1, sgie2, and sgie3 configuration file paths
    pgie.set_property('config-file-path', PGIE_CONFIG_FILE)
    sgie1.set_property('config-file-path', SGIE1_CONFIG_FILE)
    sgie2.set_property('config-file-path', SGIE2_CONFIG_FILE)
    sgie3.set_property('config-file-path', SGIE3_CONFIG_FILE)

    #Set properties of tracker
    config = configparser.ConfigParser()
    config.read(TRACKER_CONFIG_FILE)
    config.sections()

    for key in config['tracker']:
        if key == 'tracker-width' :
            tracker_width = config.getint('tracker', key)
            tracker.set_property('tracker-width', tracker_width)
        if key == 'tracker-height' :
            tracker_height = config.getint('tracker', key)
            tracker.set_property('tracker-height', tracker_height)
        if key == 'gpu-id' :
            tracker_gpu_id = config.getint('tracker', key)
            tracker.set_property('gpu_id', tracker_gpu_id)
        if key == 'll-lib-file' :
            tracker_ll_lib_file = config.get('tracker', key)
            tracker.set_property('ll-lib-file', tracker_ll_lib_file)
        if key == 'll-config-file' :
            tracker_ll_config_file = config.get('tracker', key)
            tracker.set_property('ll-config-file', tracker_ll_config_file)
        if key == 'enable-batch-process' :
            tracker_enable_batch_process = config.getint('tracker', key)
            tracker.set_property('enable_batch_process', tracker_enable_batch_process)

    #Set necessary properties of the nvinfer element, the necessary ones are:
    pgie_batch_size=pgie.get_property("batch-size")
    if(pgie_batch_size < MAX_NUM_SOURCES):
        print("WARNING: Overriding infer-config batch-size",pgie_batch_size," with number of sources ", num_sources," \n")
    pgie.set_property("batch-size",MAX_NUM_SOURCES)

    #Set gpu IDs of the inference engines
    pgie.set_property("gpu_id", GPU_ID)
    sgie1.set_property("gpu_id", GPU_ID)
    sgie2.set_property("gpu_id", GPU_ID)
    sgie3.set_property("gpu_id", GPU_ID)

    #Set tiler properties
    tiler_rows=int(math.sqrt(num_sources))
    tiler_columns=int(math.ceil((1.0*num_sources)/tiler_rows))
    tiler.set_property("rows",tiler_rows)
    tiler.set_property("columns",tiler_columns)
    tiler.set_property("width", TILED_OUTPUT_WIDTH)
    tiler.set_property("height", TILED_OUTPUT_HEIGHT)

    #Set gpu IDs of tiler, nvvideoconvert, and nvosd
    tiler.set_property("gpu_id", GPU_ID)
    nvvideoconvert.set_property("gpu_id", GPU_ID)
    nvosd.set_property("gpu_id", GPU_ID)

    #Set gpu ID of sink if not aarch64
    if(not is_aarch64()):
        sink.set_property("gpu_id", GPU_ID)

    print("Adding elements to Pipeline \n")
    pipeline.add(pgie)
    pipeline.add(tracker)
    pipeline.add(sgie1)
    pipeline.add(sgie2)
    pipeline.add(sgie3)
    pipeline.add(tiler)
    pipeline.add(nvvideoconvert)
    pipeline.add(nvosd)
    pipeline.add(sink)

    if is_aarch64():
        pipeline.add(transform)

    # We link elements in the following order:
    # sourcebin -> streammux -> nvinfer -> nvtracker -> nvdsanalytics ->
    # nvtiler -> nvvideoconvert -> nvdsosd -> (if aarch64, transform ->) sink
    print("Linking elements in the Pipeline \n")
    streammux.link(pgie)
    pgie.link(tracker)
    tracker.link(sgie1)
    sgie1.link(sgie2)
    sgie2.link(sgie3)
    sgie3.link(tiler)
    tiler.link(nvvideoconvert)
    nvvideoconvert.link(nvosd)
    if is_aarch64():
        nvosd.link(transform)
        transform.link(sink)
    else:
        nvosd.link(sink)

    sink.set_property("sync", 0)
    sink.set_property("qos",0)

    # create an event loop and feed gstreamer bus mesages to it
    loop = GLib.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect ("message", bus_call, loop)

    pipeline.set_state(Gst.State.PAUSED)

    # List the sources
    print("Now playing...")
    for i, source in enumerate(args):
        if (i != 0):
            print(i, ": ", source)

    print("Starting pipeline \n")
    # start play back and listed to events		
    pipeline.set_state(Gst.State.PLAYING)

    GLib.timeout_add_seconds(10, add_sources, g_source_bin_list)

    try:
        loop.run()
    except:
        pass
    # cleanup
    print("Exiting app\n")
    pipeline.set_state(Gst.State.NULL)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
