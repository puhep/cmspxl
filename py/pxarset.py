#!/usr/bin/env python
"""
Main script to maneuver parameters for pXar 

"""

__author__ = "Xin Shi <Xin.Shi@cern.ch>"


import sys
import os 
from filetools import UserFile


def usage():
    sys.stdout.write('-'*60 + '\n')
    sys.stdout.write('Examples: \n')
    sys.stdout.write('-'*60 + '\n\n')

    sys.stdout.write(' 1. Set DAC parameters for specfic ROCs: \n')
    sys.stdout.write('    pxarset.py dac 1,2,5 set wbc 150 \n\n')

    sys.stdout.write(' 2. Set DAC parameters for all 16 ROCs: \n')
    sys.stdout.write('    pxarset.py dac all set vtrim 70  \n\n')

    sys.stdout.write(' 3. Add DAC parameters for all ROCs: \n')
    sys.stdout.write('    pxarset.py dac all add vthrcomp 10 \n\n')

    sys.stdout.write(' 4. Subtract DAC parameters for all ROCs: \n')
    sys.stdout.write('    pxarset.py dac all sub vana 10 \n\n')

    sys.stdout.write(' 5. Set board configuration:  \n')
    sys.stdout.write('    pxarset.py board set avdd 1750 \n\n')

    sys.stdout.write('-'*60 + '\n')


def main():
    args = sys.argv[1:]
    if len(args)== 0:
        return usage()
    if args[0] == 'dac':
        dac(args[1:])
    elif args[0] == 'board':
        board(args[1:])
    else:
        raise NameError(args)


def dac(args):
    rocs = get_rocs(args[0])
    dacpath = os.getcwd()
    for roc in rocs:
        inname = 'dacParameters_C%s.dat' %roc
        infile = os.path.join(dacpath, inname)
        dac = UserFile(infile)
        action = args[1]
        if action == 'set':
            key = args[2]
            value = args[3]
            dac.set_key_value(key, value, sep=' ', 
                              key_pos=1, value_pos=2, verbose=1)

        elif action == 'add':
            key = args[2]
            value = args[3]
            dac.add_key_value(key, value, sep=' ', 
                              key_pos=1, value_pos=2, verbose=1)
                        
        elif action == 'sub':
            key = args[2]
            value = args[3]
            dac.sub_key_value(key, value, sep=' ',
                              key_pos=1, value_pos=2, verbose=1)
                        
        else:
            raise NameError(args[1])
        dac.output(infile)

    
def board(args):
    cfgpath = os.getcwd()
    cfgname = 'boardConfigurationDataTaking.txt'
    cfgfile = os.path.join(cfgpath, cfgname)
    board = UserFile(cfgfile)

    action = args[0]
    if action == 'set':
        key = args[1]
        value = args[2]
        board.set_key_value(key, value, sep=' ', verbose=1)
    else:
        raise NameError(args[1])

    new_cfgname = cfgname.replace('.txt', '_%s_%s.txt' %(key, value))
    new_cfgfile = os.path.join(cfgpath, new_cfgname)

    board.output(new_cfgfile)


def get_rocs(args):
    if args == 'all':
        rocs = range(16)
    else:
        rocs = args.split(',')
    return rocs 
    

if __name__ == '__main__':
    main()


