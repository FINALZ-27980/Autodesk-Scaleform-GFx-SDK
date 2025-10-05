NVTXAA 
======

TXAA is a new film-style anti-aliasing technique designed specifically 
to reduce temporal aliasing.

Directory
=========

include : Header files
lib     : Library files
doc     : Documentation
samples : Sample applications
test    : Test application

Variations
=========
GFSDK_TXAA.* - This is the default variation.  Alpha channel is set to zero on output.

GFSDK_TXAA_AlphaResolve.* - This variation will add a seperate box filter resolve of alpha channel and inject into resolve results.

GFSDK_TXAA_AlphaPreserve.* - This variation will mask off the alpha channel in the target, preserving what is already there.  It does not copy data from the MSAA source.

