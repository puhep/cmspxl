#!/usr/bin/env python
"""
Translate the XML to log format

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"

import sys
from decimal import Decimal 
import time
import datetime


xmlFile = sys.argv[1] 
logFile = xmlFile.replace('.xml', '.log')

sr = logFile.replace('.log', '')


xmlData = open(xmlFile, 'r')
logData = open(logFile, 'w')

#xmlData.write(xmlHeader)
#for row in xmlData:
#    print row



import xml.etree.ElementTree as ET
tree = ET.parse(xmlFile)
root = tree.getroot()

print root

# for child in root:
#     print child.tag, child.attrib
#     if child.tag == 'DATA_SET':
#         for dt in child:
#             print dt.tag, dt.attrib

vs = [ data.text for data in root.iter('VOLTAGE_VOLT')]
iss =[ data.text for data in root.iter('ACTV_CURRENT_AMP')]

print vs, iss

print len(vs), len(iss)


# for data in root.iter('VOLTAGE_VOLT'):
#     print data.text


#    'ACTV_CURRENT_AMP'

sys.exit() 


for row in xmlData:

    if row.find('#') == 0:
        continue

    items = row.split() 
    voltage = -1*Decimal(items[0])
    current = -1*Decimal(items[1])

    xmlData.write('<DATA>\n')
    xmlData.write('<VOLTAGE_VOLT>%.2E</VOLTAGE_VOLT>\n' %voltage)
    xmlData.write('<ACTV_CURRENT_AMP>%.2E</ACTV_CURRENT_AMP>\n' %current)
    xmlData.write('</DATA>\n')
    

xmlData.write('</DATA_SET>\n')
xmlData.write('</ROOT>\n')
xmlData.close()

print 'Saved as %s.' %xmlFile




