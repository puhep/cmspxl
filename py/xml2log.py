#!/usr/bin/env python
"""
Translate the XML to log format

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"

import sys
import xml.etree.ElementTree as ET

xmlFile = sys.argv[1] 
logFile = xmlFile.replace('.xml', '.log')

tree = ET.parse(xmlFile)
root = tree.getroot()

Vs = [ data.text for data in root.iter('VOLTAGE_VOLT')]
Is =[ data.text for data in root.iter('ACTV_CURRENT_AMP')]

IVs = zip(Vs, Is)

logData = open(logFile, 'w')
for IV in IVs:
    logData.write('%s  %s \n' %IV)

print 'Saved as %s.' %logFile





