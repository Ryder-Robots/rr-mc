# rr-mc
Firmware software for RR Robot Fat Controller

# MULTI-WII Porject

```[command][size][checksum][data][term]```

- command = message_id as per the table below
- size = number of data bytes, binary. Can be zero as in the case of a data request to the MWC
- crc = XOR of each data byte into a zero'ed sum, the remainder should be 0, otherwise data may be corrupted. Note tthat unlike multiwii protocol, size, and command are not added to CRC,  as data should always a precise for a precise command this should be indicated by checking size() and command().    
- data  = as per the table below. UINT16 values are MSB first.
- term  = always 0x1E

| element    | position      | type      | byte offset | optional |
| ---------- | ------------- | --------  | ----------  | -------- |
| command    | 0             | uint8_t   | 1           | no       |
| size       | 1, 2          | uint16_t  | 2           | no       |
| crc        | 3, 4, 5, 6    | uint32_t  | 4           | no       |
| data       | 6             | uint8_t*  | 0 to n      | yes      |
| term       | n + 1         | uint8_t*  | 1           | no       |

minimum length is 8, for command only commands such as:

```
0x68, 0x0, 0x0, 0x0, 0x0, 0x0,  0x1E
```  

when size = 0 then, term is at position 7.

# Reference

loosly based on: [Multiwii Serial Protocol](http://www.multiwii.com/wiki/index.php?title=Multiwii_Serial_Protocol)
