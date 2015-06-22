# OscStreamer

OscStreamer is a lightweight C++ library for streaming and broadcasting OSC data over UDP using [oscpack](http://www.rossbencina.com/code/oscpack).


### Usage

```cpp
OscStreamer *oscStreamer;
oscStreamer = new OscStreamer("192.168.1.101", 3000);
oscStreamer->init();

int data = 0;
while (true) {
    oscStreamer->send(data++);
}

delete oscStreamer;

```

### Examples

- **BasicOscServer**: Streaming integer data 
- **MotiveOscStreamer**: Streaming 6dof rigid body data witg OptiTrack [Motive API](http://www.optitrack.com/products/motive/)
- **NatNetOscStreamer**: Streaming 6dof rigid body data with OptiTrack [NatNet SDK](http://www.optitrack.com/products/natnet-sdk/) 