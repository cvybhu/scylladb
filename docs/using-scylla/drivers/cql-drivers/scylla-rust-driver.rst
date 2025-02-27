==================
Scylla Rust Driver
==================

The Scylla Rust Driver has not yet been released as GA. Updates will be made to the `Release Notes <https://www.scylladb.com/product/release-notes/>`_.
The Scylla Rust driver is a client-side, shard-aware driver written in pure Rust with a fully async API using Tokio.

Although optimized for ScyllaDB, the driver is also compatible with Apache Cassandra®.


.. image:: ./images/monster-rust.png
   :width: 150pt


**To download and install the driver**, visit the `Github project <https://github.com/scylladb/scylla-rust-driver>`_.

Read the `Documentation <https://rust-driver.docs.scylladb.com>`_.

Using CDC with Rust
----------------------

When writing applications, you can use ScyllaDB's `Rust CDC Library <https://github.com/scylladb/scylla-cdc-rust>`_ 
to simplify writing applications that read from ScyllaDB's CDC.

Use `Rust CDC Library <https://github.com/scylladb/scylla-cdc-rust>`_ to read 
:doc:`ScyllaDB's CDC </using-scylla/cdc/index>` update streams.