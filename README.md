# HX71708 v0.1.0 (alpha)

## Overview

The **HX71708** library is a fork of https://github.com/RobTillaart/HX711 version 0.5.2. It is built for the **HX71708** from Avia Semiconductor (Xiamen) Ltd. using the **Arduino IDE**. 

Whereas the HX711 uses clock pulses to set gain, the HX71708 operates with a fixed gain, and uses clock pulses to set the data sample rate of 10, 20, 80, or 320 Hz. This is the only modification I have made to the code base.

### `set_data_rate()` Behavior

| Version                        | Description                                                                 | Behavior                                                                                   |
|-------------------------------|-----------------------------------------------------------------------------|--------------------------------------------------------------------------------------------|
| `set_data_rate(rate)`         | Sets data rate if it differs from the current setting                       | Skips reapplying if the rate is already active. Returns `true` if valid, `false` otherwise |
| `set_data_rate(rate, false)`  | Same as above — explicitly avoids reapplying the same rate                  | Returns `true` if the rate is unchanged or successfully applied                            |
| `set_data_rate(rate, true)`   | Forces the rate to be applied even if it’s the same                         | Re-applies rate and calls `read()` to resync                                               |
| `set_data_rate(invalid_rate)` | Tries to set an unsupported SPS value                                       | Returns `false`, makes no change                                                           |
| `bool ok = set_data_rate(...)`| You can capture the return value to verify success                         | `true` for valid/accepted rate, `false` for invalid input                                  |

### Permitted Data Rates

The following constants are valid arguments for `scale.set_data_rate()`:

| Constant Name                   | SPS Value | Example Code                                |
|--------------------------------|-----------|---------------------------------------------|
| `HX71708_DATA_RATE_10`         | 10 SPS    | `scale.set_data_rate(HX71708_DATA_RATE_10);` |
| `HX71708_DATA_RATE_20`         | 20 SPS    | `scale.set_data_rate(HX71708_DATA_RATE_20);` |
| `HX71708_DATA_RATE_80`         | 80 SPS    | `scale.set_data_rate(HX71708_DATA_RATE_80);` |
| `HX71708_DATA_RATE_320`        | 320 SPS   | `scale.set_data_rate(HX71708_DATA_RATE_320);` |
