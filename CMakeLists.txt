cmake_minimum_required(VERSION 3.13)
if (DEFINED MCU)
	# Setting up the toolchain
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/cortex.cmake")
endif()
# Project information
project(SD
	VERSION 1.0.1
	DESCRIPTION "SD driver"
	LANGUAGES C CXX
)
if (DEFINED MCU)
	# Grab the processor and set up definitions and compile options
	include(${CMAKE_SOURCE_DIR}/cmake/config_mcu.cmake)
	configMcu(${MCU})
	include(FetchContent)
	# Fetch core
	FetchContent_Declare(
		core
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/core.git
		GIT_TAG v1.0.1
	)
	FetchContent_MakeAvailable(core)
	# Add the library target
	add_library(sd
		src/sd/FatFile.cc
		src/sd/FatFileLFN.cc
		src/sd/FatFilePrint.cc
		src/sd/FatFileSFN.cc
		src/sd/FatVolume.cc
		src/sd/FmtNumber.cc
		src/sd/fstream.cc
		src/sd/istream.cc
		src/sd/MinimumSerial.cc
		src/sd/ostream.cc
		src/sd/SdioCardEX.cc
		src/sd/SdioTeensy.cc
		src/sd/StdioStream.cc
		include/sd/BlockDriver.h
		include/sd/FreeStack.h
		include/sd/MinimumSerial.h
		include/sd/SdFat.h
		include/sd/SdFatConfig.h
		include/sd/sdios.h
		include/sd/SysCall.h
		include/sd/FatLib/ArduinoFiles.h
		include/sd/FatLib/ArduinoStream.h
		include/sd/FatLib/BaseBlockDriver.h
		include/sd/FatLib/bufstream.h
		include/sd/FatLib/FatApiConstants.h
		include/sd/FatLib/FatFile.h
		include/sd/FatLib/FatFileSystem.h
		include/sd/FatLib/FatLibConfig.h
		include/sd/FatLib/FatLib.h
		include/sd/FatLib/FatStructs.h
		include/sd/FatLib/FatVolume.h
		include/sd/FatLib/FmtNumber.h
		include/sd/FatLib/fstream.h
		include/sd/FatLib/ios.h
		include/sd/FatLib/iostream.h
		include/sd/FatLib/istream.h
		include/sd/FatLib/ostream.h
		include/sd/FatLib/StdioStream.h
		include/sd/SdCard/SdInfo.h
		include/sd/SdCard/SdioCard.h
		include/sd/SpiDriver/DigitalPin.h
		include/sd/SpiDriver/SdSpiBaseDriver.h
		include/sd/SpiDriver/SdSpiDriver.h
		include/sd/SpiDriver/SoftSPI.h
	)
	# Link libraries
	target_link_libraries(sd
		PUBLIC
			core
	)
	# Setup include directories 
	target_include_directories(sd PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
endif()
