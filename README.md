Voting Pool Audit Service
=========================

[![Build Status](https://travis-ci.org/Monetas/vp-auditservice.svg?branch=develop)](https://travis-ci.org/Monetas/vp-auditservice)

Auditing component of the [Open-Transactions](http://opentransactions.org) Voting Pool.


Bootstrapping
=============

TBD


Dependencies
============

* xmlrpc-c (on OSX, compiled with "CXXFLAGS='-std=c++11 -stdlib=libc++' ./configure --enable-libxml2-backend; make -j2")
* libxml2
* boost >= 1.54.0


Known Issues
============

* If you are getting errors such as "API Error 0021: Unexpected API Failure - need more than 0 values to unpack", 
    that means xmlrpc-c and auditor were not compiled with the same standard library. Also make sure that you remembered to use
    "--enable-libxml2-backend" when running "./configure" on xmlrpc-c.


References
==========

* [Voting Pools on Open-Transacations Wiki](http://opentransactions.org/wiki/index.php?title=Voting_Pools)
