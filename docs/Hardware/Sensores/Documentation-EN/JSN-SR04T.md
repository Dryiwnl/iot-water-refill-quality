# JSN-SR04T Ultrasonic Sensor Documentation

# Purpose of the JSN-SR04T

The sensor was implemented in the project to measure the water level inside the drinking trough. Therefore, its reading returns the distance (in centimeters) between the sensor and the water surface.

> **Figure 1:** Representation of the distance measurement between the JSN-SR04T and the water surface.

![Figure 1 - Distance Measurement Representation](/docs/Hardware/Sensores/img/img8.png)

---

# How It Works

The sensor has four pins:

* **5V:** Power supply.
* **GND:** Ground.
* **Trig:** Emits the ultrasonic pulse.
* **Echo:** Measures the round-trip travel time of the ultrasonic pulse.

The **Trig** pin is driven HIGH to emit an ultrasonic pulse. This pulse travels through the air, reflects off a surface, and returns to the sensor. At the same moment the pulse is transmitted, the **Echo** pin goes HIGH and remains HIGH until the reflected pulse is received.

Notice that the sensor measures the **travel time** of the ultrasonic pulse rather than the distance itself. Therefore, the measured time must be converted into centimeters.

Since the travel time is known, the following equation is used:

```math
s = v \cdot t
```

where:

* (s): distance (centimeters);
* (v): speed of sound;
* (t): time (seconds).

For the calculations performed in the firmware, the speed of sound is considered in centimeters per microsecond:

```math
v = 0.0343 \; \text{cm}/\mu\text{s}
```

Since the measured time corresponds to the pulse traveling to the object **and back**, the result must be divided by two:

```math
d = \frac{v \cdot t}{2}
```

Substituting the speed of sound:

```math
d = \frac{0.0343 \cdot t}{2}
```

In the source code, this equation is implemented as:

```math
\text{distance} = \frac{\text{duration} \cdot 0.0343}{2}
```

---

# Pinout

> **Figure 2:** Connection between the JSN-SR04T and the ESP32.

![Figure 2 - JSN-SR04T connected to the ESP32](/docs/Hardware/Sensores/img/img9.png)

| Connection    |
| ------------- |
| 5V → Vin      |
| Trig → GPIO5  |
| Echo → GPIO18 |
| GND → GND     |

---

# Test Code

```cpp
#include <Arduino.h>

// Pin configuration
#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configure Trig as output and Echo as input
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Keep Trig LOW initially
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);

  // Send the ultrasonic pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_PIN, LOW);

  // pulseIn returns the duration that Echo stays HIGH
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 60000);

  if (duration == 0) {
    Serial.println("Out_of_range/No_reading");
  } else {
    // Calculate the distance in centimeters
    float distance_cm = duration * 0.0343 / 2.0;
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
  }

  delay(500);
}
```

---

# Notes

Measurements should only be performed with an object located at least **20 cm** away from the JSN-SR04T. Shorter distances may produce unstable or even invalid readings due to the sensor's blind zone.

---

# Specifications

| Parameter             | Value                                                                                                                                  |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| Type                  | JSN-SR04T / AJ-SR04M Ultrasonic Module                                                                                                 |
| Application           | Distance measurement in humid environments with a waterproof probe                                                                     |
| Material              | Electronic components                                                                                                                  |
| Supply Voltage        | 5 V DC                                                                                                                                 |
| Operating Current     | 30 mA                                                                                                                                  |
| Standby Current       | 5 mA                                                                                                                                   |
| Low-Power Current     | 20 μA                                                                                                                                  |
| Operating Frequency   | 40 kHz                                                                                                                                 |
| Maximum Range         | 4.5 m                                                                                                                                  |
| Minimum Range         | 25 cm                                                                                                                                  |
| Resolution            | 0.5 cm                                                                                                                                 |
| Measuring Angle       | < 50°                                                                                                                                  |
| Operating Temperature | -10 °C to 70 °C                                                                                                                        |
| Probe Cable Length    | Approximately 2.5 m                                                                                                                    |
| Module Dimensions     | Approximately 41 × 28 × 11 mm                                                                                                          |
| Features              | Integrated waterproof probe, high stability and sensitivity, blind zone shorter than 25 cm, and water- and dust-resistant construction |
