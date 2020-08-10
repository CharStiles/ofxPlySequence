# All variables and this file are optional, if they are not present the PG and the
# makefiles will try to parse the correct values from the file system.
#
# Variables that specify exclusions can use % as a wildcard to specify that anything in
# that position will match. A partial path can also be specified to, for example, exclude
# a whole folder from the parsed paths from the file system
#
# Variables can be specified using = or +=
# = will clear the contents of that variable both specified from the file or the ones parsed
# from the file system
# += will add the values to the previous ones in the file or the ones parsed from the file 
# system
# 
# The PG can be used to detect errors in this file, just create a new project with this addon 
# and the PG will write to the console the kind of error and in which line it is

meta:
	ADDON_NAME = ofxPlySequence
	ADDON_DESCRIPTION = Play PLY sequences by compressing them. Very lossy, but you can comfortably play 1000 ply files w 100,000 points
	ADDON_AUTHOR = @charstiles
	ADDON_TAGS = "addon" "template"
	ADDON_URL = http://github.com/charstiles/ofxPlySequence

common:
	
	
linux64:
	# linux only, any library that should be included in the project using
	# pkg-config
	# ADDON_PKG_CONFIG_LIBRARIES =
vs:
	# After compiling copy the following dynamic libraries to the executable directory
	# only windows visual studio
	# ADDON_DLLS_TO_COPY = 
	
linuxarmv6l:
linuxarmv7l:
android/armeabi:	
android/armeabi-v7a:	
osx:
	# osx/iOS only, any framework that should be included in the project
	# ADDON_FRAMEWORKS =
ios:
tvos:

