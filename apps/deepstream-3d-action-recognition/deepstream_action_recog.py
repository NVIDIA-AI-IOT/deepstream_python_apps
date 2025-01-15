import sys
sys.path.append("../")
import gi

gi.require_version("Gst", "1.0")
from gi.repository import Gst, GObject, GLib
import numpy as np
from common.platform_info import PlatformInfo
from common.bus_call import bus_call
from common.FPS import PERF_DATA
from ctypes import *
import math
import argparse
from pathlib import Path
import ctypes
import tracemalloc

import pyds

no_display = False
perf_data = None

MAX_STR_LEN = 2048
MAX_LABEL_SIZE = 128
MAX_CLASS_LEN = 5
MODEL_3D_SHAPES = 5
FPS_INTERVAL = 30
OSD_PROCESS_MODE = 1
OSD_DISPLAY_TEXT = 1
GST_CAPS_FEATURES_NVMM = "memory:NVMM"
MUXER_BATCH_TIMEOUT_USEC = 34000
TILED_OUTPUT_WIDTH = 1280
TILED_OUTPUT_HEIGHT = 720
PREPROCESS_CONFIG = "/opt/nvidia/deepstream/deepstream-7.1/sources/apps/sample_apps/deepstream-3d-action-recognition/config_preprocess_3d_custom.txt"

pgie_classes_str = ["push", "fall_floor" , "walk", "run", "ride_bike"]


def pgie_src_pad_buffer_probe(pad, info, u_data):
    frame_number = 0
   
    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer ")
        return

    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    
    l_user_meta=batch_meta.batch_user_meta_list
    while l_user_meta is not None:
        try:
            user_meta=pyds.NvDsUserMeta.cast(l_user_meta.data)
        except StopIteration:
            break
        if(user_meta and user_meta.base_meta.meta_type==pyds.NvDsMetaType.NVDS_PREPROCESS_BATCH_META):
            try:
                preprocess_batchmeta = pyds.GstNvDsPreProcessBatchMeta.cast(user_meta.user_meta_data)
            except StopIteration:
                break
            model_dims = ""
            if preprocess_batchmeta.tensor_meta:
                if len(preprocess_batchmeta.tensor_meta.tensor_shape) == MODEL_3D_SHAPES:
                    model_dims = "3D: AR - "
                else:
                    model_dims = "2D: AR - "
            for roi_meta in preprocess_batchmeta.roi_vector:
                l_user = roi_meta.roi_user_meta_list
                while l_user is not None:
                    try:
                        user_meta=pyds.NvDsUserMeta.cast(l_user.data)
                    except StopIteration:
                        break
                
                    if user_meta.base_meta.meta_type == pyds.NvDsMetaType.NVDSINFER_TENSOR_OUTPUT_META:
                        tensor_meta = pyds.NvDsInferTensorMeta.cast(user_meta.user_meta_data)
                        max_prob = 0
                        class_id = 0
                        
                        capsule = tensor_meta.out_buf_ptrs_host
                        buffer_ptr = pyds.get_ptr(capsule)
                        ctypes_buffer = ctypes.cast(buffer_ptr, ctypes.POINTER(ctypes.c_float))
                        buffer = np.ctypeslib.as_array(ctypes_buffer, shape=(len(pgie_classes_str),))
                        
                        for i in range(0, len(pgie_classes_str)):
                            if buffer[i] > max_prob:
                                max_prob = buffer[i]
                                class_id = i
                        label = ""
                        if class_id < MAX_CLASS_LEN:
                            label = pgie_classes_str[class_id]
                        # print(f"output tensor result: cls_id: {class_id}, scrore:{max_prob}, label: {label}")
                    l_classifier = roi_meta.classifier_meta_list 
                    while l_classifier is not None:
                        try:
                            classifier_meta = pyds.NvDsClassifierMeta.cast(l_classifier.data)
                        except StopIteration:
                            break
                        l_label = classifier_meta.label_info_list
                        while l_label is not None:
                            try:
                                label_info = pyds.NvDsLabelInfo.cast(l_label.data)
                            except StopIteration:
                                break
                            display_meta = pyds.nvds_acquire_display_meta_from_pool(batch_meta)
                            display_meta.num_labels = 1
                            txt_params = display_meta.text_params[0]
                            
                            txt_params.display_text = f"{model_dims}: {label_info.result_label}"
                            print(f"classification result: cls_id: {label_info.result_class_id}, label: {label_info.result_label}")
                            
                            txt_params.x_offset = int(roi_meta.roi.left)
                            txt_params.y_offset = int(np.max([roi_meta.roi.top-10, 0]))
                            
                            txt_params.font_params.font_name = "Serif"
                            txt_params.font_params.font_size = 12
                            txt_params.font_params.font_color.red = 1.0
                            txt_params.font_params.font_color.green = 1.0
                            txt_params.font_params.font_color.blue = 1.0
                            txt_params.font_params.font_color.alpha = 1.0
                            
                            txt_params.set_bg_clr = 1
                            txt_params.text_bg_clr.red = 0.0
                            txt_params.text_bg_clr.green = 0.0
                            txt_params.text_bg_clr.blue = 0.0
                            txt_params.text_bg_clr.alpha = 1.0
                            print("frame string:   ", pyds.get_string(txt_params.display_text))
                            pyds.nvds_add_display_meta_to_frame(roi_meta.frame_meta, display_meta)

                            try:
                                l_label = l_label.next
                            except StopIteration:
                                break
                        try:
                            l_classifier = l_classifier.next
                        except StopIteration:
                            break    
                    try:
                        l_user = l_user.next
                    except StopIteration:
                        break
        try:
            l_user_meta = l_user_meta.next
        except StopIteration:
            break
        
    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break
        
        frame_number = frame_meta.frame_num
        print("Frame Number=", frame_number)    
        stream_index = "stream{0}".format(frame_meta.pad_index)
        global perf_data
        perf_data.update_fps(stream_index)
        try:
            l_frame=l_frame.next
        except StopIteration:
            break

    return Gst.PadProbeReturn.OK


def cb_newpad(decodebin, decoder_src_pad, data):
    print("In cb_newpad\n")
    caps = decoder_src_pad.get_current_caps()
    if not caps:
        caps = decoder_src_pad.query_caps()
    gststruct = caps.get_structure(0)
    gstname = gststruct.get_name()
    source_bin = data
    features = caps.get_features(0)

    if gstname.find("video") != -1:
        if features.contains(GST_CAPS_FEATURES_NVMM):
            # Get the source bin ghost pad
            bin_ghost_pad = source_bin.get_static_pad("src")
            if not bin_ghost_pad.set_target(decoder_src_pad):
                sys.stderr.write(
                    "Failed to link decoder src pad to source bin ghost pad\n"
                )
        else:
            sys.stderr.write(" Error: Decodebin did not pick nvidia decoder plugin.\n")


def decodebin_child_added(child_proxy, Object, name, user_data):
    print("Decodebin child added:", name, "\n")
    if name.find("decodebin") != -1:
        Object.connect("child-added", decodebin_child_added, user_data)


def create_source_bin(index, uri):
    print("Creating source bin")

    # Create a source GstBin to abstract this bin's content from the rest of the
    # pipeline
    bin_name = "source-bin-%02d" % index
    print(bin_name)
    nbin = Gst.Bin.new(bin_name)
    if not nbin:
        sys.stderr.write(" Unable to create source bin \n")

    # Source element for reading from the uri.
    # We will use decodebin and let it figure out the container format of the
    # stream and the codec and plug the appropriate demux and decode plugins.

    uri_decode_bin = Gst.ElementFactory.make("uridecodebin", "uri-decode-bin")
    if not uri_decode_bin:
        sys.stderr.write(" Unable to create uri decode bin \n")
    # We set the input uri to the source element
    uri_decode_bin.set_property("uri", uri)
    # Connect to the "pad-added" signal of the decodebin which generates a
    # callback once a new pad for raw data has beed created by the decodebin
    uri_decode_bin.connect("pad-added", cb_newpad, nbin)
    uri_decode_bin.connect("child-added", decodebin_child_added, nbin)

    # We need to create a ghost pad for the source bin which will act as a proxy
    # for the video decoder src pad. The ghost pad will not have a target right
    # now. Once the decode bin creates the video decoder and generates the
    # cb_newpad callback, we will set the ghost pad target to the video decoder
    # src pad.
    Gst.Bin.add(nbin, uri_decode_bin)
    bin_pad = nbin.add_pad(Gst.GhostPad.new_no_target("src", Gst.PadDirection.SRC))
    if not bin_pad:
        sys.stderr.write(" Failed to add ghost pad in source bin \n")
        return None
    return nbin


# Create the pipeline and elements
def main(args, requested_pgie=None, config=None, disable_probe=True):
    global perf_data
    perf_data = PERF_DATA(len(args))

    number_sources = len(args)

    platform_info = PlatformInfo()

    Gst.init(None)

    print("Creating Pipeline \n ")
    pipeline = Gst.Pipeline()
    is_live = False

    streammux = Gst.ElementFactory.make("nvstreammux", "Stream-muxer")
    if not streammux:
        sys.stderr.write(" Unable to create NvStreamMux \n")

    pipeline.add(streammux)

    for i in range(number_sources):
        print("Creating source_bin ", i, " \n ")
        uri_name = args[i]
        if uri_name.find("rtsp://") == 0:
            is_live = True
        source_bin = create_source_bin(i, uri_name)
        if not source_bin:
            sys.stderr.write("Unable to create source bin \n")
        pipeline.add(source_bin)
        padname = "sink_%u" % i
        sinkpad = streammux.request_pad_simple(padname)
        if not sinkpad:
            sys.stderr.write("Unable to create sink pad bin \n")
        srcpad = source_bin.get_static_pad("src")
        if not srcpad:
            sys.stderr.write("Unable to create src pad bin \n")
        srcpad.link(sinkpad)

    preprocess = Gst.ElementFactory.make("nvdspreprocess", "preprocess-plugin")
    if not preprocess:
        sys.stderr.write(" Unable to create preprcoess")

    print("Creating Pgie \n ")
    if requested_pgie != None and (
        requested_pgie == "nvinferserver" or requested_pgie == "nvinferserver-grpc"
    ):
        pgie = Gst.ElementFactory.make("nvinferserver", "primary-inference")
    elif requested_pgie != None and requested_pgie == "nvinfer":
        pgie = Gst.ElementFactory.make("nvinfer", "primary-inference")
    else:
        pgie = Gst.ElementFactory.make("nvinfer", "primary-inference")

    if not pgie:
        sys.stderr.write(" Unable to create pgie :  %s\n" % requested_pgie)

    queue1 = Gst.ElementFactory.make("queue", "queue1")
    queue2 = Gst.ElementFactory.make("queue", "queue2")
    queue3 = Gst.ElementFactory.make("queue", "queue3")
    queue4 = Gst.ElementFactory.make("queue", "queue4")
    queue5 = Gst.ElementFactory.make("queue", "queue5")
    queue6 = Gst.ElementFactory.make("queue", "queue6")

    print("Creating tiler \n ")
    tiler = Gst.ElementFactory.make("nvmultistreamtiler", "nvtiler")
    if not tiler:
        sys.stderr.write(" Unable to create tiler \n")

    print("Creating nvvidconv \n ")
    nvvidconv = Gst.ElementFactory.make("nvvideoconvert", "convertor")
    if not nvvidconv:
        sys.stderr.write(" Unable to create nvvidconv \n")
    print("Creating nvosd \n ")
    nvosd = Gst.ElementFactory.make("nvdsosd", "onscreendisplay")
    if not nvosd:
        sys.stderr.write(" Unable to create nvosd \n")

    if no_display:
        print("Creating Fakesink \n")
        sink = Gst.ElementFactory.make("fakesink", "fakesink")
        sink.set_property("enable-last-sample", 0)
        sink.set_property("sync", 0)
    else:
        if platform_info.is_integrated_gpu():
            print("Creating nv3dsink \n")
            sink = Gst.ElementFactory.make("nv3dsink", "nv3d-sink")
            if not sink:
                sys.stderr.write(" Unable to create nv3dsink \n")
        else:
            if platform_info.is_platform_aarch64():
                print("Creating nv3dsink \n")
                sink = Gst.ElementFactory.make("nv3dsink", "nv3d-sink")
            else:
                print("Creating EGLSink \n")
                sink = Gst.ElementFactory.make("nveglglessink", "nvvideo-renderer")
                sink.set_property("sync", 0)
            if not sink:
                sys.stderr.write(" Unable to create egl sink \n")

    if not sink:
        sys.stderr.write(" Unable to create sink element \n")

    if is_live:
        print("At least one of the sources is live")
        streammux.set_property("live-source", 1)

    streammux.set_property("width", 1280)
    streammux.set_property("height", 720)
    streammux.set_property("batch-size", number_sources)
    streammux.set_property("batched-push-timeout", MUXER_BATCH_TIMEOUT_USEC)
    
    if requested_pgie == "nvinferserver" and config != None:
        pgie.set_property("config-file-path", config)
    elif requested_pgie == "nvinferserver-grpc" and config != None:
        pgie.set_property("config-file-path", config)
    elif requested_pgie == "nvinfer" and config != None:
        pgie.set_property("config-file-path", config)
    else:
        pgie.set_property("config-file-path", "action_recognition.txt")
        
    pgie_batch_size = pgie.get_property("batch-size")
    
    preprocess.set_property("config-file", PREPROCESS_CONFIG)
    
    if pgie_batch_size != number_sources:
        print(
            "WARNING: Overriding infer-config batch-size",
            pgie_batch_size,
            " with number of sources ",
            number_sources,
            " \n",
        )
        pgie.set_property("batch-size", number_sources)
    tiler_rows = int(math.sqrt(number_sources))
    tiler_columns = int(math.ceil((1.0 * number_sources) / tiler_rows))
    tiler.set_property("rows", tiler_rows)
    tiler.set_property("columns", tiler_columns)
    tiler.set_property("width", TILED_OUTPUT_WIDTH)
    tiler.set_property("height", TILED_OUTPUT_HEIGHT)
    if platform_info.is_integrated_gpu():
        tiler.set_property("compute-hw", 2)
    else:
        tiler.set_property("compute-hw", 1)
    sink.set_property("qos", 0)

    print("Adding elements to Pipeline \n")
    if no_display:
        pipeline.add(queue1)
        pipeline.add(preprocess)
        pipeline.add(queue2)
        pipeline.add(pgie)
        pipeline.add(queue3)
        pipeline.add(sink)
        try:
            print("Linking elements in the Pipeline without sink\n")
            streammux.link(queue1)
            queue1.link(preprocess)
            preprocess.link(queue2)
            queue2.link(pgie)
            pgie.link(queue3)
            queue3.link(sink)
        except Exception as e:
            print("error in linking:   ", e)
    else:
        pipeline.add(queue1)
        pipeline.add(preprocess)
        pipeline.add(queue2)
        pipeline.add(pgie)
        pipeline.add(queue3)
        pipeline.add(tiler)
        pipeline.add(queue4)
        pipeline.add(nvvidconv)
        pipeline.add(queue5)
        pipeline.add(nvosd)
        pipeline.add(queue6)
        pipeline.add(sink)
        try:
            print("Linking elements in the Pipeline with sink\n")
            streammux.link(queue1)
            queue1.link(preprocess)
            preprocess.link(queue2)
            queue2.link(pgie)
            pgie.link(queue3)
            queue3.link(tiler)
            tiler.link(queue4)
            queue4.link(nvvidconv)
            nvvidconv.link(queue5)
            queue5.link(nvosd)
            nvosd.link(queue6)
            queue6.link(sink)
        except Exception as e:
            print("error in linking:   ", e)

    loop = GLib.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect("message", bus_call, loop)
    pgie_src_pad = pgie.get_static_pad("src")
    if not pgie_src_pad:
        print(" Unable to get src pad \n")
        sys.stderr.write(" Unable to get src pad \n")
    else:
        pgie_src_pad.add_probe(Gst.PadProbeType.BUFFER, pgie_src_pad_buffer_probe, 0)
        # perf callback function to print fps every 5 sec
        GLib.timeout_add(1000, perf_data.perf_print_callback)

    # List the sources
    print("Now playing...")
    for i, source in enumerate(args):
        print(i, ": ", source)

    print("Starting pipeline \n")
    # start play back and listed to events
    pipeline.set_state(Gst.State.PLAYING)
    try:
        loop.run()
    except:
        pass
    # cleanup
    print("Exiting app\n")
    pipeline.set_state(Gst.State.NULL)


def parse_args():

    parser = argparse.ArgumentParser(
        prog="deepstream_action_recog",
        description="deepstream action recognition pipeline,  multi stream, multi model inference reference app",
    )
    parser.add_argument(
        "-i",
        "--input",
        help="Path to input streams",
        nargs="+",
        metavar="URIs",
        default=["file:///opt/nvidia/deepstream/deepstream-7.1/samples/streams/sample_ride_bike.mov",
                 "file:///opt/nvidia/deepstream/deepstream-7.1/samples/streams/sample_push.mov",
                 "file:///opt/nvidia/deepstream/deepstream-7.1/samples/streams/sample_walk.mov",
                 "file:///opt/nvidia/deepstream/deepstream-7.1/samples/streams/sample_run.mov"],
        # required=True,
    )
    parser.add_argument(
        "-c",
        "--configfile",
        metavar="config_location.txt",
        default="dsaction_recognition_config.txt",
        help="Choose the config-file to be used with specified pgie",
    )
    parser.add_argument(
        "-g",
        "--pgie",
        default="nvinfer",
        help="Choose Primary GPU Inference Engine",
        choices=["nvinfer", "nvinferserver", "nvinferserver-grpc"],
    )
    parser.add_argument(
        "--no-display",
        action="store_true",
        default=False,
        dest="no_display",
        help="Disable display of video output",
    )
    # Check input arguments
    # if len(sys.argv) == 1:
    #     parser.print_help(sys.stderr)
    #     sys.exit(1)
    args = parser.parse_args()

    stream_paths = args.input
    pgie = args.pgie
    config = args.configfile
    global no_display
    global silent
    global file_loop
    no_display = args.no_display

    if config and not pgie or pgie and not config:
        sys.stderr.write(
            "\nEither pgie or configfile is missing. Please specify both! Exiting...\n\n\n\n"
        )
        parser.print_help()
        sys.exit(1)
    if config:
        config_path = Path(config)
        if not config_path.is_file():
            sys.stderr.write(
                "Specified config-file: %s doesn't exist. Exiting...\n\n" % config
            )
            sys.exit(1)
    print(args)
    return stream_paths, pgie, config


if __name__ == "__main__":
    stream_paths, pgie, config = parse_args()
    sys.exit(main(stream_paths, pgie, config))
