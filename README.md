Voting Pool Audit Service
=========================

[![Build Status](https://travis-ci.org/monetas/vp-auditservice.svg?branch=develop)](https://travis-ci.org/monetas/vp-auditservice)

Auditing component of the [Open-Transactions](http://opentransactions.org) Voting Pool.


Bootstrapping
=============

TBD


Dependencies
============

* xmlrpc-c
* jsoncpp
* libxml2
* boost >= 1.54.0
* [Google Protocol Buffers](https://code.google.com/p/protobuf/)
* [Google Test](https://code.google.com/p/googletest/)

Known Issues
============

* If you are getting errors such as "API Error 0021: Unexpected API Failure - need more than 0 values to unpack", 
    that means xmlrpc-c and auditor were not compiled with the same standard library. Also make sure that you remembered to use
    "--enable-libxml2-backend" when running "./configure" on xmlrpc-c.


References
==========

* [Voting Pools on Open-Transacations Wiki](http://opentransactions.org/wiki/index.php?title=Voting_Pools)
