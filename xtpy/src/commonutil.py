 # -*- coding: utf-8 -*-
import sys,time
import os
import glob
import fnmatch
import shutil
import warnings

import datetime
import math
import re

import numpy as np
import pandas as pd
import pandas.io.sql as psql

import tables as tb

import json

import codecs
import gzip

import cppheaderparser  as chp

#number
def is_float(v):
    try:
        float(v)
        return True
    except ValueError:
        return False
def is_int(v):
    try:
        int(v)
        return True
    except ValueError:
        return False
def is_year(v):
    year=0
    try:
        year=int(v)
        return year>1000 and year < 9999
    except ValueError:
        return False
def str_to_float(v):
    try:
        d=float(v)
        return d
    except ValueError:
        return 0.0
def str_to_int(v):
    try:
        d=int(v)
        return d
    except ValueError:
        return 0
def str_to_long(v):
    try:
        d=long(v)
        return d
    except ValueError:
        return long(0)
#end number 

#string
def is_any_of_words_in_str(words=[],s=''):
    for w in words:
        if w in s:
            return True
    return False
def is_all_of_words_in_str(words=[],s=''):
    for w in words:
        if not w in s:
            return False
    return True
def is_str_starts_with(prefixes=[],s=''):
    for w in prefixes:
        if s.startswith(w):
            return True
    return False
def is_str_ends_with(suffixes=[],s=''):
    for w in suffixes:
        if s.endswith(w):
            return True
    return False    
def add_prefix_for_words_in_str(words=[],s='',prefixstr='',sep=' '):
    items=s.split(sep)
    result=''
    count=0
    for item in items:
        if count>0:
            result='%s%s' % (result,sep)
        if is_any_of_words_in_str(words,item) and (not item.startswith(prefixstr)):
            result='%s%s%s' % (result,prefixstr,item) 
        else:
            result='%s%s' % (result,item)
        count+=1
    return result
def add_suffix_for_words_in_str(words=[],s='',suffixstr='',sep=' '):
    items=s.split(sep)
    result=''
    count=0
    for item in items:
        if count>0:
            result='%s%s' % (result,sep)
        if is_any_of_words_in_str(words,item) and (not item.endswith(suffixstr) ):
            result='%s%s%s' % (result,item,suffixstr) 
        else:
            result='%s%s' % (result,item)
        count+=1
    return result

#end string

#intdate
def get_curr_intdate():
    currdt=datetime.datetime.now()
    return currdt.year*10000+currdt.month*100+currdt.day
def get_prev_intdate(currintdate=None,backdays=1):
    if currintdate is None:
        currdt=datetime.datetime.now()
    else:
        (y,m,d)=parse_intdate(currintdate)
        currdt=datetime.datetime(y,m,d)
    prevdt=currdt-datetime.timedelta(days=backdays)
    return prevdt.year*10000+prevdt.month*100+prevdt.day
def get_prev_working_intdate(currintdate=None):
    if currintdate is None:
        currdt=datetime.datetime.now()
    else:
        (y,m,d)=parse_intdate(currintdate)
        currdt=datetime.datetime(y,m,d)
    if currdt.weekday()==0:
        prevdt=currdt-datetime.timedelta(days=3)
    else:
        prevdt=currdt-datetime.timedelta(days=1)
    return prevdt.year*10000+prevdt.month*100+prevdt.day
def parse_intdate(intdate):
    return (intdate//10000,(intdate%10000)//100,intdate%100)
def get_datetime_for_intdate(intdate):
    (y,m,d)=parse_intdate(intdate)
    return datetime.datetime(y,m,d)
def get_pydt_for_intdate(intdate):
    (y,m,d)=parse_intdate(intdate)
    return datetime.datetime(y,m,d)
def get_prev_datetime_for_intdate(intdate):
    previntdate=get_prev_intdate(intdate)
    return get_datetime_for_intdate(previntdate)
def get_monthday_str_for_intdate(intdate):
    (y,m,d)=parse_intdate(intdate)
    return "%02d%02d" % (m,d)
def get_days_between_intdates(intdate1,intdate2):
    dt1=get_datetime_for_intdate(intdate1)
    dt2=get_datetime_for_intdate(intdate2)
    td=dt2-dt1
    return td.days+1
def get_intdate_from_datestr(s):
    return (int)(s.replace('-',''))
def get_intdate_from_pydt(dt):
    return dt.year*10000+dt.month*100+dt.day
#end intdate

#time
def pydt_to_str19(pydt):
    return pydt.strftime('%Y-%m-%d %H:%M:%S')
def get_ts_for_pydt(pydt):
    return (int)(1000000*(pydt-datetime.datetime(1970,1,1)).total_seconds())
def get_ts_for_intdate(intdate):
    pydt=get_pydt_for_intdate(intdate)
    return get_ts_for_pydt(pydt)
def pydt_to_int64_ts(pydt):
    return (int)(1000000*(pydt-datetime.datetime(1970,1,1)).total_seconds())
def pydt_to_timestamp(pydt):
    return (pydt-datetime.datetime(1970,1,1)).total_seconds()
def get_dtstr_for_ActionDay_UpdateTime_UpdateMillisec(ActionDay,UpdateTime,UpdateMillisec):
#    if len(ActionDay)!=8:
#        return ''
    return "%s-%s-%s %s.%06d" % (ActionDay[0:4],ActionDay[4:6],ActionDay[6:8],UpdateTime,UpdateMillisec*1000)
def get_dtstr_for_tradingDay_UpdateTime_UpdateMillisec(tradingDay,UpdateTime,UpdateMillisec):
    hour=(int)(str(UpdateTime[0:2]))
    if hour<18:
        return "%s-%s-%s %s.%06d" % (tradingDay[0:4],tradingDay[4:6],tradingDay[6:8],UpdateTime,UpdateMillisec*1000)
    intdate=(int)(tradingDay)
    intdate=get_prev_working_intdate(intdate)
    return "%04d-%02d-%02d %s.%06d" % (intdate/10000,(intdate%10000)/100,intdate % 100,UpdateTime,UpdateMillisec*1000)
def get_pydt_for_dtstr(s):
    if len(s)>=20:
        return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]), int(s[20:])*(10**(6-len(s[20:]))) )
    elif len(s)==19:
        return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]))
    elif len(s)==10:
        return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]))
    else:
        return datetime.datetime(1970,1, 1)    
#    return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]), int(s[20:])*(10**(6-len(s[20:]))) )
def get_int64_ts_for_pydt(pydt):
    return (long)(1000000*(pydt-datetime.datetime(1970,1,1)).total_seconds())
def get_unix_timestamp_for_pydt(pydt):
    return (pydt-datetime.datetime(1970,1,1)).total_seconds()
def get_pddt_for_dtstr(s):
    return pd.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]), int(s[20:])*(10**(6-len(s[20:]))) )
def get_pydt_for_dtstr19(s):
    return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]))
def get_pydt_for_dtstr23(s):
    return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]),int(s[20:23]) )
def get_pydt_for_dtstr26(s):
    return datetime.datetime(int(s[0:4]), int(s[5:7]), int(s[8:10]), int(s[11:13]), int(s[14:16]), int(s[17:19]),int(s[20:26]) )
def get_pydt_for_intdate(intdate):
    (y,m,d)=parse_intdate(intdate)
    return datetime.datetime(y,m,d)
def get_pydt_for_ts(ts):
    return datetime.datetime(1970,1,1)+datetime.timedelta(microseconds=ts)	

def get_pydt_for_dzh_updatedt(s):
    year=0
    month=0
    day=0
    hour=0
    minute=0
    second=0
    microsecond=0
    items=s.split(' ')
    if len(items)>1:
        items0=items[0].split('-')
        if len(items0)>2:
            year=int(items0[0])
            month=int(items0[1])
            day=int(items0[2])
        items1=items[1].split('.')
        if len(items1)>1:
            microsecond=1000*int(items1[1])
        items12=items1[0].split(':')
        if len(items12)>2:
            hour=int(items12[0])
            minute=int(items12[1])
            second=int(items12[2])
    return datetime.datetime(year, month, day, hour, minute, second,microsecond )

#end time

#tgz file
def untar_tgz_file(filename,tardir='./'):
    cmd="tar xvfz %s --directory=%s " % (filename,tardir)
    os.system(cmd)
#end tgz file

#read file
def get_chp(filename):
    result=None
    try:
        result=chp.CppHeader(filename)
    except chp.CppParseError as e:
        print(e)
        result=None
    return result
#    
def parse_filename(filename0):
    result={}
    stem=''
    extension=''
    filename=''
    path='./'
    fname=filename0.replace('\\','/')
    tempitems=fname.split('/')
    if len(tempitems)>1:
        path='/'.join(tempitems[0:-1])
        filename=tempitems[-1]
    else:
        filename=filename0
    tempitems=filename.split('.')
    stemp=tempitems[0]
    if len(tempitems)>0:
        extension=tempitems[-1]
        stem=tempitems[0]
    result['filename0']=filename0
    result['path']=path
    result['stem']=stem
    result['extension']=extension
    result['filename']=filename
    return result
    
def parse_daydata_filename(filename0):
    result=parse_filename(filename0)
    stem=result.get('stem','')
    stemitems=stem.split('_')
    if len(stemitems)>=6:
        result['datestr']=stemitems[0]
        result['session']=stemitems[1]
        result['exch']=stemitems[2]
        result['product']=stemitems[3]
        result['sectype']=stemitems[4]
        result['datatype']=stemitems[5]
    return result

def read_file_lines(filename,encoding='UTF-8'):
    lines=[]
    if sys.version_info.major==3:
        with open(filename,'r',encoding=encoding) as f:
            lines=f.readlines()
    else:
        with codecs.open(filename,'r',encoding=encoding) as f:
            lines=f.readlines()
    return lines
def get_files_by_pattern(directory='./',pattern='*'):
    filepattern=("%s/%s") % (directory,pattern)
    return glob.glob(filepattern)
def get_filenames_by_pattern(directory='./',pattern='*'):
    files=get_files_by_pattern(directory,pattern)
    if files is None or len(files)==0:
        return None
    filenames=[]
    for f in files:
        filename=f.split('/')[-1]
        filename=filename.split('\\')[-1]
        filenames.append(filename)
    return filenames
def get_subdirs_by_pattern(directory='./',pattern='*'):
    dirpattern=("%s/%s") % (directory,pattern)
    subdirs=glob.glob(dirpattern)
    results=[]
    for d in subdirs:
        if os.path.isdir(d):
            results.append(d)
    return results
def get_sub_name_for_path_or_file(fullname):
    name=fullname.replace('\\','/')
    items=name.split('/')
    return items[-1]
def get_upper_dir_for_path_or_file(fullname):
    name=fullname.replace('\\','/')
    items=name.split('/')
    return '/'.join(items[0:-1])
def get_files_by_pattern_r(directory='./',pattern='*'):
    results=[]
    for dirpath,dirnames,files in os.walk(directory):
        for f in fnmatch.filter(files,pattern):
            results.append(os.path.join(dirpath,f))
    return results
def get_subdirs_r(directory='./',pattern='*'):
    results=[]
    for dirpath,dirnames,files in os.walk(directory):
        for d in fnmatch.filter(dirnames,pattern):
            results.append(os.path.join(dirpath,d))
    return results
def get_int_subdirs_r(directory):
    results=[]
    for dirpath,dirnames,files in os.walk(directory):
        for d in dirnames:
            if is_int(d):
                results.append(os.path.join(dirpath,d))
    return results

def get_files_linestr_by_pattern(directory='./',pattern='*',quotestr='"',lineprefix="#include "):
    files=get_files_by_pattern(directory,pattern)
    files=[('%s%s%s%s' % (lineprefix,quotestr,f,quotestr)).replace('\\','/') for f in files]
    linestr='\n'.join(files)
    return linestr
def get_files_linestr_by_pattern_r(directory='./',pattern='*',quotestr='"',lineprefix="#include "):
    files=get_files_by_pattern_r(directory,pattern)
    files=[('%s%s%s%s' % (lineprefix,quotestr,f,quotestr)).replace('\\','/') for f in files]
    linestr='\n'.join(files)
    return linestr
def get_file_for_list_by_pattern(items,pattern='%s',filename='temp.txt'):
    outf=open(filename,'w')
    for item in items:
        line=pattern % (item)
        outf.write(line+"\n")
    outf.close()
    return
#end read file

#file
def get_def_file_from_dumpbin_output(dumpbin_output, dll_name):
    def_file='%s.def' % (dll_name)
    dump_str=''
    pattern = r'^\s*(\d+)\s+[A-Z0-9]+\s+[A-Z0-9]{8}\s+([^ ]+)'
    with open(dumpbin_output) as f:
        dump_str=f.read()
    lines=dump_str.split('\n')
    def_str='EXPORTS \n'
    for line in lines:
        matches = re.search(pattern, line)
        if matches is not None:
            function_name = matches.group(2)
            def_str=def_str + function_name + "\n"
    with open(def_file,'w') as fout:
        fout.write(def_str)
    return
#end file

#records
def get_records_from_file(filename,tokenstr,encoding='utf-8'):
    if filename.endswith(".gz"):
        f=gzip.open(filename,'rb')##,encoding=encoding) encoding not supported in binary mode
    else:
        f=open(filename,'rb') #,encoding=encoding)
    grepper=grep(lambda line : tokenstr.encode(encoding) in line)#grep(lambda line : tokenstr in line)
    matched=grepper(f)
    records=list(matched)
    f.close()
    return records
def is_json(s):
    try:
        j=json.loads(s)
    except (ValueError,e):
        return False
    return True
def get_json(s,encoding='latin-1'):
    try:
        j=json.loads(s,encoding=encoding)
    except (ValueError):
        linfo='error in get_json,%s' % (s)
        print(linfo) 
        return None
    return j
def get_json_records_from_file(filename,tokenstr,encoding='utf-8'):
    records=get_records_from_file(filename,tokenstr,encoding=encoding)
    results=[]
    if(len(records)==0):
        return results
#    results=[json.loads(r,encoding='gbk') for r in records]
    results=[get_json(r,encoding) for r in records]
    results=[r for r in results if r is not None] 
    return results
def get_df_from_file(filename,tokenstr,encoding='utf-8'):
    js=get_json_records_from_file(filename,tokenstr,encoding=encoding)
    if(len(js)==0):
        return None
    df=pd.DataFrame(js)
    del js
    return df
def get_records_from_files(filenames,tokenstr,encoding='utf-8'):
    if(len(filenames)==0):
        return None
    results=[]
    for filename in filenames:
        records=get_records_from_file(filename,tokenstr,encoding=encoding)
        if (not records is None) and (len(records)>0):
            results.extend(records)
    return results
def get_json_records_from_files(filenames,tokenstr,encoding='utf-8'):
    records=get_records_from_files(filenames,tokenstr)
    results=[]
    if (records is None) or (len(records)==0):
        return results
    results=[json.loads(r,encoding='gbk') for r in records]
    del records
    return results
def get_df_from_files(filenames,tokenstr,encoding='utf-8'):
    dfs=[]
    for filename in filenames:
        df=get_df_from_file(filename,tokenstr,encoding=encoding)
        if not df is None and len(df)>0:
            dfs.append(df)
    if len(dfs)==0:
        return None
    return pd.concat(dfs,axis=0)
#endrecords

#csv files
def get_df_from_csv(filename,in_encoding='utf_8'):
    df=None 
    try:
        if filename.endswith('gz'):
            df=pd.read_csv(filename,compression='gzip',encoding=in_encoding)
        else:
            df=pd.read_csv(filename,encoding=in_encoding)
    except:
        linfo='failed to read %s' % (filename)
        print(linfo)
    return df

#end csv files
#files
def create_dir_for_intdate(datadir,intdate):
    (year,month,day)=parse_intdate(intdate)
    tgtdir="%s/%04d/%02d/%02d" % (datadir,year,month,day)
    if not os.path.exists(tgtdir):
        os.makedirs(tgtdir)
#    yeardir='%s/%s' % (datadir,year)
#    if not os.path.exists(yeardir):
#        os.system("mkdir %s" % (yeardir))
#        os.system("chmod -R a+r %s" % (yeardir))
#    monthdir='%s/%02d' % (yeardir,month)
#    if not os.path.exists(monthdir):
#        os.system("mkdir %s" % (monthdir))
#        if os.name!='nt':
#            os.system("chmod -R a+r %s" % (monthdir))
#    daydir='%s/%02d' % (monthdir,day)
#    if not os.path.exists(daydir):
#        os.system("mkdir %s" % (daydir))
#        if os.name!='nt':
#            os.system("chmod -R a+r %s" % (daydir))
    return True
def get_dir_for_intdate(datadir,intdate):
    (year,month,day)=parse_intdate(intdate)
    tgtdir="%s/%04d/%02d/%02d" % (datadir,year,month,day)
    if not os.path.exists(tgtdir):
        os.makedirs(tgtdir)
    return tgtdir

###########################

def create_dir_for_exch_intdate(datadir,exch,intdate):
    (year,month,day)=parse_intdate(intdate)
    tgtdir="%s/%s/%04d/%02d/%02d" % (datadir,exch,year,month,day)
    if not os.path.exists(tgtdir):
        os.makedirs(tgtdir)
    return True
def create_dir_for_exch(datadir,exch):
    tgtdir='%s/%s' % (datadir,exch)
    if not os.path.exists(tgtdir):
        os.makedirs(tgtdir)
#        os.system("mkdir %s" % (tgtdir))
#        os.system("chmod -R a+r %s " %(tgtdir))
    return True

def get_subdir_names(datadir):
    subdirs=get_subdirs_by_pattern(datadir)
    sub_names=[get_sub_name_for_path_or_file(subdir) for subdir in subdirs]
    sub_names.sort()
    return sub_names
def get_subdir_ints(datadir):
    subdirs=get_subdirs_by_pattern(datadir)
    results=[]
    for subdir in subdirs:
        d=get_sub_name_for_path_or_file(subdir)
        if is_int(d):
            results.append((int)(d))
    results.sort()
    return results

def get_dir_years_for_exch(datadir,exch):
    d='%s/%s' % (datadir,exch)
    return get_subdir_ints(d)
def get_dir_months_for_exch_year(datadir,exch,year):
    d='%s/%s/%04d' % (datadir,exch,year)
    return get_subdir_ints(d)
def get_dir_days_for_exch_year_month(datadir,exch,year,month):
    d='%s/%s/%04d/%02d' % (datadir,exch,year,month)
    return get_subdir_ints(d)
def get_dir_intdates_for_exch(datadir,exch):
    results=[]
    years=get_dir_years_for_exch(datadir,exch)
    for year in years:
        months=get_dir_months_for_exch_year(datadir,exch,year)
        for month in months:
            days=get_dir_days_for_exch_year_month(datadir,exch,year,month)
            for day in days:
                if is_int(year) and is_int(month) and is_int(day):
                    intdate=((int)(year))*10000+((int)(month))*100 + ((int)(day))
                    results.append(intdate)
    results.sort()
    return results
def get_dir_intdates_for_exch_between_intdates(datadir,exch,beginIntdate,endIntdate):
    intdates=get_dir_intdates_for_exch(datadir,exch)
    results=[intdate for intdate in intdates if (intdate>=beginIntdate and intdate <=endIntdate)]
    results.sort()
    return results
def get_dir_intdates_for_exch_year(datadir,exch,year):
    results=[]
    dir_year='%s/%s/%04d' % (datadir,exch,year)
    if not os.path.exists(dir_year):
        return results
    months=get_dir_months_for_exch_year(datadir,exch,year)
    for month in months:
        days=get_dir_days_for_exch_year_month(datadir,exch,year,month)
        for day in days:
            if is_int(year) and is_int(month) and is_int(day):
                intdate=((int)(year))*10000+((int)(month))*100 + ((int)(day))
                results.append(intdate)
    results.sort()
    return results
def get_dir_intdate_for_exch_year_month(datadir,exch,year,month):
    results=[]
    dir_month='%s/%s/%04d/%02d' % (datadir,exch,year,month)
    if not os.path.exists(dir_month):
        return results
    days=get_dir_days_for_exch_year_month(datadir,exch,year,month)
    for day in days:
        if is_int(year) and is_int(month) and is_int(day):
            intdate=((int)(year))*10000+((int)(month))*100 + ((int)(day))
            results.append(intdate)
    results.sort()
    return results
#endfiles

#########################################################33
def get_list_chunks(l,n=2):
    start=0
    for i in range(n):
        stop=start+len(l[::n])
        yield l[start:stop]
        start=stop
        

#grep help function
def grep(*matches):
     """Returns a generator function that operates on in iterable:
     filters items ini the iterable that match any of the patterns.

     match: a callable returning a True value if it matches the items
     example:
     >>>import re
     >>>input =["alpha\n","beta\n","gamma\n","delta\n"]
     >>>list(grep(re.compile('b').match)(input))
     ['beta\n']

     to pick lines containing the string foo out an input file:
     f=file(...)
     grepper=grep(lambda line: "foo" in line)
     matched=grepper(f) 
     
     """
     def _do_grep_wrapper(*matches):
         def _do_grep(lines):
             for line in lines:
                 for match in matches:
                     if match(line):
                         yield line
                         break
         return _do_grep
     return _do_grep_wrapper(*matches)
#end grep help function
