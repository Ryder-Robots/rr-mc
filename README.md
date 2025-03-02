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

| element    | position      | type      | byte offset | 
| ---------- | ------------- | --------  | ----------  |
| premble    | 0             | uint8_t*  | 2           |
| direction  | 2             | uint8_t   | 1           |
| size       | 3             | uint16_t  | 2           |
| command    | 5             | uint8_t   | 1           |
| data       | 6             | uint8_t*  | 0 to n      |
| crc        | (6 + (n + 1)) | uint32_t  | 4           |   

# Reference

* [Multiwii Serial Protocol](http://www.multiwii.com/wiki/index.php?title=Multiwii_Serial_Protocol)
