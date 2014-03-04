#!/usr/bin/env python
"""
Translate the CSV to XML format

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"

import csv
import sys
from decimal import Decimal 

csvFile = sys.argv[1]
xmlFile = csvFile.replace('.csv', '.xml')


csvData = csv.reader(open(csvFile))
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
      <RUN_BEGIN_TIMESTAMP></RUN_BEGIN_TIMESTAMP>
      <INITIATED_BY_USER></INITIATED_BY_USER>
      <LOCATION>Purdue</LOCATION>
      <COMMENT_DESCRIPTION></COMMENT_DESCRIPTION>
    </RUN>
  </HEADER>
'''

xmlData.write(xmlHeader)
xmlData.write('<DATA_SET>\n')

rowNum = 0
for row in csvData:
    rowNum +=1

    if rowNum == 1:
        print 'Using %s and %s as Voltage and Current ...' %(row[0], row[1]) 
        if '[nA]' in row[1]:
            factor = 1e-9 
            print 'Convert from nA to A...'

    else: 
        voltage = Decimal(row[0]) 
        current = Decimal(row[1]) * Decimal(factor)
        xmlData.write('<DATA>\n')
        xmlData.write('<VOLTAGE_VOLT>%.2E</VOLTAGE_VOLT>\n' %voltage)
        xmlData.write('<TOTAL_CURRENT_AMP>%.2E</TOTAL_CURRENT_AMP>\n' %current)
        xmlData.write('</DATA>\n')

        if len(row[0]) == 0 or len(row[1]) == 0 :
            break

xmlData.write('</DATA_SET>\n')
xmlData.write('</ROOT>\n')
xmlData.close()

print 'Saved as %s.' %xmlFile




