# rr-mc
Arduino BLE controller for Fatcontroller robot

# Build

```
platformio run -e nano33ble
```

* note that '-e' can have nano33ble or native as options
* note that if uploading is used, then compiling is not necessary (it will compile)

# Uploading

```
platformio run --target upload --environment nano33ble
```

## Test

Tests will only work on Native environment at the moment:

```
platformio test -vvv -e native
```