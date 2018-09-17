#
# Copyright (C) 2015 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
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

-include vendor/motorola/msm8916-common/BoardConfigVendor.mk

VENDOR_PATH := device/motorola/msm8916-common

BOARD_VENDOR := motorola-qcom

TARGET_SPECIFIC_HEADER_PATH := $(VENDOR_PATH)/include

TARGET_FS_CONFIG_GEN += \
    $(VENDOR_PATH)/fs_config/file_caps.fs \
    $(VENDOR_PATH)/fs_config/qcom_aids.fs \
    $(VENDOR_PATH)/fs_config/mot_aids.fs

# Platform
TARGET_BOARD_PLATFORM := msm8916
TARGET_BOARD_PLATFORM_GPU := qcom-adreno306

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := MSM8916
TARGET_NO_BOOTLOADER := true

# Architecture
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv8-a
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_VARIANT := cortex-a53

# Binder API version
TARGET_USES_64_BIT_BINDER := true

# Kernel Toolchain
ifneq ($(wildcard $(BUILD_TOP)/prebuilts/gcc/$(HOST_OS)-x86/arm/arm-eabi-7.3),)
  KERNEL_TOOLCHAIN := $(BUILD_TOP)/prebuilts/gcc/$(HOST_OS)-x86/arm/arm-eabi-7.3/bin
  KERNEL_TOOLCHAIN_PREFIX := arm-eabi-
endif

# Kernel
BOARD_KERNEL_CMDLINE := console=ttyHSL0,115200,n8 androidboot.console=ttyHSL0 androidboot.hardware=qcom msm_rtb.filter=0x3F ehci-hcd.park=3 vmalloc=400M androidboot.bootdevice=7824900.sdhci utags.blkdev=/dev/block/bootdevice/by-name/utags utags.backup=/dev/block/bootdevice/by-name/utagsBackup movablecore=160M
BOARD_KERNEL_CMDLINE += androidboot.selinux=permissive
BOARD_KERNEL_BASE := 0x80000000
BOARD_KERNEL_IMAGE_NAME := zImage
BOARD_KERNEL_PAGESIZE := 2048
BOARD_KERNEL_SEPARATED_DT := true
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x01000000 --tags_offset 0x00000100
TARGET_KERNEL_ARCH := arm
TARGET_KERNEL_SOURCE := kernel/motorola/msm8916

# Audio
AUDIO_FEATURE_ENABLED_COMPRESS_VOIP := true
AUDIO_FEATURE_ENABLED_FLUENCE := true
AUDIO_FEATURE_ENABLED_FM_POWER_OPT := true
AUDIO_FEATURE_ENABLED_KPI_OPTIMIZE := true
AUDIO_FEATURE_ENABLED_MULTI_VOICE_SESSIONS := true
AUDIO_FEATURE_ENABLED_NEW_SAMPLE_RATE := true
AUDIO_FEATURE_ENABLED_PROXY_DEVICE := true
BOARD_USES_ALSA_AUDIO := true
USE_CUSTOM_AUDIO_POLICY := 1

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(VENDOR_PATH)/bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_QCOM := true
QCOM_BT_READ_ADDR_FROM_PROP := true

# Camera
USE_DEVICE_SPECIFIC_CAMERA := true
TARGET_HAS_LEGACY_CAMERA_HAL1 := true
TARGET_USES_MEDIA_EXTENSIONS := true
TARGET_PROVIDES_CAMERA_HAL := true
TARGET_PROCESS_SDK_VERSION_OVERRIDE := \
	/system/vendor/bin/mm-qcamera-daemon=23

# Charger
BACKLIGHT_PATH := /sys/class/leds/lcd-backlight/brightness
BOARD_CHARGER_ENABLE_SUSPEND := true
BOARD_NO_CHARGER_LED := true

# Crypto
TARGET_HW_DISK_ENCRYPTION := true
TARGET_KEYMASTER_WAIT_FOR_QSEE := true
TARGET_LEGACY_HW_DISK_ENCRYPTION := true

# Display
MAX_EGL_CACHE_KEY_SIZE := 12*1024
MAX_EGL_CACHE_SIZE := 2048*1024
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3
TARGET_USES_GRALLOC1 := true
TARGET_USES_ION := true
TARGET_USES_NEW_ION_API := true

# Display Renderer
OVERRIDE_RS_DRIVER := libRSDriver_adreno.so
USE_OPENGL_RENDERER := true

# Exclude serif fonts for saving system.img size.
EXCLUDE_SERIF_FONTS := true

# UI
TARGET_ADDITIONAL_GRALLOC_10_USAGE_BITS := 0x02000000U

# FM
BOARD_HAVE_QCOM_FM := true
TARGET_QCOM_NO_FM_FIRMWARE := true

# GPS
BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE := true
BOARD_VENDOR_QCOM_LOC_PDK_FEATURE_SET := true
USE_DEVICE_SPECIFIC_GPS := true

# HIDL
DEVICE_MANIFEST_FILE := $(VENDOR_PATH)/manifest.xml

# Lights
TARGET_PROVIDES_LIBLIGHT := true

# Partitions
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_FLASH_BLOCK_SIZE := 131072
TARGET_EXFAT_DRIVER := exfat

# Properties
TARGET_SYSTEM_PROP += $(VENDOR_PATH)/system.prop

# Qualcomm support
BOARD_USES_QCOM_HARDWARE := true

# Recovery
BOARD_HAS_NO_SELECT_BUTTON := true
TARGET_RECOVERY_FSTAB := $(VENDOR_PATH)/rootdir/etc/fstab.qcom
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true
TARGET_USES_MKE2FS := true

# Release Tools
TARGET_RELEASETOOLS_EXTENSIONS := $(VENDOR_PATH)

# SELinux
include device/qcom/sepolicy-legacy/sepolicy.mk
BOARD_SEPOLICY_DIRS += $(VENDOR_PATH)/sepolicy

# Shims
TARGET_LD_SHIM_LIBS := \
    /system/lib/libandroid.so|libshim_ril.so \
    /system/lib/libmdmcutback.so|libqsap_shim.so \
    /system/lib/libmot_sensorlistener.so|libsensor.so \
    /system/lib/libjustshoot.so|libshims_camera.so \
    /system/vendor/lib/libmmcamera_wavelet_lib.so|libc_util.so \
    /system/vendor/lib/libmmqjpeg_codec.so|libboringssl-compat.so \
    /system/vendor/lib/libqomx_jpegenc.so|libboringssl-compat.so \
    /system/lib/libfacenet.so|libprotobuf-cpp-haxx.so

# Wifi
BOARD_HAS_QCOM_WLAN := true
BOARD_WLAN_DEVICE := qcwcn
BOARD_HOSTAPD_DRIVER := NL80211
BOARD_HOSTAPD_PRIVATE_LIB := lib_driver_cmd_qcwcn
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_qcwcn
PRODUCT_VENDOR_MOVE_ENABLED := true
WIFI_DRIVER_FW_PATH_AP  := "ap"
WIFI_DRIVER_FW_PATH_STA := "sta"
WPA_SUPPLICANT_VERSION := VER_0_8_X


# Optimize
MALLOC_SVELTE := true
PRODUCT_SYSTEM_SERVER_COMPILER_FILTER := speed-profile
PRODUCT_ALWAYS_PREOPT_EXTRACTED_APK := true
PRODUCT_USE_PROFILE_FOR_BOOT_IMAGE := true
PRODUCT_DEX_PREOPT_BOOT_IMAGE_PROFILE_LOCATION := frameworks/base/config/boot-image-profile.txt
