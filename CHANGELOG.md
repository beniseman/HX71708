# Change Log HX71708
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [0.1.0] - 2025-04-10
- Initial publication of forked HX711 library.
- Replaced GAIN and associated functions `get_gain()` and `set_gain()` with DATA_RATE equivalents:
  - `get_data_rate()`
  - `set_data_rate()`
  - Data rate constants:
    - `HX71708_DATA_RATE_10`
    - `HX71708_DATA_RATE_20`
    - `HX71708_DATA_RATE_80`
    - `HX71708_DATA_RATE_320`