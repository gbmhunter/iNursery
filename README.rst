==============================================================
iNursery
==============================================================

- Author: gbmhunter <gbmhunter@gmail.com> (`http://www.cladlab.com <http://www.cladlab.com/>`_)
- Created: 2014/01/03
- Last Modified: 2014/01/03
- Version: v1.0.0.2
- Company: CladLabs
- Project: iNursery
- Language: C++
- Compiler: GCC	
- uC Model: Arduino
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

.. role:: bash(code)
	:language: bash

Description
===========

The repository for the iNursery, and temperature and light-controlled environment for eggs and small animals (see `here <http://cladlab.com/electronics/projects/inursery>`_ for more info). This repository contains the code running on the iNursery's Arduino Uno.

Installation
============

This assumes you are running a UNIX-like machine.

1. Clone the git repo onto your local storage.

2. From a terminal, type :code:`export BOARD=uno` to instruct makefile about correct Arduino board. Make sure Arduino Uno is connected to computer.

3. Navigate to the `/src/` directory and type :code:`make` to compile the code, or :code:`make upload` to compile and upload the code to the Arduino. You may have to grant admin privileges for the tty port with :code:`sudo chmod 666 /dev/ttyACM0` before using :code:`make upload`.


External Dependencies
=====================

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
n/a
====================== ==================== ======================================================================

Issues
======

See GitHub Issues.

Limitations
===========

n/a

FAQ
===

n/a

Changelog
=========

======== ========== =============================================================================================
Version  Date       Comment
======== ========== =============================================================================================
v1.0.0.2 2014/01/03 Second attempt at fixing hyperlinks in README.
v1.0.0.1 2014/01/03 Attempt at fixing hyperlinks in README.
v1.0.0.0 2014/01/03 Initial commit. Firmware works.
======== ========== =============================================================================================