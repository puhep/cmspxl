"""
Providing Tools for file handling.

"""

import os
import sys
import filecmp
import shutil
from ConfigParser import RawConfigParser


__author__ = "Xin Shi <Xin.Shi@cern.ch>"
__copyright__ = "Copyright (c) Xin Shi"


# ------------------------------------------------------------
# Functions 
# ------------------------------------------------------------
def make_tmpfile(f):
    path, name = os.path.split(f)
    tmpname = '.tmp_' + name
    tmpfile = os.path.join(path, tmpname)
    return tmpfile


def check_update_status(f, verbose=1):
    tmpfile = make_tmpfile(f)
    if not os.access(tmpfile, os.F_OK):
        message = 'created %s ...\n' %f
        shutil.copy2(f, tmpfile)
    elif filecmp.cmp(f, tmpfile, shallow=False):
        message = 'up-to-date: %s\n' % f
    else:
        message = 'updated %s ...\n' %f
        #os.remove(tmpfile)

    if verbose > 0 :
        sys.stdout.write(message)

    return message


def check_and_copy(source_file, dest_file, verbose=1):
    message = ''
    local_source_file = None
    if '@' in source_file and ':' in source_file:
        local_source_file = make_tmpfile(dest_file)
        try:
            p = subprocess.Popen(['scp', source_file, local_source_file])
            os.waitpid(p.pid, 0)
            source_file = local_source_file
        except IOError:
            sys.stdout.write('Skipping %s \n' %source_file)
            return 

    if os.access(dest_file, os.F_OK) :
        if filecmp.cmp(source_file, dest_file, shallow=False):
            message =  'up-to-date: %s' % dest_file
        else:
            message = 'Updating %s ...' %dest_file
    else:
        message = 'Writing %s ...' %dest_file
    try:
        shutil.copy2(source_file, dest_file)
    except IOError:
        sys.stdout.write('Skipping %s \n' %source_file)
        return 
            
    if local_source_file != None:
        os.remove(local_source_file)

    if verbose > 0:
        sys.stdout.write(message+'\n')
        
    return message


def check_and_join(filepath, filename):
    if '/castor' in filepath:
        cmd = 'rfdir %s' % filepath
        stdout = proc_cmd(cmd)
        if 'No such file or directory' in stdout:
            sys.stdout.write('creating dir (chmod 775) %s ...' % filepath)
            cmd = 'rfmkdir -p %s' % filepath
            proc_cmd(cmd)
            cmd = 'rfchmod 775 %s' % filepath
            proc_cmd(cmd)
            sys.stdout.write(' OK.\n')
    else: 
        if not os.access(filepath, os.F_OK):
            sys.stdout.write('creating dir %s ...' % filepath)
            os.makedirs(filepath)
            sys.stdout.write(' OK.\n')
        
    file_ = os.path.join(filepath, filename)
    if os.access(file_, os.F_OK) :
        tmpfile = make_tmpfile(file_)
        shutil.copy2(file_, tmpfile)

    return file_


# ------------------------------------------------------------
# Classes 
# ------------------------------------------------------------


class UserFile(object):
    '''Class to handle file  '''
    def __init__(self, filename=None, data=None):
        self.data = []
        if data != None:
            self.data = data
            
        if filename:
            self.input(filename)
            self.file = filename

    def append(self, content):
        self.data.append(content)

    def backup(self, prefix, verbose=0):
        path, name =  os.path.split(self.file)
        backup_file  = os.path.join(path, prefix + name)

        if 'default' in prefix and os.path.exists(backup_file):
            if verbose > 0: 
                sys.stdout.write('\nDefault file exits! : %s\n' % backup_file)
            return

        self.output(backup_file , verbose)

    def extend(self, content):
        self.data.extend(content)

    def find(self, pat):
        for line in self.data:
            if pat in line:
                return True
        return False

    def input(self, filename, verbose=0):
        fi = open(filename, 'r')
        for line in fi:
            self.data.append(line)
        fi.close()

    def input_data(self, data):
        self.data = data 

    def insert(self, index, newline):
        line_num = 0
        for line in self.data:
            line_num = line_num + 1
            if index in line:
                self.data.insert(line_num-1, newline)
                return 
        
    def output(self, f=None, verbose=1):
        fo = sys.stdout
        if f != None:
            filepath, filename = os.path.split(f)
            f = check_and_join(filepath, filename) 
            fo = open(f ,'w')
            
        for line in self.data:
            fo.write(line)
        fo.close()
        
        if f != None:
            message = check_update_status(f, verbose=verbose)
            return message


    def replace(self, old, new):
        line_num = 0
        for line in self.data:
            line_num = line_num + 1
            if old in line:
                self.data[line_num-1] = line.replace(old, new)

    def restore(self, prefix, verbose=0):
        path, name  =  os.path.split(self.file)
        backup_file =  os.path.join(path, prefix + name)
        f = UserFile(backup_file)
        self.data = f.data
            

    def get_key_value(self, key, sep=' ', key_pos=0, value_pos=1, verbose=0):
        for line in self.data:
            line = line.strip()
            items = [li for li in line.split(sep) if li]
            value = None
            if key in items and items[key_pos] == key:
                value = items[value_pos]
                break

        if value == None:
            print '\n'.join(self.data) 
            raise NameError(key)

        return value 


    def set_key_value(self, key, value, sep=' ', key_pos=0, value_pos=1,
                      verbose=0):
        old_value = self.get_key_value(key, key_pos=key_pos, 
                                       value_pos=value_pos)
        for line in self.data:
            line_tmp = line.strip()
            items = [li for li in line_tmp.split(sep) if li]
            if key in items and items[key_pos] == key:
                old = line
                new = old.replace(old_value, value)
                if verbose > 0:
                    sys.stdout.write('Old: %s' % old)
                    sys.stdout.write('New: %s' % new)
                self.replace(old, new)


    def add_key_value(self, key, value, sep=' ', verbose=0):
        old = self.get_key_value(key)
        new = str(eval(old) + eval(value))
        self.set_key_value(key, new, sep, verbose)


    def sub_key_value(self, key, value, sep=' ', verbose=0):
        old = self.get_key_value(key)
        new = str(eval(old) - eval(value))
        self.set_key_value(key, new, sep, verbose)


