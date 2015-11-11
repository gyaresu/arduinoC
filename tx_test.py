#!/opt/local/bin/python

import time
import sys
from rflib import *

d = RfCat()

freq = 433e6
pktlen = 4
baudRate = 9600

def Configure(d):
    d.setFreq(freq)
    d.setMdmModulation(MOD_ASK_OOK)
    d.makePktFLEN(pktlen)
    d.setMdmSyncMode(2)
    d.setMdmSyncWord(0xB547)
    d.setMdmDRate(baudRate)

print "Configuring rfcat"
try:
    Configure(d)
    for i in range(0, 1000):
        d.RFxmit('\x05\x02\x00\x00')

except Exception, e:
    sys.exit("Error %s" % str(e))

#print d.reprRadioConfig()

