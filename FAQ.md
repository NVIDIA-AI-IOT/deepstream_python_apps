# Frequently Asked Questions and Troubleshooting Guide

* [Application fails to work with mp4 stream](#faq0)  
* [Ctrl-C does not stop the app during engine file generation](#faq1)  
* [Application fails to create gst elements](#faq2)  
* [GStreamer debugging](#faq3)  
* [Application stuck with no playback](#faq4)  
* [Error on setting string field](#faq5)  
* [Pipeline unable to perform at real time](#faq6)  
* [Triton container problems with multi-GPU setup](#faq7)
* [ModuleNotFoundError: No module named 'pyds'] (#faq8)

<a name="faq0"></a>
### Application fails to work with mp4 stream
Deepstream-test1,2 and 4 apps only work with H264 elementary streams such as sample_720p.h264 provided with the DeepStream SDK. These include test apps 1, 2 and 4. Attempting to use other such types of streams will result in the following error:  
```
Error: gst-stream-error-quark: Internal data stream error. (1): gstbaseparse.c(3611): gst_base_parse_loop ():   /GstPipeline:pipeline0/GstH264Parse:h264-parser:  
streaming stopped, reason not-negotiated (-4)  
```
Deepstream-test3 supports various stream types including mp4 and RTSP. Please see the app README for usage.  

<a name="faq1"></a>
### Ctrl-C does not stop the app during engine file generation
This is a limitation of Python signal handling:  
https://docs.python.org/3/library/signal.html  
"A long-running calculation implemented purely in C (such as regular expression matching on a large body of text) may run uninterrupted for an arbitrary amount of time, regardless of any signals received. The Python signal handlers will be called when the calculation finishes."  

To work around this:  
1. Use ctrl-z to bg the process  
2. Optionally run "jobs" if there are potentially multiple bg processes:  
    $ jobs  
    [1]-  Stopped                 python3 deepstream_test_1.py /opt/nvidia/deepstream/deepstream-4.0/samples/streams/sample_720p.h264  (wd: /opt/nvidia/deepstream/deepstream-4.0/sources/apps/python/deepstream-test1)  
    [2]+  Stopped                 python3 deepstream_test_2.py /opt/nvidia/deepstream/deepstream-4.0/samples/streams/sample_720p.h264  
3. Kill the bg job:  
    $ kill %<job number, 1 or 2 from above. e.g. kill %1>  


<a name="faq2"></a>
### Application fails to create gst elements 
As with DeepStream SDK, if the application runs into errors, cannot create gst elements, try again after removing gstreamer cache:  
   rm ${HOME}/.cache/gstreamer-1.0/registry.x86_64.bin


<a name="faq3"></a>
### GStreamer debugging
General GStreamer debugging: set debug level on the command line:  
  ```
  GST_DEBUG=<level> python3 <app> [options]
  ```

<a name="faq4"></a>
### Application stuck with no playback
The application appears to be stuck without any playback activity.  
  One possible cause is incompatible input type. Some of the sample apps only support H264 elementary streams.  


<a name="faq5"></a>
### Error on setting string field  
  ```
  terminate called after throwing an instance of 'pybind11::error_already_set'  
    what():  TypeError: (): incompatible function arguments. The following argument types are supported:  
      1. (arg0: pyds.<struct, e.g. NvDsEventMsgMeta>, arg1: str) -> None  

  Invoked with: <pyds.<struct, e.g. NvDsEventMsgMeta> object at 0x7ffa93d2fce0>, <int, e.g. 140710457366960>  
  ```

  This can happen if the string field is being set with another string field, e.g.:  
  ```
  dstmeta.sensorStr = srcmeta.sensorStr
  ```

  Remember from the String Access section above that reading ```srcmeta.sensorStr``` directly returns an int, not string.  
  The proper way to copy the string field in this case is:  
  ```
  dstmeta.sensorStr = pyds.get_string(srcmeta.sensorStr)
  ```

<a name="faq6"></a>
### Pipeline unable to perform at real time
  WARNING: A lot of buffers are being dropped. (13): gstbasesink.c(2902):   
  gst_base_sink_is_too_late (): /GstPipeline:pipeline0/GstEglGlesSink:nvvideo-renderer:  
  There may be a timestamping problem, or this computer is too slow.  

  Answer:  
  This could be thrown from any GStreamer app when the pipeline through-put is low  
  resulting in late buffers at the sink plugin.  
  This could be a hardware capability limitation or expensive software calls  
  that hinder pipeline buffer flow.  
  With python, there is a possibility for such an induced delay in software.  
  This is with regards to the probe() callbacks an user could leverage  
  for metadata extraction and other use-cases as demonstrated in our test-apps.  

  Please NOTE:  
  a) probe() callbacks are synchronous and thus holds the buffer  
     (info.get_buffer()) from traversing the pipeline until user return.  
  b) loops inside probe() callback could be costly in python.  
  

<a name="faq7"></a>
### Triton container problems with multi-GPU setup
The Triton Inference Server plugin currently only supports single-GPU usage.
When running the docker, please specify  
`--gpus device=<GPU ID>`  
e.g.: `--gpus device=0`

  
<a name="faq8"></a>  
### ModuleNotFoundError: No module named 'pyds'
The pyds extension is installed under /opt/nvidia/deepstream/deepstream/lib
The sample applications all include this path via the is_aarch_64 module.
A setup.py is also provided to install this extension into standard path.
Currently this needs to be run manually:
   $ cd /opt/nvidia/deepstream/deepstream/lib
   $ python3 setup.py install
