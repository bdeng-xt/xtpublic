# -*- coding: utf-8 -*-

import os,sys

import datetime
import time
import math
import pymongo

import config 


def get_list_chunks(l,n=2):
    start=0
    for i in range(n):
        stop=start+len(l[::n])
        yield l[start:stop]
        start=stop
def get_docs(mongo_cfg,dbname,colname,query={},proj={}):
    host=mongo_cfg.get('host','127.0.0.1')
    port=mongo_cfg.get('port',27017)
    username=mongo_cfg.get('username','')
    password=mongo_cfg.get('password','')
    authSource=dbname
    mongo_client=pymongo.MongoClient(host=host,port=port,username=username,password=password,authSource=authSource)
    if mongo_client is None:
        return []       
    db=mongo_client[dbname]
    docs=[]  
    if not colname in db.collection_names():
      return docs
    try:
        coll=db[colname]
        if len(proj)==0:
            docs=list(coll.find(query))
        else:
            docs=list(coll.find(query,proj))
    finally:
        mongo_client.close()
    return docs
#    for doc in coll.find(query):
#        docs.append(doc)
#    return docs
def get_df(mongo_cfg,dbname,colname,query={},proj={}):
    docs=get_docs(mongo_cfg,dbname,colname,query,proj)
    if docs is None or len(docs)==0:
        return None
    return pd.DataFrame(docs)
def insert_docs(mongo_cfg,dbname,collname,docs):
    if docs is None or len(docs)==0:
        linfo='mongoutil::insert_docs, nrecords:%s' (len(docs))
        print(linfo)
        return 0
    host=mongo_cfg.get('host','127.0.0.1')
    port=mongo_cfg.get('port',27017)
    username=mongo_cfg.get('username','')
    password=mongo_cfg.get('password','')
    authSource=dbname
    mongo_client=pymongo.MongoClient(host=host,port=port,username=username,password=password,authSource=authSource)
    if mongo_client is None:
        return 0       
    db=mongo_client[dbname]
    coll=db[collname]
    ninserted=len(docs)
    nchunks=int(ndocs/100)+1
    for chunk in get_list_chunks(docs,nchunks):
        chunksize=len(chunk)
        try:
            coll.insert_many(chunk,ordered=False,bypass_document_validation=True)
        except pymongo.errors.BulkWriteError as bwe:
            linfo='got pymongo.errors.BulkWriteError, mongoutil::insert_docs,dbname:%s,collname:%s,nrecords:%s,exception:%s' % (dbname,collname,chunksize,bwe)
            print(linfo)
            ninserted=ninserted-chunksize
            pass
        except pymongo.errors.DuplicateKeyError as dke:
            linfo='got pymongo.errors.DuplicateKeyError, mongoutil::insert_docs,dbname:%s,collname:%s,nrecords:%s,exception:%s' % (dbname,collname,chunksize,dke)
            print(linfo)
            ninserted=ninserted-chunksize
            pass
        except Exception as e:
            linfo='got unknown exception, mongoutil::insert_docs,dbname:%s,collname:%s,nrecords:%s,exception:%s' % (dbname,collname,chunksize,e)
            ninserted=ninserted-chunksize
            print(linfo)
            pass 
        finally:
            linfo='mongoutil::insert_docs,dbname:%s,collname:%s,nrecords:%s' % (dbname,collname,chunksize)
            print(linfo)  
    return ninserted          
        
  