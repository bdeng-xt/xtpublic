#pragma once
#ifndef XT_NNG_UTIL_H
#define XT_NNG_UTIL_H


#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>

#include "XTConfig.h"

#include "XTConfig.h"

#include "nng.h"
#include "compat/nanomsg/nn.h"
#include "compat/nanomsg/nn_pubsub.h"
#include "compat/nanomsg/nn_reqrep.h"
#include "compat/nanomsg/nn_pipeline.h"
#include "compat/nanomsg/nn_bus.h"

namespace XT
{

class XT_COMMON_API NNGUtil {
public:
	NNGUtil() {} // = delete;
	NNGUtil(const NNGUtil&) {} // = delete;
   //	NNGUtil(NNGUtil&&) {} // = delete;
	~NNGUtil() {} // = delete;

	NNGUtil& operator=(const NNGUtil&) { return *this; } // = delete;
 //	NNGUtil& operator=(NNGUtil&&) { return *this; } // = delete;

public:
	static const std::string get_protocol_name(int p);

	static int get_opposite_protocol(int p);

};//class
}//namespace

#endif