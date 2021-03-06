#!/usr/bin/env python
"""
Translate the XML to log format

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"

import sys
import xml.etree.ElementTree as et



def xml2log(xmlFile):
    tree = et.parse(xmlFile)
    root = tree.getroot()

    Vs = [ data.text for data in root.iter('VOLTAGE_VOLT')]
    Is = [ data.text for data in root.iter('ACTV_CURRENT_AMP')]
    Igs =[ data.text for data in root.iter('GRD_CURRENT_AMP')]

    IVs = zip(Vs, Is)

    logFile = xmlFile.replace('.xml', '.log')    
    logData = open(logFile, 'w')
    for IV in IVs:
        logData.write('%s  %s \n' %IV)

    print 'Saved as %s.' %logFile

    IgVs = zip(Vs, Igs)    
    logFile_guard = xmlFile.replace('.xml', '_guard.log')    
    logData_guard = open(logFile_guard, 'w')
    for IV in IgVs:
        logData_guard.write('%s  %s \n' %IV)

    print 'Saved as %s.' %logFile_guard

xmlFiles = sys.argv[1:]

for xmlFile in xmlFiles:
    xml2log(xmlFile)





    


