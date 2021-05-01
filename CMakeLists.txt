cmake_minimum_required(VERSION 3.13)
if (DEFINED MCU)
	# Setting up the toolchain
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/cortex.cmake")
endif()
# Project information
project(SD
	VERSION 2.0.3
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
		GIT_REPOSITORY https://github.com/bolderflight/core.git
		GIT_TAG v2.0.5
	)
	FetchContent_MakeAvailable(core)
	# Add the library target
	add_library(sd
		src/sd/FreeStack.cpp
		src/sd/MinimumSerial.cpp
		src/sd/SpiDriver/SdSpiChipSelect.cpp
		src/sd/SpiDriver/SdSpiTeensy3.cpp
		src/sd/SdCard/SdCardInfo.cpp
		src/sd/SdCard/SdSpiCard.cpp
		src/sd/SdCard/SdioTeensy.cpp
		src/sd/iostream/StdioStream.cpp
		src/sd/iostream/StreamBaseClass.cpp
		src/sd/iostream/istream.cpp
		src/sd/iostream/ostream.cpp
		src/sd/FsLib/FsFile.h
		src/sd/FsLib/FsLib.h
		src/sd/FsLib/FsNew.h
		src/sd/FsLib/FsVolume.h
		src/sd/FatLib/FatDbg.cpp
		src/sd/FatLib/FatFile.cpp
		src/sd/FatLib/FatFileLFN.cpp
		src/sd/FatLib/FatFilePrint.cpp
		src/sd/FatLib/FatFileSFN.cpp
		src/sd/FatLib/FatFormatter.cpp
		src/sd/FatLib/FatPartition.cpp
		src/sd/FatLib/FatVolume.cpp
		src/sd/ExFatLib/ExFatDbg.cpp
		src/sd/ExFatLib/ExFatFile.cpp
		src/sd/ExFatLib/ExFatFilePrint.cpp
		src/sd/ExFatLib/ExFatFileWrite.cpp
		src/sd/ExFatLib/ExFatFormatter.cpp
		src/sd/ExFatLib/ExFatPartition.cpp
		src/sd/ExFatLib/ExFatVolume.cpp
		src/sd/ExFatLib/upcase.cpp
		src/sd/common/FmtNumber.cpp
		src/sd/common/FsCache.cpp
		src/sd/common/FsDateTime.cpp
		src/sd/common/FsStructs.cpp
		src/sd/common/PrintBasic.cpp
		src/sd/common/SysCallBareUno.cpp
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


# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	if (DEFINED MCU)		
		# Add the sd example target
		add_executable(sd_example examples/sd.cc)
		# Add the includes
		target_include_directories(sd_example PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>
		)
		# Link libraries to the example target
		target_link_libraries(sd_example
			PRIVATE 
				sd
		)
		# Add hex and upload targets
		include(${CMAKE_SOURCE_DIR}/cmake/flash_mcu.cmake)
		FlashMcu(sd_example ${MCU})
	endif()
endif()

