# PSn00bSDK example CMake script
# (C) 2021 spicyjpeg - MPL licensed

cmake_minimum_required(VERSION 3.21)

project(
	test
	LANGUAGES    CXX ASM
	VERSION      1.0.0
	DESCRIPTION  "PSn00bSDK GTE 3D cube example"
	HOMEPAGE_URL "http://lameguy64.net/?page=psn00bsdk"
)

file(GLOB_RECURSE _sources src/**.*)
psn00bsdk_add_executable(test GPREL ${_sources})
psn00bsdk_target_incbin(test PUBLIC girl_tim assets/Girl_4bit.tim)
psn00bsdk_target_incbin(test PUBLIC kuromi_tim assets/kuromi_4bit.tim)
psn00bsdk_target_incbin(test PUBLIC tim_texture assets/texture.tim)
target_include_directories(test PUBLIC src)
#psn00bsdk_add_cd_image(gte_iso gte iso.xml DEPENDS gte)

install(FILES ${PROJECT_BINARY_DIR}/test.exe TYPE BIN)
