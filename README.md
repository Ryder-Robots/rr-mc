# rr-mc
Firmware software for RR Robot Fat Controller

# MULTI-WII Porject

```$M[direction][size][command][data][checksum]```

- preamble = the ASCII characters '$M'
- direction = the ASCII character '<' if to the MWC or '>' if from the MWC
- size = number of data bytes, binary. Can be zero as in the case of a data request to the MWC
- command = message_id as per the table below
- data = as per the table below. UINT16 values are LSB first.
- crc = XOR of <size>, <command> and each data byte into a zero'ed sum


# Reference

* [Multiwii Serial Protocol](http://www.multiwii.com/wiki/index.php?title=Multiwii_Serial_Protocol)
