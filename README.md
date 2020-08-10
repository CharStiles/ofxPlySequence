PlySequence
=====================================

Introduction
------------
This addon for playing large sequences of point cloud PLY files. This converts the point clouds to PNGs and plays them back using shaders to read the point cloud data off of tif files. Its sort of utilizing image compresion for point cloud compression. No one asked for this.

License
-------
[MIT License](https://en.wikipedia.org/wiki/MIT_License)

Installation
------------
Download this and drop it into `openFrameworks/addons/` folder. Your point clouds go into the data folder in your project.

Use
------------

First you call ```plySeqObject.writePointCloudsAsImages()``` Which will open up a file browser prompt that will direct you to point it to a folder of ascii point clouds. 

Then you call ```plySeqObject.setup()``` to prepare the images to be drawn as point clouds

Then in your draw loop call ```plySeqObject.draw()``` 

Compatibility
------------
OF 10 and 11

Known issues
------------
This is in development. It only works on ascii ply point clouds.
This is a very lossy process. 

### Version 0.01 (Date):
init


