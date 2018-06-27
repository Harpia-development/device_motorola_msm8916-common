/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright (C) 2015 Motorola Mobility LLC
 */

#ifndef ANDROID_AKM_SENSOR_H
#define ANDROID_AKM_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <linux/limits.h>

#include "Sensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

/*****************************************************************************/

struct input_event;

class AkmSensor : public SensorBase {
public:
	AkmSensor();
	virtual ~AkmSensor();

	enum {
		Accelerometer = 0,
		MagneticField,
		UncalMagneticField,
		Orientation,
		RotationVector,
		numSensors
	};

	static AkmSensor* getInstance();
	virtual int writeMagDelay(int64_t ns);
	virtual int setEnable(int32_t handle, int enabled);
	virtual int setDelay(int32_t handle, int64_t ns);
	virtual int readEvents(sensors_event_t* data, int count);
	virtual int flush(int32_t handle);
	void processEvent(int code, int value);
	int setAccel(sensors_event_t* data);

private:
	static AkmSensor self;
	int mEnabled[numSensors];
	int64_t mDelay[numSensors];
	uint32_t mPendingMask;
	InputEventCircularReader mInputReader;
	sensors_event_t mPendingEvents[numSensors];
	char input_sysfs_path[PATH_MAX];
	int input_sysfs_path_len;

	int handle2id(int32_t handle);
};

/*****************************************************************************/

#endif  // ANDROID_AKM_SENSOR_H
