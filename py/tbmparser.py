#!/usr/bin/env python
"""
TBM output parser 

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"
__created__ = "19 June 2014" 


import sys
import os 


def usage():
    sys.stdout.write('-'*60 + '\n')
    sys.stdout.write('Usage: tbmparser inputfile \n')
    sys.stdout.write('-'*60 + '\n\n')


def main():
    args = sys.argv[1:]
    if len(args)== 0:
        return usage()

    filename = args[0]

    tbm = TBMFile(filename)
    
    print tbm.data

    sys.exit()

    if args[0] == 'dac':
        dac(args[1:])
    elif args[0] == 'board':
        board(args[1:])
    else:
        raise NameError(args)



class TBMFile(object):
    '''Class to handle TBM output file  '''
    def __init__(self, filename=None):
        self.data = []        
        if filename:
            self.input(filename)
            self.file = filename

        if self.data:
            self.parse()
            
        
    def input(self, filename, verbose=0):
        fi = open(filename, 'r')
        for line in fi:
            self.data.append(line)
        fi.close()

    def parse(self):
        n_decode = 0
        n_coreA = 0
        n_coreB = 0

        for dt in self.data:
            if 'words' in dt:
                n_decode += 1
                
                
            print dt
            sys.exit()

    
if __name__ == '__main__':
    main()


