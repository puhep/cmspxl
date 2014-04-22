#!/usr/bin/env python
"""
Translate the log to XML format

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"

import sys
from decimal import Decimal 
import time
import datetime

ts = time.time()
st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')

logFile = sys.argv[1]
xmlFile = logFile.replace('.log', '.xml')

sr = logFile.replace('.log', '')

user = raw_input('Initiated by user: ')

logData = open(logFile, 'r')
xmlData = open(xmlFile, 'w')

xmlHeader = '''<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <HEADER>
    <TYPE>
      <EXTENSION_TABLE_NAME>UPGRADE_FPIX_SNSRWAFR_IV</EXTENSION_TABLE_NAME>
      <NAME></NAME>
    </TYPE>
    <RUN>
      <RUN_NAME></RUN_NAME>
      <RUN_BEGIN_TIMESTAMP>%s</RUN_BEGIN_TIMESTAMP>
      <INITIATED_BY_USER>%s</INITIATED_BY_USER>
      <LOCATION>Purdue</LOCATION>
      <COMMENT_DESCRIPTION></COMMENT_DESCRIPTION>
    </RUN>
  </HEADER>
  
  <DATA_SET>
    <VERSION></VERSION>
    <COMMENT_DESCRIPTION></COMMENT_DESCRIPTION>
    <PART>
      <SERIAL_NUMBER>%s</SERIAL_NUMBER>
      <KIND_OF_PART></KIND_OF_PART>
    </PART>

''' % (st, user, sr) 

xmlData.write(xmlHeader)

for row in logData:
    print row

sys.exit()

rowNum = 0
for row in logData:
    rowNum +=1
    if len(row[0]) == 0 or len(row[1]) == 0 :
        break

    if rowNum == 1:
        print 'Using %s and %s as Voltage and Current ...' %(row[0], row[1]) 
        factor = 1 
        if '[nA]' in row[1]:
            factor = 1e-9 
            print 'Convert from nA to A...'

    else: 
        voltage = Decimal(row[0]) 
        current = Decimal(row[1]) * Decimal(factor)
        xmlData.write('<DATA>\n')
        xmlData.write('<VOLTAGE_VOLT>%.2E</VOLTAGE_VOLT>\n' %voltage)
        xmlData.write('<ACTV_CURRENT_AMP>%.2E</ACTV_CURRENT_AMP>\n' %current)
        xmlData.write('</DATA>\n')


xmlData.write('</DATA_SET>\n')
xmlData.write('</ROOT>\n')
xmlData.close()

print 'Saved as %s.' %xmlFile




