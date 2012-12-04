SECURE FILE TRANSFER PROTOCOL
=============================

This was done as a Data Communication and Networks Course Project.

AES algorithm is used to encrypt and decrypt the data sent over the routers.

+ source encrypts and sends chunks of data to router1
+ Router1 then routes the packets along router2 or router3
+ Destination collects the data chunks and created the cipher 
+ On the final cipher, decryption is applied to retrieve the original data.