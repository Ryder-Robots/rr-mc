# rr-mc
Firmware software for RR Robot Fat Controller

# MULTI-WII Porject

```$M[direction][size][command][data][checksum]```

- preamble = the ASCII characters '$M'
- direction = the ASCII character '<' if to the MWC or '>' if from the MWC
- size = number of data bytes, binary. Can be zero as in the case of a data request to the MWC
- command = message_id as per the table below
- data = as per the table below. UINT16 values are MSB first.
- crc = XOR of each data byte into a zero'ed sum, the remainder should be 0, otherwise data may be corrupted. Note tthat unlike multiwii protocol, size, and command are not added to CRC,  as data should always a precise for a precise command this should be indicated by checking size() and command().    


# Reference

* [Multiwii Serial Protocol](http://www.multiwii.com/wiki/index.php?title=Multiwii_Serial_Protocol)
