import os
import sys
import platform

#import configparser

def get_python_major_version():
    v=sys.version_info
    return v[0]
def get_architecture_name():
    platformname=sys.platform
    arch=platform.architecture()[0]
    name='unknown'
    if platformname.startswith('win'):
        if arch.startswith("64"):
            name='win64'
        else:
            name='win32'
    elif platformname.startswith('linux'):
        if arch.startswith("64"):
            name='linux64'
        else:
            name='linux32'
    elif platformname.startswith('darwin'):
        if arch.startswith("64"):
            name='darwin64'
        else:
            name='darwin32'
    return name
#####
def add_current_path():
    p=os.getcwd()
    if not p in sys.path:
        sys.path.append(p)
        linfo='added path:%s' % (p)
        print(linfo)
    ldlibpath=os.environ.get('LD_LIBRARY_PATH','')
    if not p in ldlibpath:
        if ldlibpath=='':
            os.environ['LD_LIBRARY_PATH']=p
        else:
            os.environ['LD_LIBRARY_PATH']='%s:%s' % (p,ldlibpath)
    return
def add_path(p):
    if len(p)==0:
        return
    if not p in sys.path:
        sys.path.append(p)
        linfo='added to sys.path:%s' % (p)
        print(linfo)
    ldlibpath=os.environ.get('LD_LIBRARY_PATH','')
    if not p in ldlibpath:
        if ldlibpath=='':
            os.environ['LD_LIBRARY_PATH']=p
        else:
            os.environ['LD_LIBRARY_PATH']='%s:%s' % (p,ldlibpath)
        new_ldlibpath=os.environ.get('LD_LIBRARY_PATH','')
        linfo='enviro["LD_LIBRARy_PATH"]:%s' % (new_ldlibpath)
        print(linfo)
    return
def change_to_path(p):
    try:
        os.chdir(p)
        add_current_path()
        linfo='change to path:%s' % (os.getcwd())
        print(linfo)
    except Exception as e:
        linfo='change_to_path, exception:%s' % (str(e))
        print(linfo)
    return
def change_to_lib_path():
    archname=get_architecture_name()
    libpath=''
    if archname=="win32":
        libpath='../../lib/win32'
    elif archname=="win64":
        libpath='../../lib/win64'
    elif archname=="linux64":
        libpath='../../lib/linux64'
    else:
        linfo='not available for arch:%s' % (archname)
        print(linfo)
    if libpath=='':
        return False
    change_to_path(libpath)
    return True
######
pyxt=None
def import_pyxtcommon():
    global pyxt
    if not pyxt is None:
        return pyxt
    archname=get_architecture_name()
    py_major_version=get_python_major_version()
    linfo='start to import pyxtcommon'
    print(linfo)
    currpath=os.getcwd()
    add_path(currpath)
    libpath=''
    if archname=="win32":
        libpath='../../lib/win32'
    elif archname=="win64":
        libpath='../../lib/win64'
    elif archname=="linux64":
        libpath='../../lib/linux64'
    else:
        linfo='not available for arch:%s' % (archname)
        print(linfo)
    if libpath=='':
        return None
    add_path(libpath)    
#    if libpath not in sys.path:
#        sys.path.append(libpath)
    change_to_path(libpath)
    try:
        if py_major_version==2:
            import pyxtcommon2 as pyxt
        else:
            import pyxtcommon as pyxt
    except Exception as e:
        linfo='import_pyxtcommon, got exception: %s' % (str(e))
        print(linfo)
        pyxt=None
    os.chdir(currpath)
    return pyxt

    ####
