#!/usr/bin/env python
"""
Translate the CSV to XML format

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"

import csv
import sys

csvFile = sys.argv[1]
xmlFile = csvFile.replace('.csv', '.xml')


csvData = csv.reader(open(csvFile))
xmlData = open(xmlFile, 'w')
#xmlData.write('<?xml version="1.0"?>' + "\n")

rowNum = 0
for row in csvData:
    rowNum +=1

    if rowNum == 1:
        #print row # title 
        # need to add header here 
        print 'Using %s and %s as Voltage and Current ...' %(row[0], row[1]) 

    else: 
        voltage = row[0]
        current = row[1]
        xmlData.write('<DATA>\n')
        xmlData.write('<VOLTAGE_VOLT>%s</VOLTAGE_VOLT>\n' %voltage)
        xmlData.write('<TOTAL_CURRENT_AMP>%s</TOTAL_CURRENT_AMP>\n' %current)
        xmlData.write('</DATA>\n')

        if len(current) == 0:
            break


xmlData.close()
print 'Saved as %s.' %xmlFile




