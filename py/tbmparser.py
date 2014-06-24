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
    fi = open(filename, 'r')
    for line in fi:
        print line
        
    sys.exit()

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


